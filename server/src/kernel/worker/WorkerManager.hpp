#pragma once

#include <string>
#include <ostream>
#include <queue>
#include <list>
#include "worker/AWorker.hpp"

namespace drt
{
class Config;
namespace render
{
class Scene;
}
namespace module
{
class ModuleManager;
}
namespace worker
{
class NetworkWorker;
}
namespace network
{
class ANetworkPacket;
class Socket;
class PeerInfo;
}

class WorkerManager
{
	public:
		static WorkerManager *getSingleton();
		static WorkerManager *createInstance(drt::Config * const);

	public:
		virtual ~WorkerManager();

		bool isDone() const;
		worker::AWorker::Operation *pickNext();
		void addOperation(worker::AWorker::Operation *);
		void start();
		void stop();
		const drt::Config * config() const;

		// socket stuff
		void send(network::PeerInfo *peer, network::ANetworkPacket *packet);
		void send(worker::AWorker::Operation *op, unsigned int color);
		void broadcast(network::ANetworkPacket *packet, network::Socket *avoid = NULL); // change nullptr to NULL because of a compilation error
		void broadcast(network::ANetworkPacket *packet, network::PeerInfo *avoid);

		void log(std::ostream &channel, const worker::AWorker &sender, const std::string &msg);

		void removeScene(render::Scene *);
		void addScene(network::PeerInfo *, render::Scene *);
		bool getNextBroadcast(network::ANetworkPacket **packet, network::Socket **avoid);
		bool getNextSend(network::ANetworkPacket **packet, network::PeerInfo **dst);
		bool broadcastQueueEmpty();
		bool sendQueueEmpty();

		worker::NetworkWorker *getNetwork();

  module::ModuleManager	*getModuleManager();

	private:
		WorkerManager(drt::Config * const);
		WorkerManager(const WorkerManager &);

	private:
		std::list<worker::AWorker *> workers;
		std::list<render::Scene *> scenes;
		worker::AWorker *networkWorker;

		std::queue<worker::AWorker::Operation *>operationList;
		std::queue<std::pair<network::Socket *, network::ANetworkPacket *> >broadcastQueue;
		std::queue<std::pair<network::PeerInfo *, network::ANetworkPacket *> >sendQueue;
		drt::Config * const info;
		bool done;
		bool ready;

		module::ModuleManager *modules;

		pthread_mutex_t logMutex;
		pthread_mutex_t netMutex;
		pthread_mutex_t queueMutex;

	private:
		static WorkerManager *instance;
};
}

