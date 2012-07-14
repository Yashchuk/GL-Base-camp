#include "XorEncryptor.h"

XorEncryptor::XorEncryptor()
{
	password = "trololo";
	passSize = 7;
}

XorEncryptor::~XorEncryptor()
{
	
}

bool XorEncryptor::encryptData(char *data, size_t dataSize)
{
	for (size_t i = 0, j = 0; i < dataSize; i++, j++)
	{
		if (j == passSize)
		{
			j = 0;
		}
		data[i] ^= password[j];
	}

	return true;
}

bool XorEncryptor::decryptData(char *buf, size_t bufSize)
{
	for (size_t i = 0, j = 0; i < bufSize; i++, j++)
	{
		if (j == passSize)
		{
			j = 0;
		}
		buf[i] ^= password[j];
	}
	
	return true;
}