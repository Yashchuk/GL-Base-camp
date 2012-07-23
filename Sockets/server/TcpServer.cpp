#include "TcpServer.h"
#include <Windows.h>

// Teporary struct to pass as a parameter
struct ThreadParam
{
	TcpServer *inst;
	SOCKET socket;
};

TcpServer::TcpServer()
{
	hThread = NULL;

	// Init windows socket library
	WSADATA wsaData;
	initialized = (WSAStartup(0x101, &wsaData) == 0);

	listening = false;
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

	// Create server socket
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

	// Creating listening thread
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startListenThread, this, 0, &threadId);
	if (!hThread)
	{
		return false;
	}

	listening = true;
	return true;
}

int TcpServer::startListenThread(void *instance)
{
	// Call listen method of given instance in current thread
	TcpServer *temp = (TcpServer*)instance;
	return temp->listenThread();
}

int TcpServer::startClientThread(void *param)
{
	// Call incomingConnection method of given instance in current thread,
	// sending in socket descryptor as parameter
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
		// Wait for new client
		client = accept(serverSocket, (sockaddr*)&clientAddr, &addrlen);
		if (client != INVALID_SOCKET)
		{
			// Fill temporary struct
			ThreadParam p;
			p.inst = this;
			p.socket = client;
			DWORD threadId;
			
			// Create thread for interation with client
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
		// Close listening thread
		if (hThread)
		{
			TerminateThread(hThread, 0);
		}
		// Close socket and set listening flag to false
		closesocket(serverSocket);
		serverSocket = NULL;
		listening = false;
	}
}

void TcpServer::incomingConnection(SOCKET socket)
{
}

bool TcpServer::wait()
{
	if (initialized && listening)
	{
		// Wait for listening thread to return
		if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)
		{
			return false;
		}

		return true;
	}

	return false;
}