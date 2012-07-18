#include "EncryptionServer.h"
#include "TempFile.h"
#include <cstdint>

#define CHUNK_SIZE 2048

enum
{
	ENCRYPT = 1,
	DECRYPT = 2,
	LOGIN = 4,
	OK = 8,
	ERR = 16,
	QUIT = 32
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

	char mask;

	client->read(&mask, 1);

	if (mask & LOGIN)
	{
		mask = OK;
		client->send(&mask, 1);

		if (authorize(client))
		{
			mask = OK;
			client->send(&mask, 1);

			while (true)
			{
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

				mask = 0;

				Sleep(1);
			}

			(*log) << client->socketDecriptor() << ": User disconnected" << std::endl;
		}
		else
		{
			mask = ERR;
			client->send(&mask, 1);
		}
	}

	delete client;
}

bool EncryptionServer::authorize(TcpClient *client)
{
	uint32_t size;
	bool res = false;

	if (client->read((char*)&size, 4) <= 0)
	{
		return res;
	}

	char *buf;
	try
	{
		buf = new char[size];
	}
	catch(...)
	{
		return false;
	}

	if (client->read(buf, size) > 0)
	{
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

		if (ok && db->hasUser(buf, buf + passOffset))
		{
			res = true;

			(*log) << client->socketDecriptor() << ": User " << 
				buf << " connected" << std::endl; 
		}
	}

	delete[] buf;

	return res;
}

bool EncryptionServer::encrypt(TcpClient *client, bool decrypt)
{
	uint32_t size;
	bool res = true;

	if (client->read((char*)&size, 4) <= 0)
	{
		return false;
	}

	char *buf;
	try
	{
		buf = new char[CHUNK_SIZE];
	}
	catch(std::bad_alloc)
	{
		return false;
	}

	TempFile *fileFrom = new TempFile();
	TempFile *fileTo = new TempFile();

	if (fileFrom->getStream()->is_open() && fileTo->getStream()->is_open())
	{
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

		bool ok = decrypt ? de->decryptData(*fileFrom->getStream(), *fileTo->getStream())
			: de->encryptData(*fileFrom->getStream(), *fileTo->getStream());

		if (!ok)
		{
			res = false;
		}
		else
		{
			fileTo->getStream()->seekg(0, std::ios::beg);
			uint32_t tmp = fileTo->getStream()->tellg();
			fileTo->getStream()->seekg(0, std::ios::end);
			size = fileTo->getStream()->tellg();
			size -= tmp;
			fileTo->getStream()->seekg(0, std::ios::beg);

			if (client->send((char*)&size, 4))
			{
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

	delete fileFrom;
	delete fileTo;
	delete[] buf;
	
	return res;
}