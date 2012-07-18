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