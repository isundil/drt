#include "network/PeerInfo.hpp"
#include "network/Socket.hpp"
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
	(void) manager;
	//TODO read from socket and add operation to manager
}

unsigned short PeerInfo::getId() const
{ return id; }

PeerInfo *PeerInfo::getMe()
{
	return new PeerInfo(nullptr, 1);
}

