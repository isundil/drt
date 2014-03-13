#include <iostream>
#include <fstream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include "NetworkPacket.hpp"
#include "PeerInfo.hpp"
#include "Socket.hpp"
#include "worker/NetworkWorker.hpp"
#include "worker/WorkerManager.hpp"
#include "render/Scene.hpp"

using namespace drt::network;

bool ANetworkPacket::sendToClient(PeerInfo *) const
{ return false; }

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

CAuth::CAuth(unsigned short _id): id(_id)
{ }

Welcome::Welcome(unsigned short _id): id(_id)
{ }

bool Welcome::sendToClient(PeerInfo *) const
{ return true; }

IdCh::IdCh(unsigned short o, unsigned short n): oldId(o), newId(n)
{ }

bool IdCh::sendToClient(PeerInfo *pi) const
{ return pi->getOldId() == oldId; }

Confirm::Confirm(unsigned short _id): id(_id)
{ }

Result::Result(unsigned short _id, unsigned short px, unsigned short py, unsigned int c): id(_id), x(px), y(py), color(c)
{ }

Result::Result(const Result &o): id(o.id), x(o.x), y(o.y), color(o.color)
{ }

Netsplit::Netsplit(unsigned short _id): id(_id)
{ }

NewJob::NewJob(
		network::Socket *socket,
		unsigned short _id,
		size_t len  ):id( _id )
{
	char* filename = tempnam( nullptr, nullptr );
	network::PeerInfo *client = nullptr;
	std::ofstream file( filename );
	std::ifstream filein;

	std::cout << "New scene detected for user " << id << " in file " << filename <<std::endl;
	size_t length = 0;

	while( length < len )
	{
		char buff[512];
		if( len-length < 512 )
		{
			size_t limit = len-length;
			length += socket -> read( buff, len-length );
			file.write( buff, limit );
		}
		else
		{
			length += socket -> read( buff, 512 );
			file.write( buff, 512 );
		}

	}

	file.close();
	filein.open( filename );

	render::Scene *scene = new render::Scene( filein, filename );
	filein.close();

	client = drt::WorkerManager::getSingleton() -> getNetwork() -> getPeer( id );
	client -> setScene( scene );

}

Monitor::Monitor(unsigned short _src, std::list<float> &_cpus, const memInfo &_ram, const memInfo &_swap): src(_src), cpuStat(_cpus), ramLevel(_ram), swapLevel(_swap)
{ }

Monitor::Monitor(const PeerInfo &peer)
{
	src = peer.getId();
	if (peer.getStats() == nullptr)
		throw std::exception();
	for (auto i = peer.getStats()->cpus.cbegin();
			i != peer.getStats()->cpus.cend(); i++)
		cpuStat.push_back(*i);
	ramLevel = std::make_pair(peer.getStats()->ram, peer.getStats()->maxRam);
	swapLevel = std::make_pair(peer.getStats()->swap, peer.getStats()->maxSwap);
}

bool Result::sendToClient(PeerInfo *pi) const
{ return id == pi->getId(); }

