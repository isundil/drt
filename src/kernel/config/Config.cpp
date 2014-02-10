#include <iostream>
#include <fstream>
#include "Config.hpp"

using namespace drt;

Config::Config(ConfigParam &c, int ac, char **av): usage(c), progName(*av), configFile(DEFAULT_CONFIG), valid(true)
{
	if (parseParam(ac, av))
		parseFile();
	else
		printUsage();
}

void Config::printUsage() const
{
	std::list<ConfigParam::IValue *> l;

	std::cerr << "Usage: " << progName;
	for (auto _i = l.cbegin(); _i != l.cend(); _i++)
	{
		ConfigParam::IValue *i = (*_i);
		std::cerr << " ";
		if (!i->isMendatory())
			std::cerr << "[";
		std::cerr << (i->isShortcut() ? "-" : "--") << i->getName();
		if (!i->isMendatory())
		{
			std::cerr << "(=" << i->getDefault() << ")]";
		}
	}
	std::cerr << std::endl;
}

bool Config::isValid() const
{ return valid; }

bool Config::parseParam(int ac, char **av)
{
	for (int i=1; i < ac; i++)
	{
		if (av[i][0] == '-' && av[i][1] == '-')
		{
			int result;

			if ((result = parseParamFull(&av[i])) == -1)
				return false;
			else if (result == 1)
				i++;
		}
		else if (av[i][0] == '-')
		{
			if (!parseParamShort(av[i] +1))
				return false;
		}
		else
		{
			std::cerr << "Unrecognized parameter: " << av[i] << std::endl;
			return false;
		}
	}
	return true;
}

bool Config::parseFile()
{
	std::ifstream in(configFile.c_str());
	if (in.is_open() == false)
	{
		valid = false;
		return false;
	}
	//TODO parse file
	in.close();
	return true;
}

int Config::parseParamFull(char **str)
{
	ConfigParam::IValue *p = usage.get(std::string(*str +2));

	if (p == nullptr)
	{
		std::cerr << "Unrecognized parameter: " << *str << std::endl;
		return -1;
	}
	if (dynamic_cast<ConfigParam::StringValue *> (p) != nullptr)
	{
		if (*(str +1) == nullptr)
		{
			std::cerr << "Missing argument after: " << *str << std::endl;
			return -1;
		}
		((ConfigParam::StringValue *)p)->setValue(std::string(*(str +1)));
		return 1;
	}
	else if (dynamic_cast<ConfigParam::BooleanValue *> (p) != nullptr)
		((ConfigParam::BooleanValue *)p)->setValue(true);
	return 0;
}

bool Config::parseParamShort(char *str)
{
	return true;
}

