#pragma once

#include <utility>
#include <sstream>
#include <stdio.h>
#include <list>

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
		virtual const std::string getName() const =0;
		virtual bool sendToClient(network::PeerInfo *) const;

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
		const std::string getName() const;

	private:
		SAuth();

	private:
		unsigned short id;
		unsigned short nbServer;
};

class CAuth: public ANetworkPacket
{
	public:
		CAuth(unsigned short _id);
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
	
		void 
		doMagic(drt::WorkerManager &manager, drt::network::PeerInfo *);

		const std::string getName() const;

	private:
		unsigned short id;
};

class Welcome: public ANetworkPacket
{
	public:
		Welcome(unsigned short _id);
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		void doMagic(drt::WorkerManager &manager, drt::network::PeerInfo *);

		const std::string getName() const;

		bool sendToClient(PeerInfo *) const;

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

		const std::string getName() const;
		bool sendToClient(PeerInfo *) const;

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
		const std::string getName() const;
};

class Confirm: public ANetworkPacket
{
	public:
		Confirm(unsigned short id);

		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;

		void doMagic(drt::WorkerManager &, drt::network::PeerInfo *);
		const std::string getName() const;

	private:
		unsigned short id;
};

class Quit: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		const std::string getName() const;
};

class Netsplit: public ANetworkPacket
{
	public:
		Netsplit(unsigned short id);
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		void doMagic(drt::WorkerManager &, drt::network::PeerInfo *);
		const std::string getName() const;

	private:
		Netsplit();

		unsigned short id;
};

class NewJob: public ANetworkPacket
{
	public:
		NewJob( network::Socket *, unsigned short, size_t );
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		void doMagic(
				drt::WorkerManager &, 
				drt::network::PeerInfo *);
		const std::string getName() const;

	private:
		unsigned short id;
};

class EndJob: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		const std::string getName() const;
};

class Ready: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		const std::string getName() const;
};

class Monitor: public ANetworkPacket
{
	public:
		typedef std::pair<unsigned int, unsigned int> memInfo;

	public:
		Monitor(unsigned short src, std::list<float> &cpuInfo, const memInfo &ram, const memInfo &swap);
		Monitor(const network::PeerInfo &peer);
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;

		void doMagic(drt::WorkerManager &, drt::network::PeerInfo *);
		const std::string getName() const;

	private:
		Monitor();

		unsigned short src;
		std::list<float> cpuStat;
		memInfo ramLevel;
		memInfo swapLevel;
};

class Proc: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		const std::string getName() const;
};

class Calc: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		const std::string getName() const;
};

class Result: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		const std::string getName() const;
		bool sendToClient(PeerInfo *) const;
};

class CompilFail: public ANetworkPacket
{
	public:
		static ANetworkPacket *create(Socket * socket);
		std::stringstream *getStream(size_t *buflen) const;
		const std::string getName() const;
		bool sendToClient(PeerInfo *) const;
};
}
}
