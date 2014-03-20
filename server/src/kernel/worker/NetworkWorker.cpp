#include <set>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <stropts.h>
#include "worker/NetworkWorker.hpp"
#include "worker/WorkerManager.hpp"
#include "config/PeerSection.hpp"
#include "config/ServerSection.hpp"
#include "config/Config.hpp"
#include "network/ServerSocket.hpp"
#include "network/Socket.hpp"
#include "network/PeerInfo.hpp"
#include "network/NetworkPacket.hpp"
#include "system/CpuUsage.hpp"
#include "system/MemUsage.hpp"

using namespace drt::worker;

class is_connected
{
	public:
		is_connected(const std::list<std::pair<std::string, unsigned short> >&e, const std::list<std::pair<std::string, unsigned short> >&f): list(e)
		{
			for (auto i =f.cbegin(); i != f.cend(); i++)
				list.push_back(*i);
		}

		bool operator()(const std::pair<std::string, unsigned short> item)
		{
			for (auto i = list.cbegin(); i != list.cend(); i++)
				if (*i == item)
					return true;
			return false;
		}

	private:
		std::list<std::pair<std::string, unsigned short> >list;
};

NetworkWorker::NetworkWorker(drt::WorkerManager &_manager, unsigned int _id): AWorker(_manager, _id), connectingTo(nullptr), myself(drt::network::PeerInfo::getMe()), biggerId(1)
{
	const drt::parser::ServerSection *config;

	lastConnectAtempt = 0;

	config = _manager.config()->getSection<drt::parser::ServerSection>();
	server = nullptr;
	if (config->enabled())
	{
		std::stringstream ss;
		ss << "Started server on port " << config->getPort();
		server = new drt::network::ServerSocket(config->getPort());
		_manager.log(std::cout, *this, ss.str());
	}
}

NetworkWorker::~NetworkWorker()
{
	delete myself;
	if (server)
		delete server;
}

void NetworkWorker::start()
{
	while (!manager.isDone())
	{
		bool use = false;

		use |= acceptNew();
		use |= readAll();
		use |= connectToPeers();
		use |= sendAll();
		if (!use)
			usleep(500);
	}
}

bool NetworkWorker::acceptNew()
{
	if (server != nullptr)
	{
		drt::network::Socket *s = server->accept();
		if (s)
		{
			clients.push_back(new drt::network::PeerInfo(s, true));
			manager.log(std::cout, *this, "new client");
			return true;
		}
	}
	return false;
}

void NetworkWorker::sendCpuUsage()
{
	std::pair<int, int> memInfo[2];
	std::list<int> usage = system::CpuUsage::getCpuUsage();
	system::MemUsage::getMemUsage(memInfo[0], memInfo[1]);
	network::PeerInfo::stats st;
	network::ClientMonitor *cm = nullptr;

	for (auto i = usage.cbegin(); i != usage.cend(); i++)
		st.cpus.push_back((*i));
	st.ram = memInfo[0].first;
	st.maxRam = memInfo[0].second;
	st.swap = memInfo[1].first;
	st.maxSwap = memInfo[1].second;
	getMe()->setStats(st);
	manager.broadcast(new network::Monitor(*(getMe())));

	for (auto i = clients.cbegin(); i != clients.cend(); i++)
		if ((*i)->isAClient() && (*i)->isDirect())
		{
			if (!cm)
				cm = getAvgUsage();
			manager.send(*i, new network::ClientMonitor(*cm));
		}
	if (cm)
		delete cm;
}

drt::network::ClientMonitor *NetworkWorker::getAvgUsage() const
{
	network::ClientMonitor *result = new network::ClientMonitor();

	if (myself->getStats())
		result->addStat(*(myself->getStats()));
	for (auto i =clients.cbegin(); i != clients.cend(); i++)
		if (!(*i)->isAClient())
		{
			const drt::network::PeerInfo::stats *st;

			if ((st = (*i)->getStats()) != nullptr)
				result->addStat(*st);
		}
	return result;
}

