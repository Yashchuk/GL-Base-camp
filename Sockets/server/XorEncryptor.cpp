#include "XorEncryptor.h"

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
		original >> c;
		result << (c ^ password[i]);

		if (++i == passSize)
		{
			i = 0;
		}
	}

	return true;
}

bool XorEncryptor::decryptData(std::fstream &original, std::fstream &result)
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
		original >> c;
		result << (c ^ password[i]);

		if (++i == passSize)
		{
			i = 0;
		}
	}

	return true;
}