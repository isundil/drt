#pragma once

#include <fstream>
#include <list>

namespace drt
{
class WorkerManager;

namespace render
{
	class Scene;
}

namespace network
{
	class Socket;

	class PeerInfo
	{
		public:
			struct stats
			{
				public:
					std::list<float> cpus;
					size_t ram;
					size_t maxRam;
					size_t swap;
					size_t maxSwap;

					void copy(const stats &other);
					std::string debug() const;
			};

		public:
			PeerInfo(const std::string &ip, unsigned short port);
			PeerInfo(Socket *socket, bool direct, unsigned short id = -1);
			virtual ~PeerInfo();

			bool isClosing() const;
			Socket *getSocket() const;
			void read(WorkerManager&);
			void setId(unsigned short id);
			void setClient();
			bool isAClient() const;
			unsigned short getId() const;
			unsigned short getOldId() const;

			bool ready() const;
			bool ready(bool);

			static PeerInfo *getMe();
			void sendData(std::stringstream &ss, size_t len);
			void sendData(std::ifstream &ss, size_t len);

			std::pair<std::string, unsigned short> getConInfo() const;
			void setStats(const stats &stats);
			const stats *getStats() const;

			bool isDirect() const;

			void setScene( render::Scene* );
			render::Scene* getScene();
			int getConfirmed() const;
			void setConfirmed(int);
			bool decConfirm();

		private:
			std::string ip;
			unsigned short port;

			bool _ready;
			bool closing;
			Socket *socket;
			unsigned short id;
			unsigned short oldId;
			const bool direct;
			stats *procInfo;
			bool isClient;
			render::Scene* scene;
			int confirmed;
	};
}
}

