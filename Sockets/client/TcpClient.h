#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H
#include <WinSock2.h>

class TcpClient
{
private:
	SOCKET socket;

public:
	TcpClient(SOCKET socket);
	TcpClient(const TcpClient &client);
	~TcpClient();
	TcpClient& operator= (const TcpClient &client);
	void close();
	bool connect(const char *address, unsigned port);
	bool send(char *data, size_t dataSize);
	int read(char *buf, size_t bufSize);
	void setSocketDecriptor(SOCKET socket);
	SOCKET socketDecriptor();
};

#endif	/* _TCP_CLIENT_H */