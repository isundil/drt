#include <iostream>

#include <map>
#include "NetworkPacket.hpp"
#include "PeerInfo.hpp"
#include "Socket.hpp"
#include "worker/NetworkWorker.hpp"
#include "worker/WorkerManager.hpp"

using namespace drt::network;

ANetworkPacket *ANetworkPacket::fromSocket(char code, network::Socket *socket)
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
	ctors[11] = Monitor::create;
	ctors[12] = Proc::create;
	ctors[13] = Calc::create;
	ctors[14] = Result::create;
	ctors[15] = CompilFail::create;

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

Netsplit::Netsplit(unsigned short _id): id(_id)
{ }

Monitor::Monitor(unsigned short _src, std::list<float> &_cpus): src(_src), cpuStat(_cpus)
{ }

Monitor::Monitor(const PeerInfo &peer)
{
	src = peer.getId();
	if (peer.getStats() == nullptr)
		throw std::exception();
	for (auto i = peer.getStats()->cpus.cbegin();
			i != peer.getStats()->cpus.cend(); i++)
		cpuStat.push_back(*i);
}

ANetworkPacket * SAuth::create(network::Socket * socket)
{
	unsigned short id;
	unsigned short nserv;

	socket->read(&id, sizeof(id));
	socket->read(&nserv, sizeof(nserv));
	return new SAuth(id, nserv);
}

ANetworkPacket * CAuth::create(network::Socket * socket)
{
	return new CAuth();
}

ANetworkPacket * Welcome::create(network::Socket * socket)
{
	unsigned short id;

	socket->read(&id, sizeof(id));
	return new Welcome(id);
}

ANetworkPacket * IdCh::create(network::Socket * socket)
{
	unsigned short ids[2];

	socket->read(ids, sizeof(*ids) *2);
	return new IdCh(ids[0], ids[1]);
}

ANetworkPacket * Relog::create(network::Socket * socket)
{
	return new Relog();
}

ANetworkPacket * Confirm::create(network::Socket * socket)
{
	unsigned short id;

	socket->read(&id, sizeof(id));
	return new Confirm(id);
}

ANetworkPacket * Quit::create(network::Socket * socket)
{
	return new Quit();
}

ANetworkPacket * Netsplit::create(network::Socket * socket)
{
	unsigned short id;

	socket->read(&id, sizeof(id));
	return new Netsplit(id);
}

ANetworkPacket * NewJob::create(network::Socket * socket)
{
	return new NewJob();
}

ANetworkPacket * EndJob::create(network::Socket * socket)
{
	return new EndJob();
}

ANetworkPacket * Ready::create(network::Socket * socket)
{
	return new Ready();
}

ANetworkPacket * Monitor::create(network::Socket *socket)
{
	char nbProc;
	std::list<float> cpus;
	unsigned short src;

	socket->read(&src, sizeof(src));
	socket->read(&nbProc, sizeof(nbProc));
	for (char i =0; i < nbProc; i++)
	{
		char stat;

		socket->read(&stat, sizeof(stat));
		cpus.push_back(stat);
	}
	return new Monitor(src, cpus);
}

ANetworkPacket * Proc::create(network::Socket * socket)
{
	return new Proc();
}

ANetworkPacket * Calc::create(network::Socket * socket)
{
	return new Calc();
}

ANetworkPacket * Result::create(network::Socket * socket)
{
	return new Result();
}

ANetworkPacket * CompilFail::create(network::Socket * socket)
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

void Welcome::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *)
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

void Netsplit::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *pi)
{
	m.getNetwork()->releasePeer(m.getNetwork()->getPeer(id));
	m.broadcast(new Netsplit(*this), pi);
}

void Monitor::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *s)
{
	network::PeerInfo *pi = m.getNetwork()->getPeer(src);
	network::PeerInfo::stats st;

	if (pi == nullptr)
		return;
	m.broadcast(new Monitor(*this), s);
	st.cpus = cpuStat;
	st.ram = 0; //TODO
	st.maxRam = 0; //TODO
	pi->setStats(st);
}

std::stringstream * SAuth::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0;
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
	char c = 2;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &id, sizeof(id));
	*buflen = sizeof(c) +sizeof(id);
	return ss;
}

std::stringstream * IdCh::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 3;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &oldId, sizeof(oldId));
	ss->write((char *) &newId, sizeof(newId));
	*buflen = sizeof(c) +sizeof(oldId) +sizeof(newId);
	return ss;
}

std::stringstream * Relog::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 4;
	ss->write((char *) &c, sizeof(c));
	*buflen = sizeof(c);
	return ss;
}

std::stringstream * Confirm::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 5;
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
	std::stringstream *ss = new std::stringstream();
	char c = 7;
	ss->write((char *) &c, sizeof(c));
	ss->write((char *) &id, sizeof(id));
	*buflen = sizeof(c) +sizeof(id);
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

std::stringstream *Monitor::getStream(size_t *buflen) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 11;
	char nbProc;

	nbProc = (char) cpuStat.size();
	ss->write((char *)&c, sizeof(c));
	ss->write((char *)&src, sizeof(src));
	ss->write((char *)&nbProc, sizeof(nbProc));
	*buflen = sizeof(c) +sizeof(src) +sizeof(nbProc);
	for (auto i =cpuStat.cbegin(); i != cpuStat.cend(); i++)
	{
		char currentCpu = *i;

		ss->write(&currentCpu, sizeof(currentCpu));
		(*buflen) += sizeof(currentCpu);
	}
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

