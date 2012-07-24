#ifndef _TMP_FILE_H
#define _TMP_FILE_H

#include <fstream>

class TempFile
{
private:
	char *fileName;
	std::fstream stream;

public:
	TempFile();
	~TempFile();
	std::fstream* getStream();
};

#endif	/* _TMP_FILE_H */