#include <iostream>
#include "Library.h"

using namespace std;

int main()
{
	LineSegment ls1, ls2;
	float a, b;

	while (true)
	{
		cin >> a >> b;
		ls1 = createLineSegment(a, b);

		cin >> a >> b;
		ls2 = createLineSegment(a, b);

		cout << boolalpha << ls1.a << " " << ls1.b << " " << isEmpty(ls1) << endl;
		cout << boolalpha << ls2.a << " " << ls2.b << " " << isEmpty(ls2) << endl;

		ls1 = getLineCrossingSegment(ls1, ls2);

		cout << boolalpha << ls1.a << " " << ls1.b << " " << isEmpty(ls1) << endl;
	}

	return 0;
}