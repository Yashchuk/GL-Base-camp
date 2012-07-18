#include "TempFile.h"
#include <Windows.h>

HANDLE hMutex = NULL;

TempFile::TempFile()
{
	if (!hMutex)
	{
		hMutex = CreateMutex(0, FALSE, NULL);
	}

	if (hMutex)
	{
		WaitForSingleObject(hMutex, INFINITE);
	}
	
	int res = CreateDirectory("tmp", NULL);
	if (!res && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		return;
	}

	// Create buffer for conaining generated temporary file name
	try
	{
		fileName = new char[MAX_PATH];
	}
	catch (std::bad_alloc)
	{
		fileName = NULL;
		return;
	}

	// Get temporary file name
    if (GetTempFileName("tmp", "tmp", 0, fileName))
    {
		// Create file
		HANDLE hTempFile = CreateFile(fileName, GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hTempFile != INVALID_HANDLE_VALUE) 
		{
			CloseHandle(hTempFile);
			stream.open(fileName, std::ios_base::binary |  std::ios_base::in |  std::ios_base::out);
		}
    }

	if (hMutex)
	{
		ReleaseMutex(hMutex);
	}
}

TempFile::~TempFile()
{
	// Close stream and delete file
	if (fileName && stream.is_open())
	{
		stream.close();
		DeleteFile(fileName);
		delete[] fileName;
	}
}

std::fstream* TempFile::getStream()
{
	if (stream.is_open())
	{
		return &stream;
	}

	return NULL;
}
