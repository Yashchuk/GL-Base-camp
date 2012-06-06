#include <iostream>

using namespace std;

void swapBits(unsigned long &number, unsigned bit1, unsigned bit2);

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

	// Create new masks (should be 0 if bits are equal)
	mask1 = equal << bit1;
	mask2 = equal << bit2;

	// Apply masks to number
	number ^= mask1 | mask2; 

}