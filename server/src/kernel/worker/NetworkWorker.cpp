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
		is_connected(std::list<std::pair<std::string, unsigned short> >e): list(e)
		{ }

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

NetworkWorker::NetworkWorker(drt::WorkerManager &_manager, unsigned int _id): AWorker(_manager, _id), myself(drt::network::PeerInfo::getMe()), biggerId(1)
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
		acceptNew();
		readAll();
		connectToPeers();
		sendAll();
		usleep(500);
	}
}

void NetworkWorker::acceptNew()
{
	if (server != nullptr)
	{
		drt::network::Socket *s = server->accept();
		if (s)
		{
			clients.push_back(new drt::network::PeerInfo(s, true));
			manager.log(std::cout, *this, "new client");
		}
	}
}

void NetworkWorker::sendCpuUsage()
{
	std::pair<int, int> memInfo[2];
	std::list<int> usage = system::CpuUsage::getCpuUsage();
	system::MemUsage::getMemUsage(memInfo[0], memInfo[1]);
	network::PeerInfo::stats st;

	for (auto i = usage.cbegin(); i != usage.cend(); i++)
		st.cpus.push_back((*i));
	getMe()->setStats(st);
	manager.broadcast(new network::Monitor(*(getMe())));
}

void NetworkWorker::connectToPeers()
{
	std::list<std::pair<std::string, unsigned short> >clients = manager.config()->getSection<drt::parser::PeerSection>()->getPeerlist();
	is_connected d(connectedPeers);

	if (time(nullptr) - lastConnectAtempt < 5)
		return;
	sendCpuUsage();
	lastConnectAtempt = time(nullptr);
	clients.remove_if(d);
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		std::pair<std::string, unsigned short> addr = (*i);
		network::PeerInfo *pi;

		try
		{
			pi = new network::PeerInfo(addr.first, addr.second);
		}
		catch (std::exception &e)
		{
			manager.log(std::cout, *this, "Unable to server: " +std::string(e.what()));
			continue;
		}

		manager.send(pi, new network::SAuth(-1, this->clients.size()));
		connectedPeers.push_back(std::pair<std::string, unsigned short> (*i));
		this->clients.push_back(pi);
		std::stringstream ss;
		ss << "Successfull connection to " << addr.first << ":" << addr.second;
		manager.log(std::cout, *this, ss.str());
	}
	std::stringstream ss;
	ss << "I'm " << this->getMe()->getId() << " - " << this->getMe()->getStats()->debug() << std::endl;
	for (auto i = this->clients.cbegin(); i != this->clients.cend(); i++)
		ss << "Client " << (*i)->getId() << " - " << (*i)->getStats()->debug() << std::endl;
	manager.log(std::cout, *this, ss.str());
}

void NetworkWorker::releasePeer(network::PeerInfo *peer)
{
	std::stringstream ss;

	ss << "Lost connection to " << peer->getConInfo().first << ":" << peer->getConInfo().second;
	clients.remove(peer);
	if (peer->isDirect())
		connectedPeers.remove(peer->getConInfo());
	manager.log(std::cout, *this, ss.str());
	delete peer;
}

void NetworkWorker::readAll()
{
	fd_set fdset;
	const network::Socket *biggerFd =nullptr;
	std::list<network::Socket *> discon;

	if (clients.size() == 0)
		return;
	FD_ZERO(&fdset);
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		if (!(*i)->isDirect())
			continue;
		(*i)->getSocket()->addToSet(&fdset);
		biggerFd = (*i)->getSocket()->greater(biggerFd);
	}
	if (biggerFd == nullptr || biggerFd->select(&fdset) <= 0)
		return;
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		if (!(*i)->getSocket()->isInSet(&fdset) || !(*i)->isDirect())
			continue;
		if ((*i)->getSocket()->isClosed())
		{
			if ((*i)->isClosing())
				discon.push_back((*i)->getSocket());
			else
			{
				discon.push_back((*i)->getSocket());
				manager.log(std::cout, *this, "client disconnected");
			}
		}
		else
		{
			try
			{
				this->readPeer((*i));
			}
			catch (std::exception &e)
			{
				discon.push_back((*i)->getSocket());
			}
		}
	}
	for (auto i = discon.cbegin(); i != discon.cend(); i++)
	{
		std::queue<network::PeerInfo *>dd;

		for (auto j = clients.cbegin(); j != clients.cend(); j++)
			if ((*j)->getSocket() == *i)
				dd.push(*j);
		while (dd.size())
		{
			manager.broadcast(new network::Netsplit(dd.front()->getId()));
			releasePeer(dd.front());
			dd.pop();
		}
	}
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

void NetworkWorker::sendAll()
{
	while (!manager.broadcastQueueEmpty())
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

			if (alreadySent.find((*i)->getSocket()) != alreadySent.end())
				continue;
			ss = packet->getStream(&packet_len);
			(*i)->sendData(*ss, packet_len);
			alreadySent.insert((*i)->getSocket());
			delete ss;
		}
		delete packet;
	}
	while (!manager.sendQueueEmpty())
	{
		network::PeerInfo *peer;
		network::ANetworkPacket *packet;
		std::stringstream *ss;
		size_t packet_len;

		manager.getNextSend(&packet, &peer);
		ss = packet->getStream(&packet_len);
		peer->sendData(*ss, packet_len);
		delete ss;
		delete packet;
	}
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


unsigned int NetworkWorker::nbClient() const
{ return clients.size(); }

drt::network::PeerInfo *NetworkWorker::getMe()
{ return myself; }

const std::list<drt::network::PeerInfo *> &NetworkWorker::getPeers() const
{ return clients; }

void NetworkWorker::nextOp(Operation *)
{ }

unsigned short NetworkWorker::incBiggerId()
{ return ++biggerId; }

