#pragma once
#include <set>
#include <list>
#include "AWorker.hpp"

#ifndef  COMPUTE_SQUARE
# define COMPUTE_SQUARE (1)
#endif

namespace drt
{
class WorkerManager;
namespace network
{
class PeerInfo;
}
namespace render
{
class Scene;
}

	namespace worker
{
class ManagedScene
{
	public:
		ManagedScene(WorkerManager &manager, network::PeerInfo *client, render::Scene *scene);
		~ManagedScene();

		void removePeer(unsigned short id);
		void removePeer(const drt::network::PeerInfo *pi);

		void compilFail(const drt::network::PeerInfo *pi);

		bool operator==(const render::Scene &) const;

		bool ready(drt::network::PeerInfo *);

	private:
		std::set<drt::network::PeerInfo *> elligiblePeers;
		WorkerManager &manager;
		network::PeerInfo *peer;
		render::Scene *scene;

		std::pair<drt::network::PeerInfo *, bool> **pixels;
		unsigned short px, py;
		bool done;

	private:
		worker::AWorker::Operation *getNextOp();
};
}
}

