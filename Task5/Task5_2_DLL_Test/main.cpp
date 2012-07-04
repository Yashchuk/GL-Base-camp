#include "Set.h"
#include <iostream>
#include <string>

using namespace std;

char mostOccurringCharacter(string &str);

bool areEqual(string &str1, string &str2);

bool containAllCharacters(string &str1, string &str2);

int main()
{
	string s1, s2;
	
	if (!loadUpDll())
	{
		return 1;
	}

	cout << "Enter two strings" << endl;
	getline(cin, s1);
	getline(cin, s2);

	cout << "Most occurring character in first string: " << mostOccurringCharacter(s1) << endl;
	cout << "Most occurring character in second string: " << mostOccurringCharacter(s2) << endl;

	cout << "Strings are " << (areEqual(s1, s2) ? "equal" : "not equal") << endl;

	cout << "Strings " << (containAllCharacters(s1, s2) ? "have " : "dont have ") << "the same set of characters" << endl;

	unloadDll();

	return 0;
}

bool containAllCharacters(string &str1, string &str2)
{
	unsigned setId1 = addSet();
	unsigned setId2 = addSet();

	for (int i = 0; i < str1.length(); i++)
	{
		addElement(setId1, str1[i]);
	}

	for (int i = 0; i < str2.length(); i++)
	{
		addElement(setId2, str2[i]);
	}

	bool equal = true;

	SetElement *pData = getData(setId1);

	unsigned l = dataSize(setId1);
	unsigned t = 0;
	for (int i = 0; i < l; i++)
	{
		t = getOccurrences(setId2, pData[i].number);
		if (!t || pData[i].nOccurrences > t)
		{
			equal = false;
			break;
		}
	}

	removeSet(setId1);
	removeSet(setId2);

	return equal;
}

bool areEqual(string &str1, string &str2)
{
	if (str1.length() != str2.length())
	{
		return false;
	}
	
	unsigned setId1 = addSet();
	unsigned setId2 = addSet();

	for (int i = 0; i < str1.length(); i++)
	{
		addElement(setId1, str1[i]);
		addElement(setId2, str2[i]);
	}

	bool equal = true;
	for (int i = 0; i < str1.length(); i++)
	{
		if (getOccurrences(setId2, str1[i]) != getOccurrences(setId1, str1[i]))
		{
			equal = false;
			break;
		}
	}

	removeSet(setId1);
	removeSet(setId2);

	return equal;
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