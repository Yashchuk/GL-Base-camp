#include "TcpServer.h"
#include <Windows.h>

struct ThreadParam
{
	TcpServer *inst;
	SOCKET socket;
};

TcpServer::TcpServer()
{
	hThread = NULL;
	WSADATA wsaData;
    initialized = (WSAStartup(0x101, &wsaData) == 0);
}

TcpServer::~TcpServer()
{
	close();
	WSACleanup();
}

TcpServer::TcpServer(const TcpServer &serv)
{
}

TcpServer& TcpServer::operator= (const TcpServer &serv)
{
	return *this;
}

bool TcpServer::listen(unsigned port, unsigned maxPendingConnections)
{
	if (!initialized)
	{
		return false;
	}

	sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if(serverSocket == INVALID_SOCKET)
	{
		serverSocket = NULL;
		return false;
	}

	if(bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		close();
		return false;
	}

	if(::listen(serverSocket, maxPendingConnections))
    {
		close();
		return false;
	}

	DWORD threadId;

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startListenThread, this, 0, &threadId);
	if (!hThread)
	{
		return false;
	}

	return true;
}

int TcpServer::startListenThread(void *instance)
{
	TcpServer *temp = (TcpServer*)instance;
    return temp->listenThread();
}

int TcpServer::startClientThread(void *param)
{
	ThreadParam *temp = (ThreadParam*)param;
	temp->inst->incomingConnection(temp->socket);

	return 0;
}

int TcpServer::listenThread()
{
	SOCKET client;
	sockaddr_in clientAddr;
	int addrlen = sizeof(clientAddr);
	
	while(true)
	{
		client = accept(serverSocket, (sockaddr*)&clientAddr, &addrlen);
		if (client != INVALID_SOCKET)
		{
			ThreadParam p;
			p.inst = this;
			p.socket = client;
			DWORD threadId;
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startClientThread, &p, 0, &threadId);
		}
		Sleep(1);
	}

	return 0;
}

void TcpServer::close()
{
	if (initialized && serverSocket)
	{
		if (hThread)
		{
			TerminateThread(hThread, 0);
		}
		closesocket(serverSocket);
		serverSocket = NULL;
	}
}

void TcpServer::incomingConnection(SOCKET socket)
{
}