#pragma once

#include <string>
#include <stdio.h>

namespace drt
{
namespace network
{

	class Socket
	{
		public:
			Socket(const std::string &ip, unsigned short port);
			Socket(unsigned int _socket);
			~Socket();

			int getSocketNumber() const;
			FILE * getSocket() const;

			void addRel();
			void rmRel();
			bool lastRel() const;

		private:
			int socket;
			FILE *socket_std;

			int rel;

		private:
			Socket();
			Socket(const Socket &);
	};

}
}
