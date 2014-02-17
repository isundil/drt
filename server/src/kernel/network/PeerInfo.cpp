#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include "network/PeerInfo.hpp"
#include "network/Socket.hpp"
#include "network/NetworkPacket.hpp"
#include "worker/WorkerManager.hpp"

using namespace drt::network;

PeerInfo::PeerInfo(const std::string &ip, unsigned short port): PeerInfo(new Socket(ip, port), -1)
{ }

PeerInfo::PeerInfo(Socket *s, unsigned short _id): closing(true), socket(s), id(_id)
{ }

PeerInfo::~PeerInfo()
{
	if (socket)
		delete socket;
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

	::fread(&code, sizeof(code), 1, socket->getSocket());
	ANetworkPacket *packet = ANetworkPacket::fromSocket(code, socket->getSocket());
	if (packet == nullptr)
	{
		throw std::runtime_error("Invalid packet type");
		std::cerr << "Fatal: invalid packet detected (code " << (int)code << ")" << std::endl;
	}
	delete packet;
}

void PeerInfo::sendData(std::stringstream &ss, size_t len)
{
	char buffer[512];
	size_t current_pos = 0;

	while (current_pos < len)
	{
		ss.read(buffer, ((len - current_pos > 512) ? 512 : len - current_pos));
		fwrite(buffer, sizeof(*buffer), ((len - current_pos > 512) ? 512 : len - current_pos), getSocket()->getSocket());
		current_pos += ((len - current_pos > 512) ? 512 : len - current_pos);
	}
}

unsigned short PeerInfo::getId() const
{ return id; }

PeerInfo *PeerInfo::getMe()
{
	return new PeerInfo(nullptr, 1);
}

