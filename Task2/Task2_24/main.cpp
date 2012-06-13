/* 
 * Input data, containing the status of subscription periodicals. 
 * Print the data as a table, sorting them by index. 
 * Identify the two most popular publications.
 */

#include <iostream>
#include <iomanip>
#define N 3
#define MAX_LEN 128

using namespace std;

struct periodical
{
	unsigned index;
	char name[MAX_LEN];
	unsigned subscriberCount;
};

void inputData(periodical *periodicals, int count);
void printData(periodical *periodicals, int count);

void sortByIndex(periodical *periodicals, int count);
void sortByPopularity(periodical *periodicals, int count);

/* prints two most  popular publications */
void printMostPopular(periodical *periodicals, int count);

int main()
{
	periodical periodicals[N];
	inputData(periodicals, N);
	sortByIndex(periodicals, N);
	printData(periodicals, N);
	printMostPopular(periodicals, N);
	return 0;
}

void inputData(periodical *periodicals, int count)
{
	cout << "Input data" << endl;
	for(int i = 0; i < count; i++)
	{
		cout << "Index: ";
		cin >> periodicals[i].index;

		cout << "Name: ";
		cin >> periodicals[i].name;

		cout << "Number of subscribers: ";
		cin >> periodicals[i].subscriberCount;
	}
}

void printData(periodical *periodicals, int count)
{
	cout << endl << "Index\t\tName\t\tNumber of subscribers" << endl;
	for(int i = 0; i < count; i++)
	{
		cout << periodicals[i].index << "\t\t" 
			 << periodicals[i].name << "\t\t" 
			 << periodicals[i].subscriberCount << endl;
	}
}

void sortByIndex(periodical *periodicals, int count)
{
	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			if(periodicals[i].index < periodicals[j].index)
			{
				periodical temp = periodicals[j];
				periodicals[j] = periodicals[i];
				periodicals[i] = temp;
			}
		}
	}
}

void sortByPopularity(periodical *periodicals, int count)
{
	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			if(periodicals[i].subscriberCount > periodicals[j].subscriberCount)
			{
				periodical temp = periodicals[j];
				periodicals[j] = periodicals[i];
				periodicals[i] = temp;
			}
		}
	}
}

void printMostPopular(periodical *periodicals, int count)
{
	if(count < 2)
		return;
	
	sortByPopularity(periodicals, count);

	cout << "Two most popular periodicals are: " << endl;
	cout << periodicals[0].name << " and " << periodicals[1].name << endl;
}