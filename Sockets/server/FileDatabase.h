/** 
  * @class	FileDatabase
  * @brief	User database in text files
  * Copyright (C) 2012 Vitaliy Sidenko <vitalyax@gmail.com>
  */

#ifndef _FILE_DATABASE_H
#define _FILE_DATABASE_H

#include "UserDatabase.h"
#include <fstream>
#include <string>

using std::fstream;
using std::string;

class FileDatabase : public UserDatabase
{
private:
	string fname;
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

	/**
      * @brief			Add user to the database
      * @param	[in]	login User login
	  * @param	[in]	password User password
	  * @return			False if error occured or user already in the database
      */
	bool addUser(const char *login, const char *password);

	/**
      * @brief			Remove user from the database
      * @param	[in]	login User login
	  * @param	[in]	password User password
	  * @return			False if error occured or user is not in the database
      */
	bool removeUser(const char *login, const char *password);
};

#endif	/* _FILE_DATABASE_H */