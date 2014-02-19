#pragma once

namespace drt
{
class WorkerManager;

namespace network
{
	class Socket;

	class PeerInfo
	{
		public:
			PeerInfo(const std::string &ip, unsigned short port);
			PeerInfo(Socket *socket, bool direct, unsigned short id = -1);
			virtual ~PeerInfo();

			bool isClosing() const;
			Socket *getSocket() const;
			void read(WorkerManager&);
			void setId(unsigned short id);
			unsigned short getId() const;
			unsigned short getOldId() const;

			static PeerInfo *getMe();
			void sendData(std::stringstream &ss, size_t len);

			std::pair<std::string, unsigned short> getConInfo() const;

			bool isDirect() const;

		private:
			std::string ip;
			unsigned short port;

			bool closing;
			Socket *socket;
			unsigned short id;
			unsigned short oldId;
			const bool direct;
	};
}
}