bool NetworkWorker::connectToPeers()
{
	std::list<std::pair<std::string, unsigned short> >clients = manager.config()->getSection<drt::parser::PeerSection>()->getPeerlist();
	is_connected d(connectedPeers, blackListedPeers);
	bool use = false;

	if (time(nullptr) - lastConnectAtempt < 5)
		return false;
	sendCpuUsage();
	if (connectingTo)
		return false;
	lastConnectAtempt = time(nullptr);
	clients.remove_if(d);
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		std::pair<std::string, unsigned short> addr = (*i);
		network::PeerInfo *pi;

		std::cerr << "DEBUG trying to connect to next server" << std::endl;
		try
		{
			pi = new network::PeerInfo(addr.first, addr.second);
			use = true;
		}
		catch (std::exception &e)
		{
			manager.log(std::cout, *this, "Unable to server: " +std::string(e.what()));
			continue;
		}

		connectingTo = pi;
		manager.send(pi, new network::SAuth(-1, this->clients.size()));
		connectedPeers.push_back(std::pair<std::string, unsigned short> (*i));
		this->clients.push_back(pi);
		std::stringstream ss;
		ss << "Successfull connection to " << addr.first << ":" << addr.second;
		manager.log(std::cout, *this, ss.str());
		break;
	}

	std::stringstream ss;
	ss << std::endl << "I'm ";
	ss.width(9);
	ss << this->getMe()->getId() << "[C][D] - " << this->getMe()->getStats()->debug() << std::endl;
	for (auto i = this->clients.cbegin(); i != this->clients.cend(); i++)
	{
		ss << "Client ";
		ss.width(6);
		ss << (*i)->getId();
		if (!(*i)->getConfirmed())
			ss << "[C]";
		else
			ss << "   ";
		if ((*i)->isDirect())
			ss << "[D]";
		else
			ss << "   ";
		ss << " - " << (*i)->getStats()->debug();
		ss << std::endl;
	}
	manager.log(std::cout, *this, ss.str());
	return use;
}

void NetworkWorker::releasePeer(network::PeerInfo *peer)
{
	std::stringstream ss;
	network::Socket *sock;

	if (!peer)
		return;
	std::cout << "Release Peer " << peer->getId() << std::endl;
	sock = peer->getSocket();
	clients.remove(peer);
	ss << "Lost connection to " << peer->getConInfo().first << ":" << peer->getConInfo().second;
	manager.log(std::cout, *this, ss.str());
	if (peer->isDirect())
		connectedPeers.remove(peer->getConInfo());
	if (peer->isDirect())
	{
		std::list<network::PeerInfo *> n;

		for (auto i = clients.cbegin(); i != clients.cend(); i++)
			if ((*i)->getSocket() == sock)
				n.push_back(*i);
		for (auto i = n.cbegin(); i != n.cend(); i++)
			releasePeer(*i);
	}
	delete peer;
}

bool NetworkWorker::readAll()
{
	fd_set fdset;
	const network::Socket *biggerFd =nullptr;
	std::set<network::Socket *> discon;
	bool usage = false;

	if (clients.size() == 0)
		return false;
	FD_ZERO(&fdset);
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		if (!(*i)->isDirect())
			continue;
		(*i)->getSocket()->addToSet(&fdset);
		biggerFd = (*i)->getSocket()->greater(biggerFd);
	}
	if (biggerFd == nullptr || biggerFd->select(&fdset) <= 0)
		return false;
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		if (!(*i)->getSocket()->isInSet(&fdset) || !(*i)->isDirect())
			continue;
		if ((*i)->getSocket()->isClosed())
		{
			if ((*i)->isClosing())
				discon.insert((*i)->getSocket());
			else
			{
				discon.insert((*i)->getSocket());
				manager.log(std::cout, *this, "client disconnected");
			}
		}
		else if (discon.find((*i)->getSocket()) == discon.cend() && this->discon.find(*i) == this->discon.cend())
		{
			try
			{
				this->readPeer((*i));
				usage = true;
			}
			catch (std::exception &e)
			{
				discon.insert((*i)->getSocket());
			}
		}
	}
	for (auto i = this->discon.cbegin(); i != this->discon.cend(); i++)
	{
		releasePeer(*i);
		usage = true;
	}
	for (auto i = discon.cbegin(); i != discon.cend(); i++)
	{
		network::PeerInfo * dd = nullptr;

		for (auto j = clients.cbegin(); j != clients.cend() && dd == nullptr; j++)
			if ((*j)->getSocket() == *i && (*j)->isDirect())
				dd = (*j);
		if (dd)
		{
			manager.broadcast(new network::Netsplit(dd->getId()));
			if (this->discon.find(dd) == this->discon.end())
			{
				usage = true;
				releasePeer(dd);
			}
		}
	}
	this->discon.clear();
	return usage;
}

void NetworkWorker::readPeer(network::PeerInfo *peer)
{
	peer->read(manager);
}

void NetworkWorker::stop()
{
	for (auto i = clients.begin(); i != clients.end(); i++)
		delete (*i);
	if (server)
	{
		delete server;
		server = nullptr;
	}
}

