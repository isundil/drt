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

			void addRel();
			void rmRel();
			bool lastRel() const;

			int write(void *buffer, size_t len);
			int read(void *buffer, size_t len);
			char getc();

			const Socket *greater(const Socket *) const;

			bool isClosed() const;
			void addToSet(fd_set *set);
			bool isInSet(fd_set *set) const;
			int select(fd_set *read, fd_set *error =nullptr) const;

		private:
			int socket;

			int rel;

		private:
			Socket();
			Socket(const Socket &);
	};

}
}
