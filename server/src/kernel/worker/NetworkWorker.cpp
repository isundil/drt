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

	clients.remove_if(d);
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

void NetworkWorker::nextOp(Operation *)
{ }

