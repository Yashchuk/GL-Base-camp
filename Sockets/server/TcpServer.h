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
	bool listen(unsigned port, unsigned maxPendingConnections);
	void close();
	bool wait();

protected:
	SOCKET serverSocket;

	virtual void incomingConnection(SOCKET socket);
};

#endif	/* _TCP_SERVER_H */