bool CompilFail::sendToClient(PeerInfo *) const
{ return true; //id == pi->getId();
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
	unsigned short id;

	socket -> read( &id, sizeof( id ) );
	return new CAuth( id );
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
	unsigned short id;
	size_t len;

	socket -> read( &id, sizeof( id ) );
	socket -> read( &len, sizeof( len ) );
	return new NewJob( socket, id, len );
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
	memInfo ram, swap;
	unsigned int min, max;

	socket->read(&src, sizeof(src));
	socket->read(&nbProc, sizeof(nbProc));
	for (char i =0; i < nbProc; i++)
	{
		char stat;

		socket->read(&stat, sizeof(stat));
		cpus.push_back(stat);
	}
	socket->read(&min, sizeof(min));
	socket->read(&max, sizeof(max));
	ram = std::make_pair(min, max);
	socket->read(&min, sizeof(min));
	socket->read(&max, sizeof(max));
	swap = std::make_pair(min, max);
	return new Monitor(src, cpus, ram, swap);
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
	unsigned short id;
	unsigned short pos[2];
	unsigned int color;

	socket->read(&id, sizeof(id));
	socket->read(&pos, sizeof(pos));
	socket->read(&color, sizeof(color));
	return new Result(id, pos[0], pos[1], color);
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

		peer->setConfirmed(manager.getNetwork()->nbClient() -1);
		peer->setId(manager.getNetwork()->incBiggerId());
		manager.send(peer, new Welcome(peer->getId()));
		//for (size_t i = 0; i < nbServer; i++)
		//	manager.getNetwork()->addServer(peer->getSocket());
		if (!peer->getConfirmed())
		{
			manager.send(peer, new Confirm(peer->getId()));
			manager.send(peer, new IdCh(-1, manager.getNetwork()->getMe()->getId()));
		}
		else
			manager.broadcast(new IdCh(peer->getId(), -1), peer);
	}
	else
	{
		if (peer->getId() == (unsigned short)-1)
			peer->setId(id);
		else
			manager.getNetwork()->addServer(peer->getSocket(), id);
	}
}

void
CAuth::doMagic(
		drt::WorkerManager &m,
		drt::network::PeerInfo *peer )
{
	if( (short) id == -1 )
	{
		peer -> setClient();
		peer -> setId( m.getNetwork() -> incBiggerId() );
		m.send( peer, new Welcome( peer -> getId() ) );
		id = peer -> getId();
	}
	else
	{
		m.getNetwork() -> addServer( peer -> getSocket(), id );
		peer -> setClient();
	}
	m.broadcast( new CAuth( id ), peer );

}

void Welcome::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *)
{
	//unsigned short oldId;

	//oldId = m.getNetwork()->getMe()->getId();
	//if (oldId == id)
	//	return;
	m.getNetwork()->getMe()->setId(id);
	m.getNetwork()->setMax(id);
}

void IdCh::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *p)
{
	if (oldId == newId)
		return;
	else if (newId == 0xFFFF && oldId != m.getNetwork()->getMe()->getId())
	{
		network::PeerInfo *pi = m.getNetwork()->addServer(p->getSocket(), oldId);
		unsigned int children = m.getNetwork()->nbSocket(p->getSocket());

		pi->setConfirmed(children);
		//TODO boucle inf ICI (cas circle loop)
		m.broadcast(new IdCh(*this), p);
		if (children == 0)
			m.send(p, new Confirm(oldId));
	}
	else if (newId == 0xFFFF)
		m.getNetwork()->removeLastPeer();
	else if (m.getNetwork()->getMe()->getId() == oldId)
	{
		m.getNetwork()->getMe()->setId(newId);
		m.broadcast(new IdCh(*this), p);
	}
	else
	{
		PeerInfo *pi = m.getNetwork()->getPeer(oldId);

		if (pi == nullptr)
		{
			m.getNetwork()->addServer(p->getSocket(), newId);
			m.broadcast(new IdCh(*this), p);
			return;
		}
		if (newId == 0xFFFF)
			return;
		m.broadcast(new IdCh(*this), p);
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
	{
		network::PeerInfo *newServ = m.getNetwork()->getPeer(id);

		if (!newServ)
		{
			m.log(std::cerr, *(m.getNetwork()), "Invalid Confirm id packet");
			return;
		}
		if (!newServ->decConfirm())
			return;
		m.send(newServ, new Confirm(*this));
		m.send(newServ, new IdCh(-1, m.getNetwork()->getMe()->getId()));
		for (auto i = m.getNetwork()->getPeers().cbegin(); i != m.getNetwork()->getPeers().cend(); i++)
			if (!(*i)->getConfirmed() && (*i)->getSocket() != newServ->getSocket())
				m.send(newServ, new SAuth((*i)->getId(), 0));
	}
	else
	{
		//Our server is now confirmed
		pi->setConfirmed(0);
		m.getNetwork()->confirm();
		std::list<PeerInfo *> clientList = m.getNetwork()->getPeers();
		for (auto i = clientList.cbegin(); i != clientList.cend(); i++)
		{
			if (pi == *i)
				continue;
			if ((*i)->getId() < m.getNetwork()->getMe()->getId())
			{
				unsigned short newId = m.getNetwork()->incBiggerId();
				(*i)->setId(newId);
				m.broadcast(new IdCh((*i)->getOldId(), (*i)->getId()), pi);
			}
			m.send(pi, new IdCh(0xFFFF, (*i)->getId()));
		}
		m.broadcast(new IdCh(m.getNetwork()->getMe()->getOldId(), id), pi);
	}
}

void Netsplit::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *pi)
{
	m.getNetwork()->rmPeer(m.getNetwork()->getPeer(id));
	if (pi->getId() == id)
		m.broadcast(new Netsplit(*this));
	else
		m.broadcast(new Netsplit(*this), pi);
}

