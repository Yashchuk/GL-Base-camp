#include <iostream>

using namespace std;

unsigned long getNextEvenNumber(unsigned long);

int main()
{
	unsigned long number;

	cout << "Enter number:" << endl;
	cin >> number;
	cout << "Result:" << endl << getNextEvenNumber(number) << endl;

	return 0;
}

unsigned long getNextEvenNumber(unsigned long number)
{
	// Check if number is even
	unsigned long isEven = number % 2;

	// Add 1 if number is not even (isEven = 1)
	// else add 2 to move to next even number
	return number + 2 - (1 & isEven);
}