#ifndef _XOR_ENCRYPTOR_H
#define _XOR_ENCRYPTOR_H

#include "DataEncryptor.h"

class XorEncryptor : public DataEncryptor
{
private:
	char *password;
	size_t passSize;

public:
	XorEncryptor();
	~XorEncryptor();
	bool encryptData(std::fstream &original, std::fstream &result);
	bool decryptData(std::fstream &original, std::fstream &result);
};

#endif	/* _XOR_ENCRYPTOR_H */
