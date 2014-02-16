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

		private:
			drt::network::ServerSocket * server;
			std::list<std::pair<std::string, unsigned short> >connectedPeers;
			std::list <drt::network::PeerInfo *> clients;
			drt::network::PeerInfo *myself;
			unsigned short biggerId;

			void acceptNew();
			void connectToPeers();
			void readAll();
	};
}
}
