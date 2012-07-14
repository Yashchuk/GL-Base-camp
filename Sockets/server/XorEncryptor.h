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
	bool encryptData(char *data, size_t dataSize);
	bool decryptData(char *buf, size_t bufSize);
};

#endif	/* _XOR_ENCRYPTOR_H */
