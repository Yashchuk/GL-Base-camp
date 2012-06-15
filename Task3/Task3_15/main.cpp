#include <iostream>
#define MAX_LEN 200

using namespace std;

void hideWords(char *str, char c);

int main()
{
	char *pStrBuf = new char[MAX_LEN];
	char c;

	for(;;)
	{
		
		cout << "Input sentence (\"e\" to exit): " << endl;
		cin.getline(pStrBuf, 200);

		if(!strcmp(pStrBuf, "e"))
			break;

		cout << "Input character: " << endl;
		cin >> c;

		hideWords(pStrBuf, c);

		cout << "Result: " << endl << pStrBuf << endl;
	}

	delete[] pStrBuf;
	return 0;
}

void hideWords(char *pStr, char c)
{
	if(!pStr)
		return;

	while(*pStr)
	{
		if(*pStr != ' ')
		{
			char *pStart = pStr;
			bool hide = false;

			while(*pStr && (*pStr != ' '))
			{
				if(*pStr == c)
					hide = true;

				pStr++;
			}
			
			if(hide)
				memset(pStart, '*', pStr - pStart); 
		}

		pStr++;
	}
}