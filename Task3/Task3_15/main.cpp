#include <iostream>

using namespace std;

void hideWords(char *str, char c);

int main()
{
	char str[200];
	cin.getline(str, 200);
	hideWords(str, 's');
	cout << str;
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