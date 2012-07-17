#ifndef _ENCRYPTION_SERVER_H
#define _ENCRYPTION_SERVER_H

#include "TcpServer.h"
#include "UserDatabase.h"
#include "DataEncryptor.h"
#include "TcpClient.h"
#include <ostream>

class EncryptionServer : public TcpServer
{
private:
	UserDatabase *db;
	DataEncryptor *de;
	std::ostream *log;

	bool encrypt(TcpClient *client, bool decrypt);
	bool authorize(TcpClient *client);

public:
	EncryptionServer(DataEncryptor *de, UserDatabase *db, std::ostream *log = NULL);
	~EncryptionServer();
	
protected:
	void incomingConnection(SOCKET socket);
};

#endif	/* _ENCRYPTION_SERVER_H */