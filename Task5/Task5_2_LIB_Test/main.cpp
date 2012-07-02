#include "Set.h"
#include <iostream>
#include <string>

using namespace std;

char mostOccurringCharacter(string &str);

int main()
{
	string s1, s2;
	
	cout << "Enter two strings" << endl;
	getline(cin, s1);
	getline(cin, s2);

	cout << mostOccurringCharacter(s1) << mostOccurringCharacter(s2) << endl;

	return 0;
}

char mostOccurringCharacter(string &str)
{
	unsigned setId = addSet();

	for (int i = 0; i < str.length(); i++)
	{
		addElement(setId, str[i]);
	}

	SetElement *pData = getData(setId);

	unsigned l = dataSize(setId);
	unsigned max = 0;
	char c = 0;
	for (int i = 0; i < l; i++)
	{
		if (pData[i].nOccurrences > max)
		{
			max = pData[i].nOccurrences;
			c = pData[i].number;
		}
	}

	removeSet(setId);

	return c;
}