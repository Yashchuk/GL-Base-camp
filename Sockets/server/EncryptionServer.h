#ifndef _ENCRYPTING_SERVER_H
#define _ENCRYPTING_SERVER_H

#include "TcpServer.h"
#include "UserDatabase.h"
#include "DataEncryptor.h"
#include "TcpClient.h"
#include <cstdint>

class EncryptionServer : public TcpServer
{
private:
	UserDatabase *db;
	DataEncryptor *de;

	void readData(TcpClient *client, uint32_t size);
	bool authorize(TcpClient *client);

public:
	EncryptionServer(DataEncryptor *de, UserDatabase *db);
	~EncryptionServer();
	
protected:
	void incomingConnection(SOCKET socket);
};

#endif	/* _ENCRYPTING_SERVER_H */