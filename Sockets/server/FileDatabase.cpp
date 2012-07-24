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

int FileDatabase::hasUser(const char *login, const char *password)
{
	if (!file.is_open() || !login || !password)
	{
		return 0;
	}

	string rank, name, pass;

	file.seekg(0, std::ios::beg);

	while (file.good())
	{
		file >> rank >> name >> pass;
		if (name == login && pass == password)
		{
			if (rank == "1")
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
	}

	return 0;
}

bool FileDatabase::addUser(const char *login, const char *password, bool admin)
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

	file << (admin ? "1 " : "0 ") << login << " " << password << "\n";

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
	string rank, name, pass;

	fstream tempFile(tempFileName, fstream::in | fstream::out | fstream::trunc);
	if (tempFile.is_open())
	{
		file.clear();
		file.seekg(0, std::ios::beg);

		file >> rank >> name >> pass;

		while (file.good())
		{
			if (name == login && pass == password)
			{
				file >> name >> pass;
				continue;
			}

			tempFile << rank << " " << name << " " << pass << "\n";

			file >> rank >> name >> pass;
		}

		file.close();
		tempFile.close();

		DeleteFile(fname.c_str());

		MoveFile(tempFileName.c_str(), fname.c_str());

		file.open(fname.c_str(), fstream::in | fstream::out | fstream::app);
	}
}