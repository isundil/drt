#pragma once

#include <string>
#include <ostream>
#include <queue>
#include <list>

namespace drt
{
class Config;
class Operation;
namespace module
{
class ModuleManager;
}
namespace worker
{
class AWorker;
}

class WorkerManager
{
	public:
		static WorkerManager *getSingleton();
		static WorkerManager *createInstance(drt::Config * const);

	public:
		virtual ~WorkerManager();

		bool isDone() const;
		Operation *pickNext();
		void addOperation(Operation *);
		void start();
		void stop();
		const drt::Config * config() const;

		void log(std::ostream &channel, const worker::AWorker &sender, const std::string &msg);

	private:
		WorkerManager(drt::Config * const);
		WorkerManager(const WorkerManager &);

	private:
		std::list<worker::AWorker *> workers;
		std::queue<Operation *>operationList;
		drt::Config * const info;
		bool done;
		bool ready;

		module::ModuleManager *modules;

		pthread_mutex_t logMutex;
		pthread_mutex_t queueMutex;

	private:
		static WorkerManager *instance;
};
}

