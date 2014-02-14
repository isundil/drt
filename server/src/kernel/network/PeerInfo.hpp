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
			PeerInfo(Socket *socket, unsigned short id = 0);
			virtual ~PeerInfo();

			bool isClosing() const;
			Socket *getSocket() const;
			void read(WorkerManager&);
			unsigned short getId() const;

			static PeerInfo *getMe();

		private:
			bool closing;
			Socket *socket;
			unsigned short id;
	};
}
}

