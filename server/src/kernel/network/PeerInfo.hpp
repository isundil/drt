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
			PeerInfo(Socket *socket, unsigned short id = 0);
			virtual ~PeerInfo();

			bool isClosing() const;
			Socket *getSocket() const;
			void read(WorkerManager&);
			unsigned short getId() const;

			static PeerInfo *getMe();
			void sendData(std::stringstream &ss, size_t len);

			std::pair<std::string, unsigned short> getConInfo() const;

		private:
			std::string ip;
			unsigned short port;

			bool closing;
			Socket *socket;
			unsigned short id;
	};
}
}

