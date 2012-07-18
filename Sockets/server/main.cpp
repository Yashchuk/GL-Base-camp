#include "EncryptionServer.h"
#include "XorEncryptor.h"
#include "FileDatabase.h"
#include <iostream>

using namespace std;

int main()
{
	DataEncryptor *de = new XorEncryptor();

	UserDatabase *udb = new FileDatabase("G:\\users.txt");
	EncryptionServer *server = new EncryptionServer(de, udb, &cout);

	server->listen(4000, 10);

	server->wait();

	delete server;
	delete de;
	delete udb;
}