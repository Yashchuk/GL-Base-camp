#include "TcpClient.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <Windows.h> 

#define CHUNK_SIZE 2048

using namespace std;

SOCKET createSocket();
bool sendFile(TcpClient *client, const char *fname, const char *fname2);

enum
{
	ENCRYPT = 1,
	DECRYPT = 2,
	LOGIN = 4,
	OK = 8,
	FAIL = 16
};

int main()
{	
	SOCKET socket = createSocket();
	if (!socket)
	{
		WSACleanup();
		return 1;
	}
	TcpClient client(socket);
	if (!client.connect("127.0.0.1", 4000))
	{
		cout << "Connection failed" << endl;
	}

	char mask;

	mask = LOGIN;
	client.send(&mask, 1);

	client.read(&mask, 1);

	if (mask & OK)
	{
		unsigned size = sizeof("user\n525") + 1;
		client.send((char*)&size, 4);
		client.send("user4\n525", size);

		client.read(&mask, 1);

		if (mask & OK)
		{
			cout << "Authorized" << endl;

			cout << boolalpha << sendFile(&client, "G:\\Task 5.dat", "G:\\Task 5_2.docx");
		}
	}

	WSACleanup();
	return 0;
}

SOCKET createSocket()
{
	WSADATA wsaData;
	if (WSAStartup(0x101, &wsaData))
	{
		return NULL;
	}

	SOCKET client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(client == SOCKET_ERROR)
	{
		return NULL;
	}

	return client;
}

bool sendFile(TcpClient *client, const char *fname, const char *fname2)
{
	fstream file(fname, std::ios_base::binary | std::ios_base::in | std::ios_base::out);

	if (!file.is_open())
	{
		return false;
	}

	char mask = ENCRYPT;
	client->send(&mask, 1);

	if (client->read(&mask, 1) == -1 || !(mask & OK))
	{
		return false;
	}

	uint32_t size = 0;
	file.seekg(0, std::ios::beg);
	uint32_t tmp = file.tellg();
	file.seekg(0, std::ios::end);
	size = file.tellg();
	size -= tmp;

	client->send((char*)&size, 4);

	char *buf = new char[CHUNK_SIZE];
	file.seekg(0, std::ios::beg);
	while (file.good())
	{
		file.read(buf, CHUNK_SIZE);
		if (!client->send(buf, file.gcount()))
		{
			file.close();
			delete[] buf;
			return false;
		}
	}

	file.close();

	fstream file2(fname2, std::ios::binary | std::ios::in | std::ios::out | ios::trunc);
	client->read((char*)&size, 4);
	uint32_t totalReceived = 0;
	int received;
	while (totalReceived < size)
	{
		received = client->read(buf, CHUNK_SIZE);
		if (received == -1)
		{
			file2.close();
			delete[] buf;
			return false;
		}

		file2.write(buf, received);
		totalReceived += received;
	}

	file2.close();
	delete[] buf;

	return true;
}