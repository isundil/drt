#include <set>
#include <sstream>
#include <iostream>
#include <sys/ioctl.h>
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
	}
}

void NetworkWorker::acceptNew()
{
	if (server != nullptr)
	{
		drt::network::Socket *s = server->accept();
		if (s)
		{
			clients.push_back(new drt::network::PeerInfo(s));
			manager.log(std::cout, *this, "new client");
		}
	}
}

void NetworkWorker::connectToPeers()
{
	std::list<std::pair<std::string, unsigned short> >clients = manager.config()->getSection<drt::parser::PeerSection>()->getPeerlist();
	is_connected d(connectedPeers);

	if (time(nullptr) - lastConnectAtempt < 5)
		return;
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
	ss << "I'm " << this->getMe()->getId() << std::endl;
	for (auto i = this->clients.cbegin(); i != this->clients.cend(); i++)
		ss << "Client " << (*i)->getId() << std::endl;
	manager.log(std::cout, *this, ss.str());
}

void NetworkWorker::readAll()
{
	fd_set fdset;
	int closed;
	int biggerFd =-1;
	struct timeval timeout = { 0, 0 };
	std::list<network::PeerInfo *> discon;

	FD_ZERO(&fdset);
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		FD_SET((*i)->getSocket()->getSocketNumber(), &fdset);
		biggerFd = (biggerFd < (*i)->getSocket()->getSocketNumber()) ? (*i)->getSocket()->getSocketNumber() : biggerFd;
	}
	if (select(biggerFd +1, &fdset, nullptr, nullptr, &timeout) <= 0)
		return;
	for (auto i = clients.cbegin(); i != clients.cend(); i++)
	{
		if (!FD_ISSET((*i)->getSocket()->getSocketNumber(), &fdset))
			continue;
		ioctl((*i)->getSocket()->getSocketNumber(), FIONREAD, &closed);
		if (closed == 0)
		{
			if ((*i)->isClosing())
				discon.push_back(*i);
			else
			{
				//TODO manager.broadcast(message::Netsplit((*i)));
				discon.push_back(*i);
				manager.log(std::cout, *this, "client disconnected");
			}
		}
		else
			this->readPeer((*i));
	}
	for (auto i = discon.cbegin(); i != discon.cend(); i++)
	{
		clients.remove(*i);
		connectedPeers.remove((*i)->getConInfo());
		std::stringstream ss;
		ss << "Lost connection to " << (*i)->getConInfo().first << ":" << (*i)->getConInfo().second;
		manager.log(std::cout, *this, ss.str());
		delete *i;
	}
}

void NetworkWorker::readPeer(network::PeerInfo *peer)
{
	try
	{
		peer->read(manager);
	}
	catch (std::exception &e)
	{
#warning "TODO"
		//TODO netsplit
	}
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
		int avoid;
		network::ANetworkPacket *packet;
		std::set<unsigned int> alreadySent;

		manager.getNextBroadcast(&packet, &avoid);
		alreadySent.insert(avoid);
		for (auto i = clients.begin(); i != clients.end(); i++)
		{
			std::stringstream *ss;
			size_t packet_len;

			if (alreadySent.find((*i)->getSocket()->getSocketNumber()) != alreadySent.end())
				continue;
			ss = packet->getStream(&packet_len);
			(*i)->sendData(*ss, packet_len);
			alreadySent.insert((*i)->getSocket()->getSocketNumber());
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
	return;
	for (auto i =clients.cbegin(); i != clients.cend(); i++)
	{
		//TODO
		//if ((*i)->isReady)
		//	manager.send(p, new network::Ready((*i)->getId()));
	}
}

drt::network::PeerInfo *NetworkWorker::addServer(drt::network::Socket *s, unsigned short id)
{
	if (id == 0)
		id = incBiggerId();
	drt::network::PeerInfo *pi = new network::PeerInfo(s, id);
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

const std::list<drt::network::PeerInfo *> NetworkWorker::getPeers() const
{ return clients; }

void NetworkWorker::nextOp(Operation *)
{ }

unsigned short NetworkWorker::incBiggerId()
{ return ++biggerId; }

