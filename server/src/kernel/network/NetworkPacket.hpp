#pragma once

#include <sstream>
#include <stdio.h>

#define NETWORK_MAXCODE  *create(14)


namespace drt
{
namespace network
{

class ANetworkPacket
{
	public:
		static ANetworkPacket *fromSocket (char code, FILE *socket);
		virtual ~ANetworkPacket() { };

		virtual std::stringstream *getStream(size_t *buflen) const =0;

	protected:
};

typedef ANetworkPacket  *(*constructorFnc) (FILE *);

class SAuth: public ANetworkPacket
{
	public:
		SAuth(unsigned short id);

		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;

	private:
		SAuth();

	private:
		unsigned short id;
};

class CAuth: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Welcome: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class IdCh: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Relog: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Confirm: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Quit: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Netsplit: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class NewJob: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class EndJob: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Ready: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Proc: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Calc: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Result: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class CompilFail: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(FILE * socket);
		std::stringstream *getStream(size_t *buflen) const;
};
}
}
