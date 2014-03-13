#pragma once

namespace drt
{
class WorkerManager;
namespace render
{
class Scene;
}
namespace network
{
class PeerInfo;
}

namespace worker
{
	class AWorker
	{
		public:
			struct Operation
			{
				network::PeerInfo *client;
				render::Scene *scene;
				unsigned int x;
				unsigned int y;

			public:
				Operation(network::PeerInfo *pi, render::Scene *s, unsigned int _x, unsigned int _y): client(pi), scene(s), x(_x), y(_y)
				{ };
			};

		public:
			AWorker(drt::WorkerManager &manager, unsigned int id);
			virtual ~AWorker() { };
			virtual void start();
			virtual void stop() =0;

			unsigned int getId() const;

		protected:
			virtual void nextOp(Operation *) =0;

		protected:
			drt::WorkerManager &manager;
			bool readyState;
			const unsigned int id;
	};
}
}
