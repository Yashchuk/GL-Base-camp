#ifndef _ENCRYPTION_SERVER_H
#define _ENCRYPTION_SERVER_H

#include "TcpServer.h"
#include "UserDatabase.h"
#include "DataEncryptor.h"
#include "TcpClient.h"

class EncryptionServer : public TcpServer
{
private:
	UserDatabase *db;
	DataEncryptor *de;

	bool encrypt(TcpClient *client);
	bool decrypt(TcpClient *client);
	bool authorize(TcpClient *client);

public:
	EncryptionServer(DataEncryptor *de, UserDatabase *db);
	~EncryptionServer();
	
protected:
	void incomingConnection(SOCKET socket);
};

#endif	/* _ENCRYPTION_SERVER_H */