#include <map>
#include "NetworkPacket.hpp"

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
	return new Welcome();
}

ANetworkPacket * IdCh::create(FILE * socket)
{
	return new IdCh();
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
	std::stringstream *ss = nullptr;
	return ss;
}

std::stringstream * IdCh::getStream(size_t *buflen) const
{
	std::stringstream *ss = nullptr;
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

