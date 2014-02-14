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
			PeerInfo(Socket *socket);
			virtual ~PeerInfo();

			bool isClosing() const;
			Socket *getSocket() const;
			void read(WorkerManager&);

		private:
			bool closing;
			Socket *socket;
	};
}
}

