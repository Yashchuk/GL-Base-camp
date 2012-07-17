#ifndef _USER_DATABASE_H
#define _USER_DATABASE_H

class UserDatabase
{
protected:
	UserDatabase() { };
	UserDatabase(const UserDatabase &db) { };
	UserDatabase& operator= (const UserDatabase &db) { return *this; };

public:
	virtual bool hasUser(const char *login, const char *password) = 0;
	virtual ~UserDatabase() { };
};

#endif	/* _USER_DATABASE_H */