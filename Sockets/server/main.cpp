#include "EncryptionServer.h"
#include "XorEncryptor.h"
#include "FileDatabase.h"
#include <iostream>

using namespace std;

int main()
{
	DataEncryptor *de = new XorEncryptor();

	UserDatabase *udb = new FileDatabase("G:\\users.txt");
	EncryptionServer *server = new EncryptionServer(de, udb);

	server->listen(4000, 10);

	while (true)
	{
		Sleep(1);
	}

	delete server;
	delete de;
	delete udb;

}