void 
NewJob::doMagic( drt::WorkerManager &m,
		drt::network::PeerInfo * pi)
{
	m.addScene(pi, pi->getScene());
}


void Monitor::doMagic(drt::WorkerManager &m, drt::network::PeerInfo *s)
{
	network::PeerInfo *pi = m.getNetwork()->getPeer(src);
	network::PeerInfo::stats st;

	if (pi == nullptr)
		return;
	m.broadcast(new Monitor(*this), s);
	st.cpus = cpuStat;
	st.ram = ramLevel.first;
	st.maxRam = ramLevel.second;
	st.swap = swapLevel.first;
	st.maxSwap = swapLevel.second;
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

std::stringstream * CAuth::getStream(size_t *s) const
{
	std::stringstream *ss = new std::stringstream();
	char c = 0x01;

	ss->write(&c, sizeof(c));
	ss->write((char *)&id, sizeof(id));
	*s = sizeof(c) +sizeof(id);
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
	ss->write((char *)&(ramLevel.first), sizeof(ramLevel.first));
	(*buflen) += sizeof(ramLevel.first);
	ss->write((char *)&(ramLevel.second), sizeof(ramLevel.second));
	(*buflen) += sizeof(ramLevel.second);
	ss->write((char *)&(swapLevel.first), sizeof(swapLevel.first));
	(*buflen) += sizeof(swapLevel.first);
	ss->write((char *)&(swapLevel.second), sizeof(swapLevel.second));
	(*buflen) += sizeof(swapLevel.second);
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

const std::string SAuth::getName() const
{
	std::stringstream ss;
	ss << "SAuth " << id;
	return ss.str();
}

const std::string CAuth::getName() const
{ return "Cauth"; }

const std::string Welcome::getName() const
{
	std::stringstream ss;
	ss << "Welcome " << id;
	return ss.str();
}

const std::string IdCh::getName() const
{
	std::stringstream ss;
	ss << "Idch " << oldId << " -> " << newId;
	return ss.str();
}

const std::string Relog::getName() const
{ return "Relog"; }

const std::string Confirm::getName() const
{
	std::stringstream ss;
	ss << "Cfn " << id;
	return ss.str();
}

const std::string Quit::getName() const
{ return "Quit"; }

const std::string Netsplit::getName() const
{
	std::stringstream ss;
	ss << "Netsplit " << id;
	return ss.str();
}

const std::string NewJob::getName() const
{ return "New job"; }

const std::string EndJob::getName() const
{ return "End job"; }

const std::string Ready::getName() const
{ return "Ready"; }

const std::string Monitor::getName() const
{ return "Monitor"; }

const std::string Proc::getName() const
{ return "Proc"; }

const std::string Calc::getName() const
{ return "Calc"; }

const std::string Result::getName() const
{ return "Result"; }

const std::string CompilFail::getName() const
{ return "CompilFail"; }

