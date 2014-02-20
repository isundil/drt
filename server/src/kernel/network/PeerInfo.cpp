#include <stdexcept>
#include <iostream>
#include <sys/socket.h>
#include "network/PeerInfo.hpp"
#include "network/Socket.hpp"
#include "network/NetworkPacket.hpp"
#include "worker/WorkerManager.hpp"
#include "worker/NetworkWorker.hpp"

using namespace drt::network;

PeerInfo::PeerInfo(const std::string &_ip, unsigned short _port): PeerInfo(new Socket(_ip, _port), true, -1)
{
	ip = _ip;
	port = _port;
}

PeerInfo::PeerInfo(Socket *s, bool _direct, unsigned short _id): ip(""), port(0), closing(true), socket(s), id(_id), oldId(_id), direct(_direct), procInfo(nullptr)
{ }

PeerInfo::~PeerInfo()
{
	if (socket && isDirect())
		delete socket;
	if (procInfo)
		delete procInfo;
}

Socket *PeerInfo::getSocket() const
{
	return socket;
}

bool PeerInfo::isClosing() const
{
	return closing;
}

void PeerInfo::read(WorkerManager &manager)
{
	char code;

	(void) manager;

	code = socket->getc();
	ANetworkPacket *packet = ANetworkPacket::fromSocket(code, socket);
	if (packet == nullptr)
	{
		std::stringstream ss;
		ss << "Fatal: invalid packet detected (code " << (int)code << ")" << std::endl;
		manager.log(std::cerr, *(manager.getNetwork()), ss.str());
		throw std::runtime_error("Invalid packet type");
	}
	packet->doMagic(manager, this);
	delete packet;
}

void PeerInfo::sendData(std::stringstream &ss, size_t len)
{
	char buffer[512];
	size_t current_pos = 0;

	while (current_pos < len)
	{
		ss.read(buffer, ((len - current_pos > 512) ? 512 : len - current_pos));
		socket->write(buffer, ((len - current_pos > 512) ? 512 : len - current_pos));
		current_pos += ((len - current_pos > 512) ? 512 : len - current_pos);
	}
}

std::pair<std::string, unsigned short> PeerInfo::getConInfo() const
{ return std::pair<std::string, unsigned short>(ip, port); }

void PeerInfo::setId(unsigned short _id)
{
	std::cout << "New id: " << id << "->" << _id << std::endl;
	oldId = id;
	id = _id;
}

void PeerInfo::setStats(const PeerInfo::stats &stats)
{
	if (procInfo == nullptr)
		procInfo = new PeerInfo::stats();
	procInfo->copy(stats);
}

const PeerInfo::stats *PeerInfo::getStats() const
{ return procInfo; }

bool PeerInfo::isDirect() const
{ return direct; }

unsigned short PeerInfo::getOldId() const
{ return oldId; }

unsigned short PeerInfo::getId() const
{ return id; }

PeerInfo *PeerInfo::getMe()
{ return new PeerInfo((Socket *)nullptr, false, 1); }

void PeerInfo::stats::copy(const PeerInfo::stats &o)
{
	cpus = o.cpus;
	ram = o.ram;
	maxRam = o.maxRam;
}

std::string PeerInfo::stats::debug() const
{
	std::stringstream ss;

	if (this == nullptr)
		return "no data";
	int num =0;
	for (auto i = cpus.cbegin(); i != cpus.cend(); i++)
		ss << "cpu" << num++ << ": " << (100 * (*i)) / 255 << "% | ";
	return ss.str();
}

