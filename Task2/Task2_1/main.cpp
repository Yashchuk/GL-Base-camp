/* 
 * Input book data in the form <author> <name>, <Year> <Notes>. 
 * Print data in a table, sorted by author's name. 
 * Print a list of books published before 1970.
 */

#include <iostream>
#include <iomanip>
#include <ctime>
#define N 3
#define MAX_LEN 128

using namespace std;

struct book
{
	char author[MAX_LEN];
	char name[MAX_LEN];
	unsigned year;
	char notes[MAX_LEN];
};

void inputData(book *books, int count);
void printData(book *books, int count);

/* sort book array by author */
void sortByAuthor(book *books, int count);

int main()
{
	book books[N];
	inputData(books, N);
	sortByAuthor(books, N);
	printData(books, N);
	return 0;
}

void inputData(book *books, int count)
{
	time_t rawtime;
    time(&rawtime);
	struct tm *pTime = localtime(&rawtime);

	for(int i = 0; i < count; i++)
	{
		book temp;

		do
		{
			cout << "Author: ";
			cin >> temp.author;
		}
		while(strlen(temp.author) == 0);

		do
		{
			cout << "Book name: ";
			cin >> temp.name;
		}
		while(strlen(temp.name) == 0);

		do
		{
			cout << "Year: ";
			cin >> temp.year;
		}
		while((temp.year - 1900) > pTime->tm_year);

		cout << "Additional notes: ";
		cin >> temp.notes;

		books[i] = temp;

		cout.fill('*');
		cout << setw(50) << '*' << endl;
	}
}

void printData(book *books, int count)
{
	cout << "Author\t\tName\t\tYear\t\tNotes" << endl;
	
	for(int i = 0; i < count; i++)
	{
		cout << books[i].author << "\t\t" << books[i].name << "\t\t"
			 << books[i].year << "\t\t" << books[i].notes << endl;
	}

	cout << "Books published before 1970: " << endl;

	for(int i = 0; i < count; i++)
	{
		if(books[i].year < 1970)
			cout << books[i].author << "\t\t" << books[i].name << "\t\t"
				 << books[i].year << "\t\t" << books[i].notes << endl;
	}
}

void sortByAuthor(book *books, int count)
{
	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			if(strcmp(books[i].author, books[j].author) < 0)
			{
				book temp = books[j];
				books[j] = books[i];
				books[i] = temp;
			}
		}
	}
}