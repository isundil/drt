#include <iostream>

#include <sstream>
#include "PeerSection.hpp"

using namespace drt::parser;

PeerSection::PeerSection()
{ }

PeerSection::PeerSection(const PeerSection &other)
{
	peerList = other.peerList;
}

PeerSection::~PeerSection()
{ }

void PeerSection::addParam(const std::string &name, const std::string &value)
{
	std::string ip;
	std::stringstream _port;
	unsigned short port;
	size_t portDelim;

	(void) name;

	portDelim = value.find(':');
	if (portDelim == std::string::npos)
	{
		ip = value;
		port = DEFAULT_PORT;
	}
	else
	{
		ip = value.substr(0, portDelim);
		_port.str(value.substr(portDelim +1));
		_port >> port;
		if (_port == 0)
		{
			std::cerr << "Warning: Invalid port: \"" << value.substr(portDelim +1) << "\". Ignoring." << std::endl;
			return;
		}
	}
	peerList.push_back(std::pair<std::string, unsigned short>(ip, port));
}

bool PeerSection::exists(const std::string &name) const
{
	return name == "Server";
}

ISection *PeerSection::clone() const
{
	return new PeerSection(*this);
}

