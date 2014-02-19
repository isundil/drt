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

SAuth::SAuth(unsigned short _id, unsigned short nserv): id(_id), nbServer(nserv)
{ }

Welcome::Welcome(unsigned short _id): id(_id)
{ }

IdCh::IdCh(unsigned short o, unsigned short n): oldId(o), newId(n)
{ }

Confirm::Confirm(unsigned short _id): id(_id)
{ }

ANetworkPacket * SAuth::create(FILE * socket)
{
	unsigned short id;
	unsigned short nserv;

	fread(&id, sizeof(id), 1, socket);
	fread(&nserv, sizeof(nserv), 1, socket);
	return new SAuth(id, nserv);
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

	fread(ids, sizeof(*ids), 2, socket);
	return new IdCh(ids[0], ids[1]);
}

ANetworkPacket * Relog::create(FILE * socket)
{
	return new Relog();
}

ANetworkPacket * Confirm::create(FILE * socket)
{
	unsigned short id;

	fread(&id, sizeof(id), 1, socket);
	return new Confirm(id);
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
		std::cout << "DEBUG client handshake detected (peer->" << peer->getId() << "), (id->" << id << ")" << std::endl;

		peer->setId(manager.getNetwork()->incBiggerId());
		manager.send(peer, new Welcome(peer->getId()));
		manager.broadcast(new SAuth(peer->getId(), 0), peer);
		manager.send(peer, new SAuth(manager.getNetwork()->getMe()->getId(), 0));
		if (manager.getNetwork()->nbClient() == 1)
			manager.send(peer, new Confirm(peer->getId()));
		//TODO will need to wait
		manager.getNetwork()->sendConnected(peer);
		for (size_t i = 0; i < nbServer; i++)
			manager.getNetwork()->addServer(peer->getSocket());
	}
	else
	{
		if (peer->getId() == (unsigned short)-1)
			peer->setId(id);
		else
			manager.getNetwork()->addServer(peer->getSocket(), id);
	}
}

void Welcome::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *p)
{
	unsigned short oldId;

	oldId = m.getNetwork()->getMe()->getId();
	if (oldId == id)
		return;
	m.getNetwork()->getMe()->setId(id);
	m.getNetwork()->setMax(id);
}

void IdCh::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *p)
{
	if (oldId == newId)
		return;
	if (m.getNetwork()->getMe()->getId() == oldId)
		m.getNetwork()->getMe()->setId(newId);
	else if (newId == 0xFFFF)
		m.getNetwork()->addServer(p->getSocket(), oldId);
	else
	{
		PeerInfo *pi = m.getNetwork()->getPeer(oldId);
		if (pi == nullptr)
		{
			m.getNetwork()->addServer(p->getSocket(), newId);
			return;
		}
		if (newId == 0xFFFF)
			return;
		pi->setId(newId);
	}
}

void Relog::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *pi)
{
	m.broadcast(new Relog(), pi);
}

void Confirm::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *pi)
{
	if (id != m.getNetwork()->getMe()->getId())
		m.send(m.getNetwork()->getPeer(id), new Confirm(*this));
	else
	{
		m.broadcast(new IdCh(m.getNetwork()->getMe()->getOldId(), id), pi);
		auto clientList = m.getNetwork()->getPeers();
		for (auto i = clientList.cbegin(); i != clientList.cend(); i++)
		{
			if (pi == *i)
				continue;
			unsigned short newId = m.getNetwork()->incBiggerId();
			m.broadcast(new IdCh((*i)->getId(), newId), pi);
			(*i)->setId(newId);
		}
	}
}

std::stringstream * SAuth::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0x00;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &id, sizeof(id));
	ss->write((char *) &nbServer, sizeof(nbServer));
	*buflen = sizeof(c) +sizeof(id) +sizeof(nbServer);
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
	char c = 0x02;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &id, sizeof(id));
	*buflen = sizeof(c) +sizeof(id);
	return ss;
}

std::stringstream * IdCh::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0x03;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &oldId, sizeof(oldId));
	ss->write((char *) &newId, sizeof(newId));
	*buflen = sizeof(c) +sizeof(oldId) +sizeof(newId);
	return ss;
}

std::stringstream * Relog::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0x04;
	ss->write((char *) &c, sizeof(c));
	*buflen = sizeof(c);
	return ss;
}

std::stringstream * Confirm::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0x05;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &id, sizeof(id));
	*buflen = sizeof(c) +sizeof(id);
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

