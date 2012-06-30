#include <iostream>
#include <climits>
#include "Library.h"

using namespace std;

bool printMaxTriangle();

bool printMinCircleRadius();

int main()
{
	point temp = {0};
	point input = {0};
	
	while (true)
	{
		cin.clear();
		cin.sync();
		
		cout << "Enter point coordinates (X, Y):" << endl;

		cin >> temp.x >> temp.y;
		if (temp.x == input.x && temp.y == input.y)
		{
			break;
		}

		input = temp;
		addPoint(input);
	}

	printMaxTriangle();
	
	printMinCircleRadius();

	return 0;
}

bool printMinCircleRadius()
{
	return true;
}

bool printMaxTriangle()
{
	if (points() < 3)
	{
		return false;
	}

	float max = 0;
	int p1 = 0, p2 = 0, p3 = 0;

	for (int i = 0; i < points() - 2; i++)
	{
		for (int j = i + 1; j < points() - 1; j++)
		{
			for (int k = j + 1; k < points(); k++)
			{
				float temp = triangleArea(i, j, k);
				if (temp > max)
				{
					max = temp;
					p1 = i;
					p2 = j;
					p3 = k;
				}
			}	
		}	
	}

	cout << "Coodrinates of points making triangle with the biggest area (X, Y): " << endl;
	cout << fixed << getPoint(p1)->x << "\t" << getPoint(p1)->y << endl;
	cout << fixed << getPoint(p2)->x << "\t" << getPoint(p2)->y << endl;
	cout << fixed << getPoint(p3)->x << "\t" << getPoint(p3)->y << endl;

	return true;
}