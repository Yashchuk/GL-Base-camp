#include <iostream>
#include <cctype>
#define MAX_LEN 128

using namespace std;

void swapWords(char *pStr, unsigned word1, unsigned word2);

int main()
{
	char *pBuf = new char[128];
	unsigned w1, w2;

	cin.getline(pBuf, MAX_LEN);
	cin >> w1 >> w2;

	swapWords(pBuf, w1, w2);

	cout << pBuf << endl;
}

void swapWords(char *pStr, unsigned word1, unsigned word2)
{
	char *pWord1Start = 0, *pWord1End;
	char *pWord2Start = 0, *pWord2End;

	unsigned i = 0;
	while(*pStr)
	{
		if(*pStr != ' ')
		{
			i++;

			if(i == word1)
				pWord1Start = pStr;
			else if(i == word2)
				pWord2Start = pStr;

			while(*pStr && *pStr != ' ')
				pStr++;

			if(i == word1)
				pWord1End = pStr;
			else if(i == word2)
				pWord2End = pStr;
		}
		
		pStr++;
	}

	if(!pWord1Start || !pWord2Start)
		return;

	char *pBuf;
	unsigned len1 = pWord1End - pWord1Start;
	unsigned len2 = pWord2End - pWord2Start;
	unsigned lenDiff = 0;

	if(len1 < len2)
	{
		lenDiff = len2 - len1;

		pBuf = new char[lenDiff];

		memcpy(pBuf, pWord2End - lenDiff, lenDiff);
		memcpy(pWord1End + lenDiff, pWord1End, (pWord2End - lenDiff) - pWord1End);

		for(int i = 0; i < len1; i++)
		{
			char temp = *(pWord1Start + i);
			*(pWord1Start + i) = *(pWord2Start + i + lenDiff);
			*(pWord2Start + i + lenDiff) = temp;
		}

		memcpy(pWord1End, pBuf, lenDiff);
	}
	else
	{
		lenDiff = len1 - len2;

		pBuf = new char[lenDiff];

		memcpy(pBuf, pWord1End - lenDiff, lenDiff);
	}
	
	delete[] pBuf;
}