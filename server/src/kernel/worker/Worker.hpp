#pragma once

#include <pthread.h>
#include "worker/AWorker.hpp"

namespace drt
{
class WorkerManager;

namespace worker
{
class Worker: public AWorker
	{
		public:
			Worker(WorkerManager &manager, unsigned int id);
			virtual void nextOp(Operation *);
			virtual void stop();

			unsigned int getId() const;

			void listen();

		private:
			pthread_t thread_handler;
	};
}
}
