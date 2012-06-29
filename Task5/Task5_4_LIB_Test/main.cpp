#include <iostream>
#include "Library.h"

using namespace std;

int main()
{
	point p = {2, 2.3};

	line l;
	l.a.x = 1;
	l.a.y = 1;
	l.b.x = 5.002;
	l.b.y = 5;

	addLine(l);
	addPoint(p);

	cout << liesOnLine(0, 0) << endl;
	return 0;
}