bool NetworkWorker::sendAll()
{
	bool usage = false;

	usage |= sendUnique();
	usage |= sendBroadcast();
	return usage;
}

bool NetworkWorker::sendBroadcast()
{
	if (manager.broadcastQueueEmpty())
		return false;
	for (char sendProtec=0; sendProtec < 10 && !manager.broadcastQueueEmpty(); sendProtec++)
	{
		network::Socket *avoid;
		network::ANetworkPacket *packet;
		std::set<network::Socket *> alreadySent;

		manager.getNextBroadcast(&packet, &avoid);
		alreadySent.insert(avoid);
		for (auto i = clients.begin(); i != clients.end(); i++)
		{
			std::stringstream *ss;
			size_t packet_len;

			if (!*i || (*i)->getConfirmed() || (alreadySent.find((*i)->getSocket()) != alreadySent.end()))
				continue;
			if ((*i)->isAClient() && !packet->sendToClient(*i))
				continue;
			ss = packet->getStream(&packet_len);
			(*i)->sendData(*ss, packet_len);
			alreadySent.insert((*i)->getSocket());
			delete ss;
		}
		delete packet;
	}
	return true;
}

template <class T>
static bool isInList(T elem, std::list<T> list)
{
	for (auto i = list.cbegin(); i != list.cend(); i++)
		if ((*i) == elem)
			return true;
	return false;
}

bool NetworkWorker::sendUnique()
{
	if (manager.sendQueueEmpty())
		return false;
	for (char i=0; i < 10 && !manager.sendQueueEmpty(); i++)
	{
		network::PeerInfo *peer;
		network::ANetworkPacket *packet;
		std::stringstream *ss;
		size_t packet_len;

		manager.getNextSend(&packet, &peer);
		if (!isInList(peer, clients))
			continue;
		if (peer->isAClient() && !packet->sendToClient(peer))
			continue;
		ss = packet->getStream(&packet_len);
		peer->sendData(*ss, packet_len);
		delete ss;
		delete packet;
	}
	return true;
}

drt::network::PeerInfo *NetworkWorker::getPeer(unsigned short id)
{
	for (auto i =clients.cbegin(); i != clients.cend(); i++)
		if (id == (*i)->getId())
			return *i;
	return nullptr;
}

void NetworkWorker::sendConnected(drt::network::PeerInfo *p)
{
	for (auto i =clients.cbegin(); i != clients.cend(); i++)
	{
		if (p == *i)
			continue;
		manager.send(p, new network::SAuth((*i)->getId(), 0));
		//TODO
		//if ((*i)->isReady)
		//	manager.send(p, new network::Ready((*i)->getId()));
	}
}

drt::network::PeerInfo *NetworkWorker::addServer(drt::network::Socket *s, unsigned short id)
{
	std::cerr << "new server" << std::endl;
	if (id <= 0)
		id = incBiggerId();
	drt::network::PeerInfo *pi = new network::PeerInfo(s, false, id);
	clients.push_back(pi);
	return pi;
}

void NetworkWorker::setMax(unsigned short newMax)
{
	if (biggerId < newMax)
		biggerId = newMax;
}

unsigned int NetworkWorker::nbSocket(network::Socket *avoid) const
{
	std::set<network::Socket *> used;
	unsigned int result =0;

	used.insert(avoid);
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		if (used.find((*i)->getSocket()) != used.end())
			continue;
		used.insert((*i)->getSocket());
		result++;
	}
	return result;
}

unsigned int NetworkWorker::nbClient() const
{ return clients.size(); }

drt::network::PeerInfo *NetworkWorker::getMe()
{ return myself; }

const std::list<drt::network::PeerInfo *> &NetworkWorker::getPeers() const
{ return clients; }

void NetworkWorker::removeLastPeer()
{
	network::PeerInfo * peer = connectingTo;
	if (peer->isDirect())
	{
		std::pair<std::string, unsigned short> inf = peer->getConInfo();
		this->blackListedPeers.push_back(inf);
	}
	discon.insert(peer);
	connectingTo = nullptr;
	getMe()->setId(getMe()->getOldId());
}

void NetworkWorker::confirm()
{
	connectingTo = nullptr;
}

void NetworkWorker::nextOp(Operation *)
{ }

void NetworkWorker::changeBiggerId(unsigned short _id)
{ biggerId = biggerId > _id ? biggerId : _id; }

unsigned short NetworkWorker::incBiggerId()
{ return ++biggerId; }

void NetworkWorker::rmPeer(network::PeerInfo *p)
{ discon.insert(p); }

