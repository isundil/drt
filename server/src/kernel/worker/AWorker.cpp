#include <iostream>
#include <unistd.h>
#include "worker/AWorker.hpp"
#include "worker/WorkerManager.hpp"

using namespace drt::worker;

AWorker::AWorker(drt::WorkerManager &a, unsigned int _id): manager(a), readyState(false), id(_id)
{ }

void AWorker::start()
{
	manager.log(std::cout, *this, "Started thread");
	while (!manager.isDone())
	{
		Operation *current = manager.pickNext(this);
		if (current)
		{
			this->nextOp(current);
			manager.releaseThread(this);
			delete current;
		}
		else
			usleep(750);
	}
	manager.log(std::cout, *this, "Thread exited");
}

unsigned int AWorker::getId() const
{
	return id;
}

