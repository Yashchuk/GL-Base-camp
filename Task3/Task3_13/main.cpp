/*
 * Create function, which changes two words in character string; 
 * word numbers are parameters of the function (if there are no words on given numbers, the line does not change). 
 * Using this function, swap the third word in the last word.
 */

#include <iostream>
#define MAX_LEN 128

using namespace std;

/**
  * @brief	Function swap two words by their ordinal numbers
  * @param	[in,out]    pStr Pointer to a character string
  * @param	[in]        word1 Number of first word
  * @param	[in]        word2 Number of second word
  * @return	void
  */
void swapWords(char *pStr, unsigned word1, unsigned word2);

int main()
{
	char *pBuf = new char[128];
	unsigned w1, w2;

	while(true)
	{
		cout << "Enter sentence (or \"e\" to exit):" << endl;
		cin.getline(pBuf, MAX_LEN);
		if(!strcmp(pBuf, "e"))
			break;

		cout << "Enter two numbers of words to swap:" << endl;
		cin >> w1 >> w2;

		swapWords(pBuf, w1, w2);

		cout << "Result:" << endl << pBuf << endl;

		cin.clear();
		cin.sync();
	}

	return 0;
}

void swapWords(char *pStr, unsigned word1, unsigned word2)
{
	char *pWord1Start = 0, *pWord1End;
	char *pWord2Start = 0, *pWord2End;

	// Loop to find words
	unsigned i = 0;
	while(*pStr)
	{
		// Beginning of a word
		if(*pStr != ' ')
		{
			i++;

			// Store pointer to start of the word
			if(i == word1)
				pWord1Start = pStr;
			else if(i == word2)
				pWord2Start = pStr;

			while(*pStr && *pStr != ' ')
				pStr++;

			// Store pointer to end of the word
			if(i == word1)
				pWord1End = pStr;
			else if(i == word2)
				pWord2End = pStr;
		}
		
		pStr++;
	}

	// If at least one word not found - exit function
	if(!pWord1Start || !pWord2Start)
		return;

	char *pBuf;	// Temporary buffer
	unsigned len1 = pWord1End - pWord1Start;	// Length of first word	
	unsigned len2 = pWord2End - pWord2Start;	// Length of second word
	unsigned lenDiff = 0;

	// Find out longer word
	if(len1 < len2)
	{
		lenDiff = len2 - len1;

		pBuf = new char[lenDiff];

		// Copy into buffer remaining characters in longer word
		memcpy(pBuf, pWord2End - lenDiff, lenDiff);

		// Shift right characters between the words(incl. part of second word)
		memcpy(pWord1End + lenDiff, pWord1End, (pWord2End - lenDiff) - pWord1End);

		// Swap characters in words
		for(int i = 0; i < len1; i++)
		{
			char temp = *(pWord1Start + i);
			*(pWord1Start + i) = *(pWord2Start + i + lenDiff);
			*(pWord2Start + i + lenDiff) = temp;
		}

		// Insert at the end of first word
		memcpy(pWord1End, pBuf, lenDiff);
	}
	else
	{
		lenDiff = len1 - len2;

		pBuf = new char[lenDiff];

		// Copy into buffer remaining characters in longer word
		memcpy(pBuf, pWord1End - lenDiff, lenDiff);

		// Shift left characters between the words(incl. second word)
		memcpy(pWord1End - lenDiff, pWord1End, pWord2End - pWord1End);

		// Swap characters in words
		for(int i = 0; i < len2; i++)
		{
			char temp = *(pWord1Start + i);
			*(pWord1Start + i) = *(pWord2Start + i - lenDiff);
			*(pWord2Start + i - lenDiff) = temp;
		}

		// Insert at the end of second word
		memcpy(pWord2End - lenDiff, pBuf, lenDiff);
	}
	
	delete[] pBuf;
}