/** 
  * @class	XorEncryptor
  * @brief	Iplementation of simple XOR-encryptor
  * Copyright (C) 2012 Vitaliy Sidenko <vitalyax@gmail.com>
  */

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

	/**
      * @brief			Encrypt file
      * @param	[in]	original Original file stream
	  * @param	[in, out]	result Encrypted file stream
	  * @return			False if error occurred
      */
	bool encryptData(std::fstream &original, std::fstream &result);

	/**
      * @brief			Dencrypt file
      * @param	[in]	original Encrypted file stream
	  * @param	[in, out]	result Decrypted file stream
	  * @return			False if error occurred
      */
	bool decryptData(std::fstream &original, std::fstream &result);
};

#endif	/* _XOR_ENCRYPTOR_H */
