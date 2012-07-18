/** 
  * @class	FileDatabase
  * @brief	User database in text files
  * Copyright (C) 2012 Vitaliy Sidenko <vitalyax@gmail.com>
  */

#ifndef _FILE_DATABASE_H
#define _FILE_DATABASE_H

#include "UserDatabase.h"
#include <fstream>

using std::fstream;

class FileDatabase : public UserDatabase
{
private:
	fstream file;

public:

	/**
      * @brief			Initialize object with given data file name
      * @param	[in]	fileName File name
      */
	FileDatabase(const char *fileName);

	~FileDatabase();
	
	/**
      * @brief			Check if database contains user with given password
      * @param	[in]	login User login
	  * @param	[in]	password User password
	  * @return			True if user is in database
      */
	bool hasUser(const char *login, const char *password);
};

#endif	/* _FILE_DATABASE_H */