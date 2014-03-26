#include <iostream>
#include <sstream>
#include "worker/Worker.hpp"
#include "worker/WorkerManager.hpp"
#include "render/Scene.hpp"
#include "network/NetworkPacket.hpp"

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
	std::list<drt::network::Result *>rList;
	render::Scene *const s = op->scene;
	unsigned int color = 0xFFFFFF;
	const int maxX = op->x +op->width;
	const int maxY = op->y +op->height;

	if (!s)
		return;
	for (int i = op->x; i < maxX; i++)
		for (int j = op->y; j < maxY; j++)
		{
			color = s->calc(manager, i, j);
			color |= 0xff000000;
			rList.push_back(new drt::network::Result(s->getId(), i, j, color));
		}
	for (auto i = rList.cbegin(); i != rList.cend(); i++)
		manager.send(op->client, (*i));
}

unsigned int Worker::getId() const
{
	return id;
}

