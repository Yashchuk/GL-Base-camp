#include <iostream>

using namespace std;

unsigned long fillBits(unsigned start, unsigned length);

int main()
{
	unsigned start, length;
	char buf[50];

	cout << "Enter start and length if block:" << endl;
	cin >> start >> length;
	cout << "Result:" << endl << itoa(fillBits(start, length), buf, 2) << endl;

	return 0;
}

unsigned long fillBits(unsigned start, unsigned length)
{
	unsigned long result = ~0;

	unsigned long mask1 = result >> (32 - start - length);

	unsigned long mask2 = result >> (32 - start);

	result = mask1 ^ mask2;

	return result;
}