#include "Library.h"

void makeLineSegmentEpty(LineSegment &ls)
{
	ls.empty = true;
}

bool isEmpty(LineSegment &ls)
{
	return ls.empty;
}

LineSegment createLineSegment(float a, float b)
{
	LineSegment ls = {0};

	if (a > b)
	{
		ls.a = b;
		ls.b = a;
	}
	else
	{
		if (a == b)
		{
			ls.empty = true;
		}

		ls.a = a;
		ls.b = b;
	}

	return ls;
}

LineSegment getLineCrossingSegment(LineSegment &ls1, LineSegment &ls2)
{
	LineSegment ls = {0.0f, 0.0f, false};
	
	if (ls1.b < ls2.a || ls1.a > ls2.b)
	{
		ls.empty = true;
		return ls;
	}

	if (ls1.a < ls2.a)
	{
		if (ls1.b < ls2.b)
		{
			ls.a = ls2.a;
			ls.b = ls1.b;

			return ls;
		}

		ls.a = ls2.a;
		ls.b = ls2.b;

		return ls;
	}

	if (ls1.b > ls2.b)
	{
		ls.a = ls1.a;
		ls.b = ls2.b;

		return ls;
	}

	ls.a = ls1.a;
	ls.b = ls1.b;

	return ls;
}