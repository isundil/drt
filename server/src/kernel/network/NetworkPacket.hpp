#pragma once

#include <sstream>
#include <stdio.h>

#define NETWORK_MAXCODE  *create(14)


namespace drt
{
class WorkerManager;
namespace network
{
class PeerInfo;
class Socket;

class ANetworkPacket
{
	public:
		static ANetworkPacket *fromSocket (char code, Socket *socket);
		virtual ~ANetworkPacket() { };

		virtual std::stringstream *getStream(size_t *buflen) const =0;

		virtual void doMagic(drt::WorkerManager &, network::PeerInfo *) { };

	protected:
};

typedef ANetworkPacket  *(*constructorFnc) (Socket *);

class SAuth: public ANetworkPacket
{
	public:
		SAuth(unsigned short id, unsigned short nbServer);

		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;

		void doMagic(drt::WorkerManager &manager, drt::network::PeerInfo *);

	private:
		SAuth();

	private:
		unsigned short id;
		unsigned short nbServer;
};

class CAuth: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Welcome: public ANetworkPacket
{
	public:
		Welcome(unsigned short _id);
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		void doMagic(drt::WorkerManager &manager, drt::network::PeerInfo *);

	private:
		unsigned short id;
};

class IdCh: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;

		IdCh(unsigned short oldId, unsigned short newId);

		void doMagic(drt::WorkerManager &, drt::network::PeerInfo *);

	private:
		IdCh();

		unsigned short oldId;
		unsigned short newId;
};

class Relog: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;

		void doMagic(drt::WorkerManager &, drt::network::PeerInfo *);
};

class Confirm: public ANetworkPacket
{
	public:
		Confirm(unsigned short id);

		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;

		void doMagic(drt::WorkerManager &, drt::network::PeerInfo *);

	private:
		unsigned short id;
};

class Quit: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Netsplit: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class NewJob: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class EndJob: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Ready: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Proc: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Calc: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class Result: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};

class CompilFail: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
};
}
}
