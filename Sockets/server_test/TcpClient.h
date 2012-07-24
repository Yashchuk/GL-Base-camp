/** 
  * @class	TcpClient
  * @brief	OO windows sockets wrapper 
  * Copyright (C) 2012 Vitaliy Sidenko <vitalyax@gmail.com>
  */

#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

#include <WinSock2.h>

class TcpClient
{
private:
	SOCKET socket;
	TcpClient(const TcpClient &client);
	TcpClient& operator= (const TcpClient &client);

public:

	/**
      * @brief			Ititialize with socket decriptor
      * @param	[in]	socket Socket decriptor
      */
	TcpClient(SOCKET socket);

	~TcpClient();

	/**
      * @brief			Close socket
      * @return			void
      */
	void close();

	/**
      * @brief			Connect to given IP adderess and port
	  * @param	[in]	address C-String containing IP address (e.g. "127.0.0.1")
	  * @param	[in]	port Connection port
      * @return			True if connected successfully
      */
	bool connect(const char *address, unsigned port);

	/**
      * @brief			Send data brom buffer
	  * @param	[in]	data Pointer to data buffer
	  * @param	[in]	dataSize Buffer size
      * @return			True if data was sent successfully
      */
	bool send(char *data, size_t dataSize);

	/**
      * @brief			Read data from socket
	  * @param	[in,out]	data Pointer to buffer
	  * @param	[in]	dataSize Buffer size
      * @return			Number of bytes read or -1 if error occurred
      */
	int read(char *buf, size_t bufSize);

	/**
      * @brief			Set socket decriptor
	  * @param	[in]	socket Socket decriptor
      * @return			void
      */
	void setSocketDecriptor(SOCKET socket);

	/**
      * @brief			Get socket decriptor
      * @return			Socket decriptor or NULL of socket is not conneted
      */
	SOCKET socketDecriptor();
};

#endif	/* _TCP_CLIENT_H */