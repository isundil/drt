#include <iostream>


#include <map>
#include "NetworkPacket.hpp"
#include "PeerInfo.hpp"
#include "worker/NetworkWorker.hpp"
#include "worker/WorkerManager.hpp"

using namespace drt::network;

ANetworkPacket *ANetworkPacket::fromSocket(char code, FILE *socket)
{
	std::map<short, constructorFnc> ctors;

	ctors[ 0] = SAuth::create;
	ctors[ 1] = CAuth::create;
	ctors[ 2] = Welcome::create;
	ctors[ 3] = IdCh::create;
	ctors[ 4] = Relog::create;
	ctors[ 5] = Confirm::create;
	ctors[ 6] = Quit::create;
	ctors[ 7] = Netsplit::create;
	ctors[ 8] = NewJob::create;
	ctors[ 9] = EndJob::create;
	ctors[10] = Ready::create;
	ctors[11] = Proc::create;
	ctors[12] = Calc::create;
	ctors[13] = Result::create;
	ctors[14] = CompilFail::create;

	auto f = ctors.find(code);
	if (f == ctors.end())
		return nullptr;
	return (*f).second(socket);
}

SAuth::SAuth(unsigned short _id): id(_id)
{ }

Welcome::Welcome(unsigned short _id): id(_id)
{ }

IdCh::IdCh(unsigned short o, unsigned short n): oldId(o), newId(n)
{ }

ANetworkPacket * SAuth::create(FILE * socket)
{
	unsigned short id;

	fread(&id, sizeof(id), 1, socket);
	return new SAuth(id);
}

ANetworkPacket * CAuth::create(FILE * socket)
{
	return new CAuth();
}

ANetworkPacket * Welcome::create(FILE * socket)
{
	unsigned short id;

	fread(&id, sizeof(id), 1, socket);
	return new Welcome(id);
}

ANetworkPacket * IdCh::create(FILE * socket)
{
	unsigned short ids[2];

	fread(&ids, sizeof(*ids), 2, socket);
	return new IdCh(ids[0], ids[1]);
}

ANetworkPacket * Relog::create(FILE * socket)
{
	return new Relog();
}

ANetworkPacket * Confirm::create(FILE * socket)
{
	return new Confirm();
}

ANetworkPacket * Quit::create(FILE * socket)
{
	return new Quit();
}

ANetworkPacket * Netsplit::create(FILE * socket)
{
	return new Netsplit();
}

ANetworkPacket * NewJob::create(FILE * socket)
{
	return new NewJob();
}

ANetworkPacket * EndJob::create(FILE * socket)
{
	return new EndJob();
}

ANetworkPacket * Ready::create(FILE * socket)
{
	return new Ready();
}

ANetworkPacket * Proc::create(FILE * socket)
{
	return new Proc();
}

ANetworkPacket * Calc::create(FILE * socket)
{
	return new Calc();
}

ANetworkPacket * Result::create(FILE * socket)
{
	return new Result();
}

ANetworkPacket * CompilFail::create(FILE * socket)
{
	return new CompilFail();
}

void SAuth::doMagic(drt::WorkerManager &manager, drt::network::PeerInfo *peer)
{
	if (peer->getId() == (unsigned short)-1 && id == (unsigned short)-1)
	{
		std::cout << "client handshake detected (peer->" << peer->getId() << "), (id->" << id << ")" << std::endl;

		peer->setId(manager.getNetwork()->incBiggerId());
		manager.broadcast(new SAuth(peer->getId()), peer);
		manager.send(peer, new Welcome(peer->getId()));
		//TODO send other server SAuth
		//(foreach clients send peer-> SAuth client->id)
	}
	else
	{
#warning "TODO"
		//TODO add server to map
	}
}

void Welcome::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *p)
{
	unsigned short oldId;

	oldId = m.getNetwork()->getMe()->getId();
	if (oldId == id)
		return;
	m.getNetwork()->getMe()->setId(id);
	m.broadcast(new IdCh(oldId, id), p);
	m.broadcast(new Relog(), p);
}

void IdCh::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *p)
{
	if (oldId == newId)
		return;
	if (m.getNetwork()->getMe()->getId() == oldId)
		m.getNetwork()->getMe()->setId(newId);
	else
	{
		PeerInfo *pi = m.getNetwork()->getPeer(oldId);
		if (pi == nullptr)
			return;
		pi->setId(newId);
	}
	m.broadcast(new IdCh(*this), p);
}

std::stringstream * SAuth::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0x00;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &id, sizeof(id));
	*buflen = sizeof(c) +sizeof(id);
	return ss;
}

std::stringstream * CAuth::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * Welcome::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0x01;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &id, sizeof(id));
	*buflen = sizeof(c) +sizeof(id);
	return ss;
}

std::stringstream * IdCh::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0x02;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &oldId, sizeof(oldId));
	ss->write((char *) &newId, sizeof(newId));
	*buflen = sizeof(c) +sizeof(oldId) +sizeof(newId);
	return ss;
}

std::stringstream * Relog::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * Confirm::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * Quit::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * Netsplit::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * NewJob::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * EndJob::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * Ready::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * Proc::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * Calc::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * Result::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * CompilFail::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
	return ss;
}

