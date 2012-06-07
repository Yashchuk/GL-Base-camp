#include <iostream>

using namespace std;

void swapEveryFourBits(unsigned long &number);

int main()
{
	unsigned long num;
	char buf[50];

	cout << "Enter number:" << endl;
	cin >> num;
	cout << "Before:" << endl << itoa(num, buf, 2) << endl;
	swapEveryFourBits(num);
	cout << "After:" << endl << itoa(num, buf, 2) << endl;

	return 0;
}

void swapEveryFourBits(unsigned long &number)
{
	unsigned long mask1 = 0x0F0F0F0F & number;
	unsigned long mask2 = 0xF0F0F0F0 & number;

	number = (mask1 << 4) | (mask2 >> 4);
}