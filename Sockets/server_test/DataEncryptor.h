/** 
  * @class	DataEncryptor
  * @brief	Interface for classes providing encryption logic
  * Copyright (C) 2012 Vitaliy Sidenko <vitalyax@gmail.com>
  */

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

	/**
      * @brief			Encrypt file
      * @param	[in]	original Original file stream
	  * @param	[in, out]	result Encrypted file stream
	  * @return			False if error occurred
      */
	virtual bool encryptData(std::fstream &original, std::fstream &result) = 0;

	/**
      * @brief			Dencrypt file
      * @param	[in]	original Encrypted file stream
	  * @param	[in, out]	result Decrypted file stream
	  * @return			False if error occurred
      */
	virtual bool decryptData(std::fstream &original, std::fstream &result) = 0;
};

#endif	/* _DATA_ENCRYPTOR_H */