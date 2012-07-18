/** 
  * @class	TcpServer
  * @brief	Tcp server implementation using windows sockets
  * Copyright (C) 2012 Vitaliy Sidenko <vitalyax@gmail.com>
  */

#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H

#include <winsock2.h>

class TcpServer
{
private:
	bool initialized;
	bool listening;
	HANDLE hThread;

	int listenThread();
	static int startListenThread(void *instance);
	static int startClientThread(void *param);
	TcpServer(const TcpServer &serv);
	TcpServer& operator= (const TcpServer &serv);

public:
	TcpServer();
	virtual ~TcpServer();

	/**
      * @brief			Start listening for clinets
      * @param	[in]	port Port
	  * @param	[in]	maxPendingConnections maximum pending connectins
	  * @return			False if error occurred
      */
	bool listen(unsigned port, unsigned maxPendingConnections);

	/**
      * @brief			Stop listening
	  * @return			void
      */
	void close();

	/**
      * @brief			Sync calling thread with server
	  * @return			False if error occurred
      */
	bool wait();

protected:
	SOCKET serverSocket;

	/**
      * @brief			Virtual function, called when new connection is established
	  * @param	[in]	socket Client socket descryptor
	  * @return			void
      */
	virtual void incomingConnection(SOCKET socket);
};

#endif	/* _TCP_SERVER_H */
