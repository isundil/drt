#include "ManagedScene.hpp"
#include "WorkerManager.hpp"
#include "NetworkWorker.hpp"
#include "network/PeerInfo.hpp"
#include "network/NetworkPacket.hpp"
#include "render/Scene.hpp"

using namespace drt::worker;

ManagedScene::ManagedScene(WorkerManager &m, network::PeerInfo *pi, render::Scene *s): manager(m), peer(pi), scene(s), done(false)
{
	std::list<network::PeerInfo *>ps = m.getNetwork()->getSrv();

	pixels = new std::pair<drt::network::PeerInfo *, bool>*[s->getHeight()];
	for (int i = s->getHeight() -1; i >= 0; i--)
	{
		pixels[i] = new std::pair<drt::network::PeerInfo *, bool>[s->getWidth()];
		for (int j = s->getWidth() -1; j >= 0; j--)
			pixels[i][j] = std::make_pair(nullptr, true);
	}
	elligiblePeers.insert(m.getNetwork()->getMe());
	px = py = 0;
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
			if (pixels[i][j].second == false && pixels[i][j].first->getId() == id)
				pixels[i][j].first = nullptr;
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

drt::worker::AWorker::Operation *ManagedScene::getNextOp()
{
	if (done)
		return nullptr;
	drt::worker::AWorker::Operation *op = new drt::worker::AWorker::Operation(peer, scene, px, py);
	px++;
	if (px == scene->getWidth())
	{
		px = 0;
		py++;
	}
	if (px == 0 && py == scene->getHeight())
	{
		done = true;
		delete op;
		return nullptr;
	}
	return op;
}

bool ManagedScene::ready(drt::network::PeerInfo *pi)
{
	if (elligiblePeers.find(pi) == elligiblePeers.end())
		return false;
	drt::worker::AWorker::Operation * op = getNextOp();
	if (!op)
		return false;
	pixels[op->y][op->x] = std::make_pair(pi, false);
	if (pi == manager.getNetwork()->getMe())
		manager.addOperation(op);
	else
	{
		manager.send(pi, new drt::network::Calc(scene->getId(), pi->getId(), *op));
		delete op;
	}
	return true;
}

