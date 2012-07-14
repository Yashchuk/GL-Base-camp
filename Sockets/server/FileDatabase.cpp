#include "FileDatabase.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

FileDatabase::FileDatabase(const char *fileName)
{
	file.open(fileName, fstream::in | fstream::out | fstream::app);
}

FileDatabase::~FileDatabase()
{
	file.close();
}

bool FileDatabase::hasUser(const char *login, const char *password)
{
	if (!file.is_open() || !login || !password)
	{
		return false;
	}

	string buf;

	file.seekg(0, std::ios::beg);

	while (file.good())
	{
		file >> buf;
		if (buf == login)
		{
			file >> buf;
			if (buf == password)
			{
				return true;
			}
		}
	}

	return false;
}

bool FileDatabase::adduser(const char *login, const char *password)
{
	if (!file.is_open() || !login || !password)
	{
		return false;
	}
	
	if (hasUser(login, password))
	{
		return false;
	}

	file.clear();
	file.seekp(0, std::ios::end);

	file << login << ' ' << password << std::endl;
	if (file.fail())
	{
		return false;
	}

	return true;
}

bool FileDatabase::removeUser(const char *login, const char *password)
{
	return false;
}
