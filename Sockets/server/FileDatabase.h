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
	FileDatabase(const char *fileName);
	~FileDatabase();
	bool hasUser(const char *login, const char *password);
	bool adduser(const char *login, const char *password);
	bool removeUser(const char *login, const char *password);
};

#endif	/* _FILE_DATABASE_H */