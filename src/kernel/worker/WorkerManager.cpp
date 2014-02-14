#include <stdexcept>
#include <iostream>
#include "WorkerManager.hpp"
#include "Worker.hpp"
#include "NetworkWorker.hpp"
#include "config/Config.hpp"
#include "config/WorkerSection.hpp"
#include "modules/ModuleManager.hpp"

using namespace drt;

WorkerManager::WorkerManager(drt::Config * const conf): info(conf), done(false)
{
	const unsigned int nbWorker = conf->getSection<drt::parser::WorkerSection>()->getMaxThread();

	modules = new module::ModuleManager();
	pthread_mutex_init(&logMutex, nullptr);
	pthread_mutex_init(&queueMutex, nullptr);
	try
	{
		workers.push_back(new worker::NetworkWorker(*this, 0));
	}
	catch (std::runtime_error &e)
	{
		pthread_mutex_destroy(&logMutex);
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
	(*workers.begin())->start();
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

void WorkerManager::addOperation(Operation *next)
{
	pthread_mutex_lock(&queueMutex);
	operationList.push(next);
	ready = false;
	pthread_mutex_unlock(&queueMutex);
}

Operation *WorkerManager::pickNext()
{
	pthread_mutex_lock(&queueMutex);
	if (operationList.size() == 0)
	{
		ready = true;
		pthread_mutex_unlock(&queueMutex);
		return nullptr;
	}
	Operation *next = operationList.front();
	operationList.pop();
	pthread_mutex_unlock(&queueMutex);
	return next;
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

WorkerManager *WorkerManager::instance;

