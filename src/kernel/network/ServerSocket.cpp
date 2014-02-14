//networkking
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

//error handling
#include <errno.h>

//cpp stuff
#include <stdexcept>

#include "network/Socket.hpp"
#include "network/ServerSocket.hpp"

using namespace drt::network;

ServerSocket::ServerSocket(unsigned short _port): port(_port)
{
	struct sockaddr_in addr;
	int flags;

	if ((socket = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("Cannot create socket");
	flags = fcntl(socket, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(socket, F_SETFL, flags);
	bzero((void *)&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (bind(socket, (__CONST_SOCKADDR_ARG) &addr, sizeof(addr)) == -1)
	{
		int err = errno;
		::close(socket);
		throw std::runtime_error("Cannot bind socket: " +std::string(strerror(err)));
	}
	if (listen(socket, 0) == -1)
	{
		int err = errno;
		::close(socket);
		throw std::runtime_error("Cannot listen on socket: " +std::string(strerror(err)));
	}
}

ServerSocket::~ServerSocket()
{
	::close(socket);
}

Socket *ServerSocket::accept()
{
	int sock;

	sock = ::accept(socket, nullptr, nullptr);
	if (sock == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
		return nullptr;
	else if (sock == -1)
		throw std::runtime_error("Cannot accept new connection: " +std::string(strerror(errno)));
	return new Socket(sock);
}

