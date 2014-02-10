
#include <iostream>
#include "config/Config.hpp"

using namespace std;

int main(int ac, char **av)
{
	drt::ConfigParam params;

	params << new drt::ConfigParam::StringValue("test", "coucou", false);

	drt::Config *conf = new drt::Config(params, ac, av);
	if (!conf->isValid())
	{
		delete conf;
		return 1;
	}
	delete conf;
	return 0;
}

