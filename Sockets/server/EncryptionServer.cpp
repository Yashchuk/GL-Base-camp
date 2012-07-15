#include "EncryptionServer.h"
#include <iostream>
#include <cstdio>
#include <cstdint>

#define CHUNK_SIZE 2048
#define TMP_NAME_LEN 128

#undef ERROR

enum
{
	ENCRYPT = 1,
	DECRYPT = 2,
	LOGIN = 4,
	OK = 8,
	ERROR = 16,
	QUIT = 32
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
			mask = OK;
			client->send(&mask, 1);

			while (true)
			{
				client->read(&mask, 1);
				
				if (mask & QUIT)
				{
					break;
				}
				else if (mask & ENCRYPT)
				{
					encrypt(client);
				}
				else if (mask & DECRYPT)
				{
					decrypt(client);
				}

				Sleep(1);
			}
		}
		else
		{
			mask = ERROR;
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
		}
	}

	delete[] buf;

	return res;
}

bool EncryptionServer::encrypt(TcpClient *client)
{
	uint32_t size;
	bool res = true;

	if (client->read((char*)&size, 4) <= 0)
	{
		return false;
	}

	char *buf;
	char *fname1, *fname2;
	try
	{
		buf = new char[CHUNK_SIZE];
		fname1 = new char[TMP_NAME_LEN];
		fname2 = new char[TMP_NAME_LEN];
	}
	catch(std::bad_alloc)
	{
		return false;
	}

	tmpnam_s(fname1, TMP_NAME_LEN);
	std::fstream fileFrom(fname1, std::ios_base::binary | std::ios_base::in, std::ios_base::out);
	tmpnam_s(fname2, TMP_NAME_LEN);
	std::fstream fileTo(fname2, std::ios_base::binary | std::ios_base::in, std::ios_base::out);

	if (fileFrom.is_open() && fileTo.is_open())
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

			fileFrom.write(buf, received);
			totalReceived += received;
		}

		if (!de->encryptData(fileFrom, fileTo))
		{
			res = false;
		}
		else
		{
			fileTo.seekg(0, std::ios::beg);

			uint32_t tmp = fileTo.tellg();
			fileTo.seekg(0, std::ios::end);
			size = fileTo.tellg();
			size -= tmp;

			client->send((char*)&size, 4);

			res = true;
			while (fileTo.good())
			{
				fileTo.read(buf, CHUNK_SIZE);
				if (!client->send(buf, CHUNK_SIZE))
				{
					res = false;
					break;
				}
			}
		}
	}
	else
	{
		res = false;
	}

	fileFrom.close();
	remove(fname1);

	fileTo.close();
	remove(fname2);

	delete[] buf;
	delete[] fname1;
	delete[] fname2;
	
	return res;
}

bool EncryptionServer::decrypt(TcpClient *client)
{
	return true;
}