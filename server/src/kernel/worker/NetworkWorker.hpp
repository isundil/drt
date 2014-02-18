#pragma once

#include <list>
#include "worker/AWorker.hpp"

namespace drt
{
class WorkerManager;
namespace network
{
class PeerInfo;
class ServerSocket;
class Socket;
}

namespace worker
{
class NetworkWorker: public AWorker
	{
		public:
			NetworkWorker(WorkerManager &manager, unsigned int id);
			~NetworkWorker();
			virtual void nextOp(Operation *); //Do nothing
			virtual void start(); // Do network listen
			virtual void stop(); //close sockets

			unsigned short incBiggerId();
			void setMax(unsigned short max);
			drt::network::PeerInfo *getMe();
			drt::network::PeerInfo *getPeer(unsigned short id);
			const std::list<drt::network::PeerInfo *>getPeers() const;

			void sendConnected(drt::network::PeerInfo *p);

			unsigned int nbClient() const;
			drt::network::PeerInfo *addServer(network::Socket *sock, unsigned short id =0);

		private:
			drt::network::ServerSocket * server;
			std::list<std::pair<std::string, unsigned short> >connectedPeers;
			std::list <drt::network::PeerInfo *> clients;
			drt::network::PeerInfo *myself;
			unsigned short biggerId;

			time_t lastConnectAtempt;

			void acceptNew();
			void connectToPeers();
			void readAll();
			void sendAll();
			void readPeer(network::PeerInfo *);
	};
}
}
