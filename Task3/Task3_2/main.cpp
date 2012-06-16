/*
 * Create a function, that for a given number of days of the year 
 * the appropriate date day and month. 
 * Generate 5 random numbers that specifies the number of days. 
 * Using created function, print the date corresponding to each of them.
 */

#include <iostream>

using namespace std;

struct date
{
	char month;
	char day; 
};

/**
  * @brief	Function coverts given number of days into months and days
  * @param	[in]    days Number of days since new year
  * @return	date structure containing month a day 
  */
date getDateByDayNumber(unsigned days);

int main()
{
	date d;
	
	for(int i = 0; i < 5; i++)
	{
		unsigned num = rand() % 366;
		cout << "Number of days: " << num << endl;
		d = getDateByDayNumber(num);
		cout << "Month - " << (int)d.month << " day - " << (int)d.day << endl; 
	}
	return 0;
}

date getDateByDayNumber(unsigned days)
{
	if(days > 365)
	{
		days -= (days / 365) * 365;
	}

	date result;
	unsigned months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	unsigned temp = 0;
	for(int i = 0; i < 12; i++)
	{
		if(temp + months[i] > days)
		{
			result.month = i;
			result.day = days - temp;
			break;
		}

		temp += months[i];
	}

	return result;
}