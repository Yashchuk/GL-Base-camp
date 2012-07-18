/** 
  * @class	EncryptionServer
  * @brief	Encryption and decryption server
  * Copyright (C) 2012 Vitaliy Sidenko <vitalyax@gmail.com>
  */

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

	/**
      * @brief			Enrypt or decrypt user data
	  * @param	[in]	client Pointer to client object
	  * @param	[in]	decrypt Set to true for decryption of false for encryption
	  * @return			False if error occurred
      */
	bool encrypt(TcpClient *client, bool decrypt);

	/**
      * @brief			Try authorize client
	  * @param	[in]	client Pointer to client object
	  * @return			False if client is not in database of error occurred
      */
	bool authorize(TcpClient *client);

public:

	/**
      * @brief			Initialze server new server object
      * @param	[in]	de Pointer to data encryptor provider
	  * @param	[in]	db Pointer to user database provider
	  * @param	[in]	log Pointer Logging stream
      */
	EncryptionServer(DataEncryptor *de, UserDatabase *db, std::ostream *log);

	~EncryptionServer();
	
protected:

	/**
      * @brief			Virtual function, called when new connection is established
	  * @param	[in]	socket Client socket descryptor
	  * @return			void
      */
	void incomingConnection(SOCKET socket);
};

#endif	/* _ENCRYPTION_SERVER_H */