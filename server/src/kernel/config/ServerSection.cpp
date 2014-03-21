#include <iostream>
#include <stdexcept>
#include <sstream>
#include "ServerSection.hpp"

using namespace drt::parser;

ServerSection::ServerSection(unsigned short _port): port(0), maxClient((unsigned int) -1), maxClient_set(false), noListen(false), realPort(_port)
{ }

ServerSection::ServerSection(const ServerSection &o): port(o.port), maxClient(o.maxClient), maxClient_set(o.maxClient_set), noListen(o.noListen), realPort(o.realPort)
{ }

ServerSection::~ServerSection()
{ }

void ServerSection::addParam(const std::string &name, const std::string &value)
{
	std::istringstream ss;

	ss.str(value);
	if (name == "Listen")
	{
		if (port != 0)
		{
			std::cerr << "Warning: duplicate entry \"Listen\". Ignoring" << std::endl;
			return;
		}
		ss >> this->port;
		if (port == 0)
		{
			std::cerr << "Fatal: invalid port (" << value << "). Aborting" << std::endl;
			throw std::runtime_error("Parse error");
		}
	}
	else if (name == "MaxClient")
	{
		if (maxClient_set)
		{
			std::cerr << "Warning: duplicate entry \"MaxClient\". Ignoring" << std::endl;
			return;
		}
		if ((value[0] < '0' || value[0] > '9') && value != "unlimited")
		{
			std::cerr << "Fatal: invalid number: MaxClient (" << value << "). Aborting" << std::endl;
			throw std::runtime_error("Parse error");
		}
		else if (value == "unlimited")
			maxClient = (unsigned int) -1;
		else
			ss >> this->maxClient;
		maxClient_set = true;
	}
	else
	{
		if (noListen)
		{
			std::cerr << "Warning: duplicate entry \"Listen\". Ignoring" << std::endl;
			return;
		}
		noListen = true;
	}
}

bool ServerSection::exists(const std::string &name) const
{
	return name == "Listen" || name == "MaxClient" || name == "NoListen";
}

unsigned short ServerSection::getPort() const
{
	if (realPort)
		return realPort;
	return port == 0 ? DEFAULT_PORT : port;
}

unsigned int ServerSection::getMaxClient() const
{ return maxClient; }

bool ServerSection::enabled() const
{ return !noListen; }

ISection *ServerSection::clone() const
{
	return new ServerSection(*this);
}

