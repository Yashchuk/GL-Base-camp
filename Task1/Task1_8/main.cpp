#include <iostream>

using namespace std;

unsigned long setEldestBit(unsigned long);

int main()
{
	unsigned long number;
	char buf[50];

	cout << "Enter number: ";
	cin >> number;
	cout << "Before:\t" << itoa(number, buf, 2) << endl;
	number = setEldestBit(number);
	cout << "After:\t" << itoa(number, buf, 2) << endl;

	return 0;
}

unsigned long setEldestBit(unsigned long number)
{
	/* Generate mask, filled with 1 after the eldest null bit
	* Example:
	* 11111110011000100000000000000000
	*               |
	*               V
	* 00000001111111111111111111111111
	*/
	unsigned long mask = ~number;
	mask |= mask >> 1;
	mask |= mask >> 2;
	mask |= mask >> 4;
	mask |= mask >> 8;
	mask |= mask >> 16;
	mask |= mask >> 32;
	
	// Highlight bit
	mask ^= mask >> 1;

	// Apply mask to number
	number ^= mask;

	return number;
}