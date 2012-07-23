#include "FileDatabase.h"
#include <Windows.h>

FileDatabase::FileDatabase(const char *fileName)
{
	file.open(fileName, fstream::in | fstream::out | fstream::app);
	if (file.is_open())
	{
		fname = fileName;
	}
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

bool FileDatabase::addUser(const char *login, const char *password)
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

	file << login << " " << password << "\n";

	file.flush();

	return true;
}

bool FileDatabase::removeUser(const char *login, const char *password)
{
	if (!hasUser(login, password))
	{
		return false;
	}

	string tempFileName = fname + "tmp";
	string name, pass;

	fstream tempFile(tempFileName, fstream::in | fstream::out | fstream::trunc);
	if (tempFile.is_open())
	{
		file.clear();
		file.seekg(0, std::ios::beg);

		file >> name >> pass;

		while (file.good())
		{
			if (name == login && pass == password)
			{
				file >> name >> pass;
				continue;
			}

			tempFile << name << " " << pass << "\n";

			file >> name >> pass;
		}

		file.close();
		tempFile.close();

		DeleteFile(fname.c_str());

		MoveFile(tempFileName.c_str(), fname.c_str());

		file.open(fname.c_str(), fstream::in | fstream::out | fstream::app);
	}
}