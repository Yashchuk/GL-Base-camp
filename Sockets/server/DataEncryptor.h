#ifndef _DATA_ENCRYPTOR_H
#define _DATA_ENCRYPTOR_H

class DataEncryptor
{
protected:
	DataEncryptor() { };
	DataEncryptor(const DataEncryptor &de) { };
	DataEncryptor& operator= (const DataEncryptor &de) { return *this; };

public:
	virtual ~DataEncryptor() { };
	virtual bool encryptData(char *data, size_t dataSize) = 0;
	virtual bool decryptData(char *buf, size_t bufSize) = 0;
};

#endif	/* _DATA_ENCRYPTOR_H */