/** 
  * @class	UserDatabase
  * @brief	Interface for classes containing user data
  * Copyright (C) 2012 Vitaliy Sidenko <vitalyax@gmail.com>
  */

#ifndef _USER_DATABASE_H
#define _USER_DATABASE_H

class UserDatabase
{
protected:
	UserDatabase() { };
	UserDatabase(const UserDatabase &db) { };
	UserDatabase& operator= (const UserDatabase &db) { return *this; };

public:

	/**
      * @brief			Check if database contains user with given password
      * @param	[in]	login User login
	  * @param	[in]	password User password
	  * @return			True if user is in database
      */
	virtual bool hasUser(const char *login, const char *password) = 0;

	/**
      * @brief			Add user to the database
      * @param	[in]	login User login
	  * @param	[in]	password User password
	  * @return			False if error occured or user already in the database
      */
	virtual bool addUser(const char *login, const char *password) = 0;

	/**
      * @brief			Remove user from the database
      * @param	[in]	login User login
	  * @param	[in]	password User password
	  * @return			False if error occured or user is not in the database
      */
	virtual bool removeUser(const char *login, const char *password) = 0;

	virtual ~UserDatabase() { };
};

#endif	/* _USER_DATABASE_H */