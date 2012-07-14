#include "TcpClient.h"
#include <iostream>

using std::cout;
using std::endl;

SOCKET createSocket();

enum
{
	ENCRYPT = 1,
	DECRYPT = 2,
	LOGIN = 4,
	OK = 8,
	FAIL = 16
};

int main()
{	
	SOCKET socket = createSocket();
	if (!socket)
	{
		WSACleanup();
		return 1;
	}
	TcpClient client(socket);
	if (!client.connect("127.0.0.1", 4000))
	{
		cout << "Connection failed" << endl;
	}

	char mask;

	mask = LOGIN;
	client.send(&mask, 1);

	client.read(&mask, 1);

	if (mask & OK)
	{
		unsigned size = sizeof("user\n525");
		client.send((char*)&size, 4);
		client.send("user4\n525", size);

		client.read(&mask, 1);

		if (mask & OK)
		{
			cout << "Authorized" << endl;
		}
	}

	WSACleanup();
	return 0;
}

SOCKET createSocket()
{
	WSADATA wsaData;
	if (WSAStartup(0x101, &wsaData))
	{
		return NULL;
	}

	SOCKET client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client == SOCKET_ERROR)
	{
		return NULL;
	}

	return client;
}