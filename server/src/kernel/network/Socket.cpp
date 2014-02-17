#include <stdexcept>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
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

	if (connect(socket, (struct sockaddr *) &addr, sizeof(addr)) == -1)
	{
		::close(socket);
		throw std::runtime_error("Cannot connect to server");
	}
	socket_std = fdopen(socket, "r+");
}

Socket::Socket(unsigned int _socket): socket(_socket), socket_std(fdopen(_socket, "r+"))
{ }

Socket::~Socket() //Calling fclose call fopen
{
	::fclose(socket_std);
}

int Socket::getSocketNumber() const
{ return socket; }

FILE * Socket::getSocket() const
{ return socket_std; }

