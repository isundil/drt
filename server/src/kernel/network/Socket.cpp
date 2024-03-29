#include <iostream>

#include <fcntl.h>
#include <sstream>
#include <stdexcept>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include "network/Socket.hpp"

using namespace drt::network;

Socket::Socket(const std::string &ip, unsigned short port)
{
	struct sockaddr_in addr;

	if ((socket = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("Cannot create socket");
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
	if (::connect(socket, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		std::stringstream ss("Cannot connect to ");
		ss << "Cannot connect to " << ip << ":" << port << " (" << strerror(errno) << ")";
		::close(socket);
		throw std::runtime_error(ss.str());
	}
}

Socket::Socket(unsigned int _socket): socket(_socket)
{ }

Socket::~Socket() //Calling fclose call fopen
{ ::close(socket); }

const Socket *Socket::greater(const Socket *o) const
{
	if (o == nullptr)
		return this;
	return o->socket > socket ? o : this;
}

int Socket::select(fd_set *read, fd_set *error) const
{
	struct timeval timeout = { 0, 0 };

	return ::select(socket +1, read, nullptr, error, &timeout);
}

bool Socket::isClosed() const
{
	int closed;
	ioctl(socket, FIONREAD, &closed);
	return closed == 0;
}

bool Socket::isInSet(fd_set *set) const
{ return FD_ISSET(socket, set); }

void Socket::addToSet(fd_set *set)
{ FD_SET(socket, set); }

int Socket::read(void *buf, size_t len)
{
	ssize_t result;
	size_t pos =0;
	char *b = (char *) buf;

	while (pos < len)
	{
		if ((result = ::read(socket, &b[pos], len -pos)) == -1)
		{
			std::cerr << "Socket error" << std::endl;
			throw std::runtime_error("Cannot read from socket");
		}
		pos += result;
	}
	return pos;
}

char Socket::getc()
{
	char b;

	this->read(&b, sizeof(b));
	return b;
}

int Socket::write(void *buf, size_t len)
{
	struct pollfd pollfd = { .fd = socket, .events = POLLERR };
	int wr, l;

	l = len;

	if (poll(&pollfd, 1, 0) < 0 || pollfd.revents & POLLERR)
		return 0;
	wr = ::write(socket, buf, len);
	if (wr < l)
	{
		return 0;
	}
	return len;
}

