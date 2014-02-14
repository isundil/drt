#pragma once

namespace drt
{
namespace network
{
class Socket;

class ServerSocket
{
	public:
		ServerSocket(unsigned short port);
		virtual ~ServerSocket();

		Socket *accept();

	private:
		ServerSocket();

	private:
		unsigned short port;
		int socket;
};
}
}
