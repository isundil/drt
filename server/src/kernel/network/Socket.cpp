#include "network/Socket.hpp"

using namespace drt::network;


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

