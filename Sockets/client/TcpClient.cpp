#include "TcpClient.h"

TcpClient::TcpClient(SOCKET socket)
{
	this->socket = socket;
}

TcpClient::~TcpClient()
{
	close();
}

TcpClient::TcpClient(const TcpClient &client)
{
	socket = client.socket;
}

TcpClient& TcpClient::operator= (const TcpClient &client)
{
	close();
	socket = client.socket;

	return *this;
}

void TcpClient::close()
{
	closesocket(socket);
	socket = NULL;
}

bool TcpClient::connect(const char *address, unsigned port)
{
	if (!socket)
	{
		return false;
	}
	
	sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr(address);
	client.sin_port = htons(port);

    if (::connect(socket, (SOCKADDR*)&client, sizeof(client)) == SOCKET_ERROR) 
	{
		return false;
    }

	return true;
}

bool TcpClient::send(char *data, size_t dataSize)
{
	if (!socket)
	{
		return false;
	}

	if (::send(socket, data, dataSize, 0) == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

int TcpClient::read(char *buf, size_t bufSize)
{
	if (!socket)
	{
		return false;
	}

	int res = 0;

	res = recv(socket, buf, bufSize, 0);
	if (res == SOCKET_ERROR)
	{
		return -1;
	}

	return res;
}

void TcpClient::setSocketDecriptor(SOCKET socket)
{
	close();
	this->socket = socket;
}

SOCKET TcpClient::socketDecriptor()
{
	return socket;
}