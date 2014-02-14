#include "network/PeerInfo.hpp"
#include "network/Socket.hpp"
#include "worker/WorkerManager.hpp"

using namespace drt::network;

PeerInfo::PeerInfo(Socket *s): closing(true), socket(s)
{ }

PeerInfo::~PeerInfo()
{
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
}

