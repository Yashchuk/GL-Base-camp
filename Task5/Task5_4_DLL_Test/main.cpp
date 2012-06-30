#include <iostream>
#include <climits>
#include "Library.h"

using namespace std;

bool printMaxTriangle();

bool printLine();

int main()
{
	point temp = {0};
	point inputPoint = {0};
	
	if (!loadUpDll())
	{
		return 1;
	}

	while (true)
	{
		cin.clear();
		cin.sync();
		
		cout << "Enter point coordinates (X, Y):" << endl;

		cin >> temp.x >> temp.y;
		if (temp.x == inputPoint.x && temp.y == inputPoint.y)
		{
			break;
		}

		inputPoint = temp;
		addPoint(inputPoint);
	}

	line l = {0};
	line inputLine = {0};

	while (true)
	{
		cin.clear();
		cin.sync();
		
		cout << "Enter line coordinates (X, Y):" << endl;

		cin >> l.a.x >> l.a.y >> l.b.x >> l.b.y;
		if (l.a.x == inputLine.a.x && l.a.y == inputLine.a.y &&
			l.b.x == inputLine.b.x && l.b.y == inputLine.b.y)
		{
			break;
		}

		inputLine = l;
		addLine(inputLine);
	}

	printMaxTriangle();
	
	printLine();

	unloadDll();

	return 0;
}

bool printLine()
{
	if (!lines() || !points())
	{
		return false;
	}

	int k = 0;
	int max = 0, l = 0;
	for (int i = 0; i < lines(); i++)
	{
		for (int j = 0; j < points(); j++)
		{
			if (liesOnLineSegment(j, i) == 1)
			{
				k++;
			}
		}

		if (k > max)
		{
			max = k;
			l = i;
		}

		k = 0;
	}

	cout << "Line with the maximum of " << max << " points:" << endl;
	cout << "(" << getLine(l)->a.x << " " << getLine(l)->a.y << ") "
		 << "(" << getLine(l)->b.x << " " << getLine(l)->b.y << ")" << endl;

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
				float temp = triangleArea2(i, j, k);
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