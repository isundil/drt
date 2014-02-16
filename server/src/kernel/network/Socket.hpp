#pragma once

#include <stdio.h>

namespace drt
{
namespace network
{

	class Socket
	{
		public:
			Socket(unsigned int _socket);
			~Socket();

			int getSocketNumber() const;
			FILE * getSocket() const;

		private:
			int socket;
			FILE *socket_std;

		private:
			Socket();
			Socket(const Socket &);
	};

}
}
