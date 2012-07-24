#include "EncryptionServer.h"
#include "TempFile.h"
#include <cstdint>

#define CHUNK_SIZE 2048		// Buffer size

enum
{
	ENCRYPT = 1,      // Encrypt data
	DECRYPT = 2,      // Decrypt data
	LOGIN = 4,        // Authorize user
	OK = 8,           // Operation successfull
	ERR = 16,         // Error
	QUIT = 32,        // Disconnect
	ADD_USER = 64,    // Add new user
};

EncryptionServer::EncryptionServer(DataEncryptor *de, UserDatabase *db, std::ostream *log)
{
	this->de = de;
	this->db = db;
	this->log = log;
}

EncryptionServer::~EncryptionServer()
{
}

void EncryptionServer::incomingConnection(SOCKET socket)
{
	TcpClient *client = new TcpClient(socket);

	bool admin = false;
	char mask;

	// Get command from client
	client->read(&mask, 1);

	if (mask & LOGIN)
	{
		// Allow to login
		mask = OK;
		client->send(&mask, 1);

		int res = authorize(client);
		if (res)
		{
			if (res == 2)
			{
				admin = true;
			}
			
			// Send authorization confirmation
			mask = OK;
			client->send(&mask, 1);

			while (true)
			{
				// Get next command from client
				if (client->read(&mask, 1) == -1)
				{
					break;
				}
				
				if (mask & QUIT)
				{
					break;
				}
				else if (mask & ENCRYPT)
				{
					/* Data encrypting */

					// Send encryption confirmation
					mask = OK;
					client->send(&mask, 1);

					(*log) << client->socketDecriptor() << 
						": Encrypting data..." << std::endl;
					if (!encrypt(client, false))
					{
						(*log) << client->socketDecriptor() << 
							": Error occured while encrypting data" << std::endl; 
					}
					else
					{
						(*log) << client->socketDecriptor() << 
							": Encryption finished" << std::endl; 
					}
				}
				else if (mask & DECRYPT)
				{
					/* Data encrypting */
					
					// Send decryption confirmation
					mask = OK;
					client->send(&mask, 1);

					(*log) << client->socketDecriptor() << 
						": Decrypting data..." << std::endl; 
					if (!encrypt(client, true))
					{
						(*log) << client->socketDecriptor() << 
							": Error occured while decrypting data" << std::endl; 
					}
					else
					{
						(*log) << client->socketDecriptor() << 
							": Decryption finished" << std::endl; 
					}
				}
				else if (mask & ADD_USER)
				{
					/* Add new user */
					
					// Check if user is admin
					if (admin)
					{
						mask = OK;
						client->send(&mask, 1);

						if (addUser(client))
						{
							mask = OK;
						}
						else
						{
							mask = ERR;
						}

						client->send(&mask, 1);
					}
					else
					{
						mask = ERR;
						client->send(&mask, 1);
					}
				}

				mask = 0;

				Sleep(1);
			}

			(*log) << client->socketDecriptor() << ": User disconnected" << std::endl;
		}
		else
		{
			// Send error message
			mask = ERR;
			client->send(&mask, 1);
		}
	}

	delete client;
}

bool EncryptionServer::addUser(TcpClient *client)
{
	uint32_t size;
	bool res = false;

	// Acquire incoming data size
	if (client->read((char*)&size, 4) <= 0)
	{
		return false;
	}

	// Create temporary buffer
	char *buf;
	try
	{
		buf = new char[size];
	}
	catch(...)
	{
		return false;
	}

	// Get user login and password
	if (client->read(buf, size) > 0)
	{
		// Separate them
		bool ok = false;
		uint32_t passOffset = 0;
		for (uint32_t i = 0; i < size; i++)
		{
			if (buf[i] == '\n')
			{
				ok = true;
				buf[i] = '\0';
				passOffset = i + 1;
				break;
			}
		}

		// Try to add user
		if (ok)
		{
			res = db->addUser(buf, buf + passOffset, false);
		}
	}

	delete[] buf;

	return res;
}

int EncryptionServer::authorize(TcpClient *client)
{
	uint32_t size;
	int res = 0;

	// Acquire incoming data size
	if (client->read((char*)&size, 4) <= 0)
	{
		return 0;
	}

	// Create temporary buffer
	char *buf;
	try
	{
		buf = new char[size];
	}
	catch(...)
	{
		return 0;
	}

	// Get user login and password
	if (client->read(buf, size) > 0)
	{
		// Separate them
		bool ok = false;
		uint32_t passOffset = 0;
		for (uint32_t i = 0; i < size; i++)
		{
			if (buf[i] == '\n')
			{
				ok = true;
				buf[i] = '\0';
				passOffset = i + 1;
				break;
			}
		}

		// Check in database
		if (ok)
		{
			res = db->hasUser(buf, buf + passOffset);

			if (res)
			{
				(*log) << client->socketDecriptor() << ": User " << 
					buf << " connected" << std::endl;
			}
		}
	}

	delete[] buf;

	return res;
}

bool EncryptionServer::encrypt(TcpClient *client, bool decrypt)
{
	uint32_t size;
	bool res = true;

	// Acquire incoming data size
	if (client->read((char*)&size, 4) <= 0)
	{
		return false;
	}

	// Create temporary buffer
	char *buf;
	try
	{
		buf = new char[CHUNK_SIZE];
	}
	catch(std::bad_alloc)
	{
		return false;
	}

	// Create two temporary files to save original end resulting data
	TempFile *fileFrom = new TempFile();
	TempFile *fileTo = new TempFile();

	if (fileFrom->getStream()->is_open() && fileTo->getStream()->is_open())
	{
		// Read data from socket to file using temporary buffer
		uint32_t totalReceived = 0;
		int received;
		while (totalReceived < size)
		{
			received = client->read(buf, CHUNK_SIZE);
			if (received == -1)
			{
				res = false;
				break;
			}

			fileFrom->getStream()->write(buf, received);
			totalReceived += received;
		}

		fileFrom->getStream()->flush();

		// Decrypt or encrypt downloaded data (depending on 'decrypt' argument)
		// fileTo should contain result of operation, if ok=true
		bool ok = decrypt ? de->decryptData(*fileFrom->getStream(), *fileTo->getStream())
			: de->encryptData(*fileFrom->getStream(), *fileTo->getStream());

		if (!ok)
		{
			res = false;
		}
		else
		{
			// Get created file size
			fileTo->getStream()->seekg(0, std::ios::beg);
			uint32_t tmp = fileTo->getStream()->tellg();
			fileTo->getStream()->seekg(0, std::ios::end);
			size = fileTo->getStream()->tellg();
			size -= tmp;

			// Put get pointer in the beginning
			fileTo->getStream()->seekg(0, std::ios::beg);

			// Send file size
			if (client->send((char*)&size, 4))
			{
				// Read and send file in chunks of 'CHUNK_SIZE' bytes
				res = true;
				while (fileTo->getStream()->good())
				{
					fileTo->getStream()->read(buf, CHUNK_SIZE);
					if (!client->send(buf, fileTo->getStream()->gcount()))
					{
						res = false;
						break;
					}
				}
			}
		}
	}
	else
	{
		res = false;
	}

	// Delete temporary files and gree buffer memory
	delete fileFrom;
	delete fileTo;
	delete[] buf;
	
	return res;
}