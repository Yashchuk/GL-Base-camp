#include "Stack.h"
#include <iostream>
#define MAX_LEN 100

using namespace std;

bool reverseString(char *pChString);

int main()
{
	char buf[MAX_LEN];

	while (true)
	{
		cin.getline(buf, MAX_LEN);
		if (!reverseString(buf))
		{
			continue;
		}
		cout << buf << endl;
	}
}

bool reverseString(char *pChString)
{
	if (!pChString)
	{
		return false;
	}

	char *pStart = pChString;
	clearStack();

	while (*pChString)
	{
		if (!pushCharacter(*pChString))
		{
			clearStack();
			return false;
		}

		pChString++;
	}

	while (pStart < pChString)
	{
		*pStart = popCharacter();
		pStart++;
	}

	return true;
}