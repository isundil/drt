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
			virtual void nextOp(Operation *); //Do nothing
			virtual void start(); // Do network listen
			virtual void stop(); //close sockets

		private:
			drt::network::ServerSocket * server;
			std::list <drt::network::PeerInfo *> clients;

			void readAll();
	};
}
}
