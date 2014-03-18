#include <stdexcept>
#include <iostream>
#include <sys/socket.h>
#include "network/PeerInfo.hpp"
#include "network/Socket.hpp"
#include "network/NetworkPacket.hpp"
#include "worker/WorkerManager.hpp"
#include "worker/NetworkWorker.hpp"
#include "render/Scene.hpp"

using namespace drt::network;

PeerInfo::PeerInfo(const std::string &_ip, unsigned short _port): PeerInfo(new Socket(_ip, _port), true, -1)
{
	ip = _ip;
	port = _port;
}

PeerInfo::PeerInfo(Socket *s, bool _direct, unsigned short _id): ip(""), port(0), closing(true), socket(s), id(_id), oldId(_id), direct(_direct), procInfo(nullptr), isClient(false), scene(nullptr), confirmed(0)
{
	if (_id != 0xffff && s)
		drt::WorkerManager::getSingleton()->getNetwork()->changeBiggerId(_id);
}

PeerInfo::~PeerInfo()
{
	if (socket && isDirect())
		delete socket;
	if (procInfo)
		delete procInfo;
	if( scene )
		delete scene;
}

Socket *PeerInfo::getSocket() const
{ return socket; }

bool PeerInfo::isClosing() const
{ return closing; }

void PeerInfo::read(WorkerManager &manager)
{
	char code;
	ANetworkPacket *packet;

	(void) manager;

	code = socket->getc();
	try
	{
		packet = ANetworkPacket::fromSocket(code, socket);
	}
	catch (network::CompilFail &e)
	{
		e.setId(id);
		manager.send(this, new CompilFail(e));
		return;
	}
	if (packet == nullptr)
	{
		std::stringstream ss;
		ss << "Fatal: invalid packet detected (code " << (int)code << ")" << std::endl;
		manager.log(std::cerr, *(manager.getNetwork()), ss.str());
		throw std::runtime_error("Invalid packet type");
	}
	if (dynamic_cast<SAuth *> (packet) == nullptr && dynamic_cast<Welcome *> (packet) == nullptr && dynamic_cast<IdCh *> (packet) == nullptr && dynamic_cast<Confirm *> (packet) == nullptr && getConfirmed())
	{
		std::cerr << "Packet " << packet->getName() << "dropped" << std::endl;
		delete packet;
		return;
	}
	std::cerr << "Packet in (" << manager.getNetwork()->getMe()->getId() << "): " << packet->getName() << std::endl;
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
	drt::WorkerManager::getSingleton()->getNetwork()->changeBiggerId(_id);
}

void
PeerInfo::setClient()
{
	isClient = true;
}

bool PeerInfo::isAClient() const
{ return isClient; }

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

int PeerInfo::getConfirmed() const
{ return confirmed; }

void PeerInfo::setConfirmed(int value)
{ confirmed = value < 0 ? 0 : value; }

bool PeerInfo::decConfirm()
{ return (--confirmed) <= 0; }

void PeerInfo::stats::copy(const PeerInfo::stats &o)
{
	cpus = o.cpus;
	ram = o.ram;
	maxRam = o.maxRam;
	swap = o.swap;
	maxSwap = o.maxSwap;
}

std::string PeerInfo::stats::debug() const
{
	std::stringstream ss;

	if (this == nullptr)
		return "no data";
	int num =0;
	for (auto i = cpus.cbegin(); i != cpus.cend(); i++)
		ss << "cpu" << num++ << ": " << (100 * (*i)) / 255 << "% | ";
	ss << " mem: " << ram << "/" << maxRam << " | " << swap << "/" << maxSwap;
	return ss.str();
}

void
PeerInfo::setScene( render::Scene *s )
{
	if (scene)
		delete scene;
	this -> scene = s;
}

drt::render::Scene*
PeerInfo::getScene( )
{
	return this -> scene;
}
