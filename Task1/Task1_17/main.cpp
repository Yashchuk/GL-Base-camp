#include <iostream>

using namespace std;

unsigned long subAbs(long num1, long num2);

int main()
{
	long number1, number2;

	cout << "Enter two numbers:" << endl;
	cin >> number1 >> number2;
	cout << "Result:" << endl << subAbs(number1, number2) << endl;

	return 0;
}

unsigned long subAbs(long num1, long num2)
{
	unsigned long result = num1 - num2;

	// Get sign bit from result
	unsigned long signBit = result >> 31;

	// Inverse and increment result if sign bit is set
	result = (result ^ (~signBit + 1)) + signBit;

	return result;
}