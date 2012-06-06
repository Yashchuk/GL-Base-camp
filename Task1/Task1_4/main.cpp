#include <iostream>

using namespace std;

void swapBits(unsigned long &, unsigned, unsigned);

int main()
{
	unsigned long number;
	unsigned long bit1, bit2;
	char buf[50];

	cout << "Enter number: ";
	cin >> number;
	cout << "Enter bit positions: ";
	cin >> bit1 >> bit2;
	cout << "Before:\t" << itoa(number, buf, 2) << endl;
	swapBits(number, bit1, bit2);
	cout << "After:\t" << itoa(number, buf, 2) << endl;

	return 0;
}

void swapBits(unsigned long &number, unsigned bit1, unsigned bit2)
{
	// Create mask for both bits	
	unsigned long mask1 = 1 << bit1;
	unsigned long mask2 = 1 << bit2;

	// Get bit values
	unsigned bitVal1 = (number & mask1) >> bit1;
	unsigned bitVal2 = (number & mask2) >> bit2;

	// Compare using XOR
	unsigned equal = bitVal1 ^ bitVal2; 

	bitVal1 = (bitVal1 | equal) & equal; 
	bitVal2 = (bitVal2 | equal) & equal;

	cout << bitVal1 << endl << bitVal2 <<endl;

	number ^= (bitVal1 << bit2) | (bitVal2 << bit1); 
}