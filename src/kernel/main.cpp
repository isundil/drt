#include <unistd.h>

#include <iostream>
#include <signal.h>
#include "config/Config.hpp"
#include "config/UnixParser.hpp"
#include "worker/WorkerManager.hpp"

using namespace std;

void *clean(int)
{
	std::cout << "Caught ^C, starting clean..." << std::endl;
	if (drt::WorkerManager::getSingleton())
		drt::WorkerManager::getSingleton()->stop();
	else
		kill(0, SIGKILL);
	return nullptr;
}

int main(int ac, char **av)
{
	drt::ConfigParam params;
	drt::Config *conf;

	params << drt::ConfigParam::StringValue("config-file", "server.conf", false);

	conf = new drt::Config(params);
	conf->eval<drt::parser::UnixParser>(ac, av);
	if (!conf->isValid())
	{
		delete conf;
		return 1;
	}
	signal(SIGINT, (__sighandler_t)clean);
	drt::WorkerManager::createInstance(conf)->start();
	delete drt::WorkerManager::getSingleton();
	std::cout << "Cleaning done." << std::endl;
	return 0;
}

