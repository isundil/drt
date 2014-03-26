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
				unsigned char width;
				unsigned char height;

			public:
				Operation(network::PeerInfo *pi, render::Scene *s, unsigned int _x, unsigned int _y, unsigned char _w, unsigned char _h): client(pi), scene(s), x(_x), y(_y), width(_w), height(_h)
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
