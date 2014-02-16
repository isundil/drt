#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include "network/PeerInfo.hpp"
#include "network/Socket.hpp"
#include "network/NetworkPacket.hpp"
#include "worker/WorkerManager.hpp"

using namespace drt::network;

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

unsigned short PeerInfo::getId() const
{ return id; }

PeerInfo *PeerInfo::getMe()
{
	return new PeerInfo(nullptr, 1);
}

