#include "worker/Worker.hpp"
#include "worker/WorkerManager.hpp"
#include "render/Scene.hpp"

using namespace drt::worker;

static void *startThread(void *i)
{
	Worker *instance = (Worker *)i;
	instance->start();
	return nullptr;
}

Worker::Worker(drt::WorkerManager &_manager, unsigned int _id): AWorker(_manager, _id)
{
	pthread_create(&thread_handler, nullptr, startThread, this);
}

void Worker::stop()
{
	pthread_join(thread_handler, nullptr);
}

void Worker::nextOp(Operation *op)
{
	render::Scene * const s = op->scene;
	unsigned int color = 0xFFFFFF;

	if (s)
	{
		color = s->calc(manager, op->x, op->y);
		color |= 0xff000000;
		//color = rand(); //s->calc(manager, op->x, op->y);
		//char *c = (char *)&color;
		//c[0] = 0xff;
		//c[1] = rand() % 255;
		//c[2] = rand() % 255;
		//c[3] = rand() % 255;
	}
	manager.send(op, color);
}

unsigned int Worker::getId() const
{
	return id;
}

