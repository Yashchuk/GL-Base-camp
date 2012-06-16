/*
 * Create function that generates strings with a verbal representation of given two-digit number. 
 * Generate a sequence of 14 random two-digit numbers. 
 * Using created function, print a table of values ​​of numbers and their verbal representations.
 */

#include <iostream>
#define MAX_LEN 200

using namespace std;

/**
  * @brief	Function generates verbal representation of given two-digit number
  * @param	[out]    pBuf Buffer to store generated string
  * @param	[in]     bufSize Buffer size
  * @param	[in]     number Number
  * @return	void
  */
void getNumberAsString(char *pBuf, unsigned bufSize, int number);

int main()
{
	char buf[MAX_LEN];

	for(int i = 0; i < 14; i++)
	{
		int num = (rand() % 200) - 100;
		getNumberAsString(buf, MAX_LEN, num);
		cout << num << " " << buf << endl;
	}
	return 0;
}

void getNumberAsString(char *pBuf, unsigned bufSize, int number)
{
	if(!bufSize)
		return;

	char *strTable[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
					 "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen",
					 "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Seventy", "Eighty", "Ninety"};

	char result[100] = {0};

	if(number < 0)
	{
		strcat(result, "Minus ");
		number = -number;
	}

	int digit = number / 10;

	if(digit > 1)
	{
		strcat(result, strTable[20 + digit - 2]);
		strcat(result, " ");
	}

	if(digit == 1)
	{
		digit = number % 10;
		strcat(result, strTable[10 + digit]);
	}
	else
	{
		digit = number % 10;
		strcat(result, strTable[digit]);
	}
	
	int resLen = strlen(result) + 1; 
	strncpy(pBuf, result, resLen < bufSize ? resLen : bufSize); 
}