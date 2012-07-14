#include "EncryptionServer.h"
#include <iostream>
#include <cstdio>

#define CHUNK_SIZE 2048
#define TMP_FILE_SIZE 2048

#undef ERROR

enum
{
	ENCRYPT = 1,
	DECRYPT = 2,
	LOGIN = 4,
	OK = 8,
	ERROR = 16
};

EncryptionServer::EncryptionServer(DataEncryptor *de, UserDatabase *db)
{
	this->de = de;
	this->db = db;
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
			client->send(&mask, 1);
		}
		else
		{
			mask = ERROR;
			client->send(&mask, 1);
			delete client;
			return;
		}

		client->read(&mask, 1);

		if (mask & ENCRYPT)
		{
			mask = OK;
			client->send(&mask, 1);
			
			uint32_t dataSize;
			client->read((char*)&dataSize, sizeof(uint32_t));
			readData(client, dataSize);
		}
		else if (mask & DECRYPT)
		{

		}
	}

	delete client;
}

bool EncryptionServer::authorize(TcpClient *client)
{
	uint32_t size;
	bool res = false;

	if (client->read((char*)&size, sizeof(uint32_t)) > 0)
	{
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
			}
		}

		delete[] buf;
	}

	return res;
}

void EncryptionServer::readData(TcpClient *client, uint32_t size)
{
	FILE *temp = tmpfile();

	char *buf = new char[CHUNK_SIZE];
	
	uint32_t received = CHUNK_SIZE;
	uint32_t totalReceived = 0;

	while (received == size)
	{
		received = client->read(buf, CHUNK_SIZE);
		totalReceived += received;
		fwrite(buf, 1, received, temp);
	}

	fclose(temp);
	delete[] buf;
}