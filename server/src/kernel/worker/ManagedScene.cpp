#include "ManagedScene.hpp"
#include "WorkerManager.hpp"
#include "NetworkWorker.hpp"
#include "network/PeerInfo.hpp"
#include "network/NetworkPacket.hpp"
#include "render/Scene.hpp"

using namespace drt::worker;

ManagedScene::ManagedScene(WorkerManager &m, network::PeerInfo *pi, render::Scene *s): manager(m), peer(pi), scene(s)
{
	std::list<network::PeerInfo *>ps = m.getNetwork()->getSrv();

	pixels = new std::pair<std::list<drt::network::PeerInfo *>, bool>*[s->getHeight()];
	for (int i = s->getHeight() -1; i >= 0; i--)
	{
		pixels[i] = new std::pair<std::list<drt::network::PeerInfo *>, bool>[s->getWidth()];
		for (int j = s->getWidth() -1; j >= 0; j--)
			pixels[i][j] = std::make_pair(std::list<drt::network::PeerInfo *>(), false);
	}
	elligiblePeers.insert(m.getNetwork()->getMe());
	px = py = 0;
	remain = isDone();
	for (auto i =ps.cbegin(); i != ps.cend(); i++)
		elligiblePeers.insert(*i);
	for (auto i =elligiblePeers.cbegin(); i != elligiblePeers.cend(); i++)
		if ((*i)->ready())
			ready(*i);
}

ManagedScene::~ManagedScene()
{
	for (int i = scene->getHeight() -1; i >= 0; i--)
		delete [] pixels[i];
	delete [] pixels;
}

void ManagedScene::removePeer(unsigned short id)
{
	for (auto i = elligiblePeers.begin(); i != elligiblePeers.end(); i++)
		if ((*i)->getId() == id)
		{
			elligiblePeers.erase(i);
			break;
		}
	for (int i = scene->getHeight() -1; i >= 0; i--)
		for (int j = scene->getWidth() -1; j >= 0; j--)
			if (pixels[i][j].second == false)
			{
				std::list<drt::network::PeerInfo *>::iterator p = pixels[i][j].first.end();
				for (auto k = pixels[i][j].first.begin();
						k != pixels[i][j].first.end(); k++)
					if ((*k)->getId() == id)
					{
						p = k;
						break;
					}
				if (p == pixels[i][j].first.end())
					continue;
				pixels[i][j].first.erase(p);
			}
}

void ManagedScene::removePeer(const drt::network::PeerInfo *pi)
{
	removePeer(pi->getId());
}

bool ManagedScene::operator==(const render::Scene &s) const
{ return s.getId() == scene->getId(); }

void ManagedScene::compilFail(const drt::network::PeerInfo *pi)
{
	removePeer(pi);
	if (elligiblePeers.size() == 0)
		throw drt::network::CompilFail(scene->getId());
}

unsigned int ManagedScene::isDone() const
{
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int result = 0;

	while (true)
	{
		if (pixels[y][x].second == false)
			result++;
		x += scene->getWidth() -x < COMPUTE_SQUARE ? scene->getWidth() -x : COMPUTE_SQUARE;
		if (x == scene->getWidth())
		{
			x = 0;
			y += scene->getHeight() -y < COMPUTE_SQUARE ? scene->getHeight()-y : COMPUTE_SQUARE;
		}
		if (x == 0 && y == scene->getHeight())
			break;
	}
	return (result);
}

bool ManagedScene::chunkDone(const drt::network::ChunkResult &chunk)
{
	pixels[chunk.getY()][chunk.getX()].first.remove(manager.getNetwork()->getPeer(chunk.getFrom()));
	if (pixels[chunk.getY()][chunk.getX()].second == true)
		return false;
	pixels[chunk.getY()][chunk.getX()].second = true;
	remain--;
	return true;
}

drt::worker::AWorker::Operation *ManagedScene::getNextOp()
{
	if (remain <= 0)
		return nullptr;
	drt::worker::AWorker::Operation *op = nullptr;
	do {
		if (op)
			delete op;
		op = new drt::worker::AWorker::Operation(peer, scene, px, py,
				scene->getWidth() -px < COMPUTE_SQUARE ? scene->getWidth() -px : COMPUTE_SQUARE,
				scene->getHeight() -py < COMPUTE_SQUARE ? scene->getHeight()-py : COMPUTE_SQUARE);
		px += op->width;
		if (px == scene->getWidth())
		{
			px = 0;
			py += op->height;
		}
		if (px == 0 && py >= scene->getHeight())
			px = py = 0;
	} while (pixels[op->y][op->x].second);
	return op;
}

bool ManagedScene::ready(drt::network::PeerInfo *pi)
{
	if (elligiblePeers.find(pi) == elligiblePeers.end())
		return false;
	drt::worker::AWorker::Operation * op = getNextOp();
	if (!op)
		return false;
	pixels[op->y][op->x].first.push_back(pi);
	if (pi == manager.getNetwork()->getMe())
		manager.addOperation(op);
	else
	{
		manager.send(pi, new drt::network::Calc(scene->getId(), pi->getId(), *op));
		delete op;
	}
	return true;
}

