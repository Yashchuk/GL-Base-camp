/* 
 * Create a function that changes in a given character string all words, 
 * containing the specified letter, into relevant number of '*' characters. 
 * Using created function "hide" all the words in sentences, which meets a given letter.
 */

#include <iostream>
#include <locale>
#define MAX_LEN 200

using namespace std;

/**
  * @brief	Function changes all words, containing given letter into asterisks
  * @param	[in,out]    pStr Pointer to a string ending with '\0'
  * @param	[in]        c Letter to search in words
  * @return	void
  */
void hideWords(char *pStr, char c);

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

	// Loop until the end of string
	while(*pStr)
	{
		// Beginning of a word found
		if(!isspace((unsigned char)*pStr))
		{
			char *pStart = pStr;
			bool hide = false;

			// Loop to find the end of a word
			while(*pStr && !isspace((unsigned char)*pStr))
			{
				// Check if word contains a character
				if(*pStr == c)
					hide = true;

				pStr++;
			}
			
			// If word contained given character, fill it with asterisks
			if(hide)
				memset(pStart, '*', pStr - pStart); 
		}

		pStr++;
	}
}