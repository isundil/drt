#include <stdexcept>
#include <iostream>
#include "WorkerManager.hpp"
#include "Worker.hpp"
#include "NetworkWorker.hpp"
#include "config/Config.hpp"
#include "config/WorkerSection.hpp"
#include "modules/ModuleManager.hpp"
#include "network/NetworkPacket.hpp"
#include "network/PeerInfo.hpp"
#include "network/Socket.hpp"
#include "render/Scene.hpp"

using namespace drt;

WorkerManager::WorkerManager(drt::Config * const conf): info(conf), done(false)
{
	const unsigned int nbWorker = conf->getSection<drt::parser::WorkerSection>()->getMaxThread();

	modules = new module::ModuleManager();
	pthread_mutex_init(&logMutex, nullptr);
	pthread_mutex_init(&netMutex, nullptr);
	pthread_mutex_init(&queueMutex, nullptr);
	try
	{
		networkWorker = new worker::NetworkWorker(*this, 0);
		workers.push_back(networkWorker);
	}
	catch (std::runtime_error &e)
	{
		pthread_mutex_destroy(&logMutex);
		pthread_mutex_destroy(&netMutex);
		pthread_mutex_destroy(&queueMutex);
		std::cerr << "Fatal: cannot start server (" << e.what() << ")" << std::endl;
		throw e;
	}
	for (unsigned int i =0; i < nbWorker; i++)
		workers.push_back(new worker::Worker(*this, i +1));
}

WorkerManager::~WorkerManager()
{
	done = true;
	for (auto i = workers.begin(); i != workers.end(); i++)
	{
		(*i)->stop();
		delete (*i);
	}
	delete info;
	delete modules;
	pthread_mutex_destroy(&logMutex);
	pthread_mutex_destroy(&netMutex);
	pthread_mutex_destroy(&queueMutex);
}

WorkerManager *WorkerManager::getSingleton()
{ return WorkerManager::instance; }

const drt::Config * WorkerManager::config() const
{ return info; }

void WorkerManager::stop()
{
	done = true;
}

void WorkerManager::start()
{
	if (this == nullptr)
		return;
	networkWorker->start();
}

WorkerManager *WorkerManager::createInstance(Config * const infos)
{
	try
	{
		WorkerManager::instance = new WorkerManager(infos);
	}
	catch (std::runtime_error &e)
	{
		WorkerManager::instance = nullptr;
	}
	return WorkerManager::getSingleton();
}

bool WorkerManager::isDone() const
{ return done; }

void WorkerManager::addOperation(worker::AWorker::Operation *next)
{
	pthread_mutex_lock(&queueMutex);
	operationList.push_back(next);
	ready = false;
	pthread_mutex_unlock(&queueMutex);
}

worker::AWorker::Operation *WorkerManager::pickNext(const worker::AWorker *thread)
{
	pthread_mutex_lock(&queueMutex);
	if (operationList.size() == 0)
	{
		ready = true;
		pthread_mutex_unlock(&queueMutex);
		return nullptr;
	}
	worker::AWorker::Operation *next = operationList.front();
	operationList.erase(operationList.begin());
	unsigned int r = runningOp.size();
	runningOp[thread] = next;
	pthread_mutex_unlock(&queueMutex);
	return next;
}

void WorkerManager::releaseThread(const worker::AWorker *w)
{
	runningOp[w] = nullptr;
}

void WorkerManager::log(std::ostream &out, const worker::AWorker &sender, const std::string &message)
{
	pthread_mutex_lock(&logMutex);
	if (sender.getId() > 0)
		out << "Thread " << sender.getId() << ": " << message << std::endl;
	else
		out << "[network]: " << message << std::endl;
	pthread_mutex_unlock(&logMutex);
}

void WorkerManager::broadcast(network::ANetworkPacket *packet, network::PeerInfo *avoid)
{
	if (avoid == nullptr)
		return broadcast(packet);
	return broadcast(packet, avoid->getSocket());
}

void WorkerManager::broadcast(network::ANetworkPacket *packet, network::Socket *avoid)
{
	pthread_mutex_lock(&netMutex);
	broadcastQueue.push(std::pair<network::Socket *, network::ANetworkPacket *>(avoid, packet));
	pthread_mutex_unlock(&netMutex);
}

void WorkerManager::send(network::PeerInfo *peer, network::ANetworkPacket *packet)
{
	pthread_mutex_lock(&netMutex);
	sendQueue.push(std::pair<network::PeerInfo *, network::ANetworkPacket *>(peer, packet));
	pthread_mutex_unlock(&netMutex);
}

void WorkerManager::send(worker::AWorker::Operation *op, unsigned int result)
{
	return this->send(op->client, new network::Result(op->client->getId(), op->x, op->y, result));
}

bool WorkerManager::getNextBroadcast(network::ANetworkPacket **packet, network::Socket **avoid)
{
	if (broadcastQueueEmpty())
		return false;
	pthread_mutex_lock(&netMutex);
	auto i = broadcastQueue.front();
	broadcastQueue.pop();
	*packet = i.second;
	*avoid = i.first;
	pthread_mutex_unlock(&netMutex);
	return true;
}

bool WorkerManager::getNextSend(network::ANetworkPacket **packet, network::PeerInfo **dst)
{
	if (sendQueueEmpty())
		return false;
	pthread_mutex_lock(&netMutex);
	auto i = sendQueue.front();
	sendQueue.pop();
	*packet = i.second;
	*dst = i.first;
	pthread_mutex_unlock(&netMutex);
	return true;
}

bool WorkerManager::broadcastQueueEmpty()
{
	bool r;

	pthread_mutex_lock(&netMutex);
	r = broadcastQueue.size() == 0;
	pthread_mutex_unlock(&netMutex);
	return r;
}

bool WorkerManager::sendQueueEmpty()
{
	bool r;

	pthread_mutex_lock(&netMutex);
	r = sendQueue.size() == 0;
	pthread_mutex_unlock(&netMutex);
	return r;
}

void WorkerManager::releaseScene(render::Scene *s)
{
	bool contains = false;
	std::list<worker::AWorker::Operation *> rem;

	if (!s)
		return;
	::pthread_mutex_lock(&queueMutex);
	for (auto i = runningOp.cbegin(); i != runningOp.cend() && !contains; i++)
		if ((*i).second && (*i).second->scene == s)
			contains = true;
	if (contains)
	{
		std::cout << "running scene " <<std::endl;
		endedScenes.push_back(s);
	}
	else
	{
		std::cout << "not running scene " <<std::endl;
		delete s;
	}
	for (auto i = operationList.cbegin(); i != operationList.cend(); i++)
		if ((*i)->scene == s)
			rem.push_back(*i);
	for (auto i = rem.cbegin(); i != rem.cend(); i++)
		operationList.remove(*i);
	scenes.remove(s);
	::pthread_mutex_unlock(&queueMutex);
}

void WorkerManager::addScene(network::PeerInfo *pi, render::Scene *s)
{
	scenes.push_back(s);

	for (unsigned int x =0; x < s->getWidth(); x++)
		for (unsigned int y =0; y < s->getHeight(); y++)
			operationList.push_back(new worker::AWorker::Operation(pi, s, x, y));
}

worker::NetworkWorker *WorkerManager::getNetwork()
{ return (worker::NetworkWorker *) networkWorker; }

WorkerManager *WorkerManager::instance;

module::ModuleManager	*WorkerManager::getModuleManager()
{
  return modules;
}
