#include "XorEncryptor.h"
#include <iostream>

XorEncryptor::XorEncryptor()
{
	password = "trololo";
	passSize = 7;
}

XorEncryptor::~XorEncryptor()
{
}

bool XorEncryptor::encryptData(std::fstream &original, std::fstream &result)
{
	if (!original.is_open() || !result.is_open())
	{
		return false;
	}

	original.seekg(0, std::ios::beg);
	result.seekp(0, std::ios::beg);

	char c = 0;
	unsigned i = 0;
	while (original.good())
	{
		original.read(&c, 1);
		c ^= password[i];
		if(original.gcount() > 0)
		{
			result.write(&c, 1);
		}

		if (++i == passSize)
		{
			i = 0;
		}
	}

	original.seekg(0, std::ios::beg);
	result.seekg(0, std::ios::beg);
	result.flush();

	return true;
}

bool XorEncryptor::decryptData(std::fstream &original, std::fstream &result)
{
	return encryptData(original, result);
}