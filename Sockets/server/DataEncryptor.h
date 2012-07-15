#ifndef _DATA_ENCRYPTOR_H
#define _DATA_ENCRYPTOR_H

#include <fstream>

class DataEncryptor
{
protected:
	DataEncryptor() { };
	DataEncryptor(const DataEncryptor &de) { };
	DataEncryptor& operator= (const DataEncryptor &de) { return *this; };

public:
	virtual ~DataEncryptor() { };
	virtual bool encryptData(std::fstream &original, std::fstream &result) = 0;
	virtual bool decryptData(std::fstream &original, std::fstream &result) = 0;
};

#endif	/* _DATA_ENCRYPTOR_H */