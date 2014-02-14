#pragma once

namespace drt
{
class WorkerManager;
class Operation;

namespace worker
{
	class AWorker
	{
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
