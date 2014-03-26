#pragma once

#include <set>
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
class ClientMonitor;
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

			void changeBiggerId(unsigned short);
			unsigned short incBiggerId();
			void setMax(unsigned short max);
			drt::network::PeerInfo *getMe();
			drt::network::PeerInfo *getPeer(unsigned short id);
			const std::list<drt::network::PeerInfo *>&getPeers() const;
			const std::list<drt::network::PeerInfo *>getSrv() const;
			void removeLastPeer();

			void sendConnected(drt::network::PeerInfo *p);

			unsigned int nbClient() const;
			unsigned int nbSocket(network::Socket *avoid =nullptr) const;
			drt::network::PeerInfo *addServer(network::Socket *sock, unsigned short id =0);

			void rmPeer(network::PeerInfo *peer);
			void confirm();

		private:
			drt::network::ServerSocket * server;
			std::list<std::pair<std::string, unsigned short> >connectedPeers;
			std::list<std::pair<std::string, unsigned short> >blackListedPeers;
			std::list <drt::network::PeerInfo *> clients;
			network::PeerInfo * connectingTo;
			std::set<drt::network::PeerInfo *> discon;
			drt::network::PeerInfo *myself;
			unsigned short biggerId;

			time_t lastConnectAtempt;

			void releasePeer(network::PeerInfo *i);

			void sendCpuUsage();
			network::ClientMonitor *getAvgUsage() const;
			bool acceptNew();
			bool connectToPeers();
			bool readAll();
			bool sendAll();
			bool sendBroadcast();
			bool sendUnique();
			void readPeer(network::PeerInfo *);
	};
}
}
