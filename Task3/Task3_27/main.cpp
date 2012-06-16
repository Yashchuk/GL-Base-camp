/*
 * Create a function that removes numeric characters in string 
 * and returns their number. Enter a sequence of character strings. 
 * Use function to print all strings without numbers.
 */

#include <iostream>
#include <cctype>
#define MAX_LEN 200

using namespace std;

/**
  * @brief	Function removes all numeric character is string
  * @param	[in,out]    pStr Pointer to a string ending with '\0'
  * @return	Number of removed characters
  */
unsigned removeNumbers(char *pStr);

int main()
{
	int n = 0;
	do
	{
		cout << "Input number of lines: ";
		cin >> n;
	}
	while(n <= 0);

	cout << "Input strings:" << endl;

	cin.clear();
	cin.sync();

	char **lines = new char*[n];
	for(int i = 0; i < n; i++)
	{
		lines[i] = new char[MAX_LEN];
		cin.getline(lines[i], MAX_LEN);
	}

	for(int i = 0; i < n; i++)
	{
		int n = removeNumbers(lines[i]);
		cout << lines[i] << endl;
		cout << "\tNumber of removed characters: " << n << endl;
	}

	for(int i = 0; i < n; i++)
		delete[] lines[i];
	delete[] lines;
	
	return 0;
}

unsigned removeNumbers(char *pStr)
{
	if(!pStr)
		return 0;

	unsigned n = 0;
	char *pEnd = pStr + strlen(pStr);

	while(*pStr)
	{
		// If character is a number - shift array left
		if(isdigit(*pStr))
		{
			memcpy(pStr, pStr + 1, pEnd - pStr);
			n++;
			continue;
		}

		pStr++;
	}

	return n;
}