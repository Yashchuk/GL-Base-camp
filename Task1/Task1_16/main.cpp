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
	unsigned long result = 0;

	/* Generate mask, filled with 1 after the eldest set bit
	* from the least bit up to start point
	* Example:
	* start = 7
	* 00000000000000000000000001111111
	*/
	unsigned long mask1 = 1 << (start - 1);
	mask1 |= mask1 >> 1;
	mask1 |= mask1 >> 2;
	mask1 |= mask1 >> 4;
	mask1 |= mask1 >> 8;
	mask1 |= mask1 >> 16;
	mask1 |= mask1 >> 32;

	// Do the same trick from the least bit up to end point
	unsigned long mask2 = 1 << (start + length - 1);
	mask2 |= mask2 >> 1;
	mask2 |= mask2 >> 2;
	mask2 |= mask2 >> 4;
	mask2 |= mask2 >> 8;
	mask2 |= mask2 >> 16;
	mask2 |= mask2 >> 32;

	// XOR of both masks
	result = mask1 ^ mask2;

	return result;
}