#pragma once

namespace drt
{
class WorkerManager;
namespace render
{
class Scene;
}

namespace worker
{
	class AWorker
	{
		public:
			struct Operation
			{
				render::Scene *scene;
				unsigned int x;
				unsigned int y;

			public:
				Operation(render::Scene *s, unsigned int _x, unsigned int _y): scene(s), x(_x), y(_y)
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
