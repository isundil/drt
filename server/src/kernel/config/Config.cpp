#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include "Config.hpp"
#include "UnixParser.hpp"

using namespace drt;

Config::Config(ConfigParam &c): usage(c), valid(true)
{
}

Config::~Config()
{
	for (auto i = infos.cbegin(); i != infos.cend(); i++)
		delete (*i);
}

template <class T> void Config::eval(int ac, char **av)
{
	if (parseParam(ac, av))
	{
		try
		{
			parseFile<T>();
		}
		catch (std::exception &e)
		{
			valid = false;
			std::cerr << "Failed to parse file: " << e.what() << std::endl;
		}
	}
	else
		printUsage();
}

void Config::printUsage() const
{
	std::list<ConfigParam::IValue *> l = this->usage.getItems();

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

template <class Parser>
void Config::parseFile()
{
	drt::ConfigParam::StringValue *configFile = dynamic_cast<drt::ConfigParam::StringValue *>(usage.get("config-file"));
	std::ifstream in;

	in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		in.open(configFile->getValue().c_str());
	}
	catch (std::ifstream::failure &e)
	{
		throw std::runtime_error("Failed opening file");
	}
	Parser *p = new Parser();
	p->parseFile(in);
	infos = p->getSections();
	delete p;
	in.close();
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
#warning "Unimplemented method"
	//TODO parse
	(void)str;
	return true;
}

template void drt::Config::eval<drt::parser::UnixParser>(int, char**);

