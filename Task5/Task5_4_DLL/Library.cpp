#include "Library.h"
#include <vector>
#include <cmath>

#define EPS .0001

std::vector<point> pointsVec;
std::vector<line> linesVec;

unsigned points()
{
	return pointsVec.size();
}

unsigned lines()
{
	return linesVec.size();
}

void clearPoints()
{
	pointsVec.clear();
}

void addPoint(point &p)
{
	pointsVec.push_back(p);
}

point* getPoint(unsigned index)
{
	if (index >= pointsVec.size())
	{
		return NULL;
	}

	return &pointsVec[index];
}

bool setPoint(point &p, unsigned index)
{
	if (index >= pointsVec.size())
	{
		return false;
	}

	pointsVec[index] = p;

	return true;
}

void clearLines()
{
	linesVec.clear();
}

void addLine(line &l)
{
	linesVec.push_back(l);
}

line* getLine(unsigned index)
{
	if (index >= linesVec.size())
	{
		return NULL;
	}

	return &linesVec[index];
}

bool setLine(line &l, unsigned index)
{
	if (index >= linesVec.size())
	{
		return false;
	}

	linesVec[index] = l;

	return true;
}

float lineLength(unsigned index)
{
	if (index >= linesVec.size())
	{
		return 0;
	}

	float dx = linesVec[index].a.x - linesVec[index].b.x;
	float dy = linesVec[index].a.y - linesVec[index].b.y;

	return sqrt(dx * dx + dy * dy);
}

int liesOnLine(unsigned pointIndex, unsigned lineIndex)
{
	if (lineIndex >= linesVec.size() || pointIndex >= pointsVec.size())
	{
		return -1;
	}

	float res = (pointsVec[pointIndex].x - linesVec[lineIndex].a.x) / 
				(linesVec[lineIndex].b.x - linesVec[lineIndex].a.x);

	res -= (pointsVec[pointIndex].y - linesVec[lineIndex].a.y) / 
		   (linesVec[lineIndex].b.y - linesVec[lineIndex].a.y);

	if (res < EPS && res > -EPS)
	{
		return 1;
	}

	return 0;
}

int liesOnLineSegment(unsigned pointIndex, unsigned lineIndex)
{
	if (lineIndex >= linesVec.size() || pointIndex >= pointsVec.size())
	{
		return -1;
	}

	if (linesVec[lineIndex].a.x < linesVec[lineIndex].b.x)
	{
		if (pointsVec[pointIndex].x < linesVec[lineIndex].a.x ||
			pointsVec[pointIndex].x > linesVec[lineIndex].b.x)
		{
			return 0;
		}
	}
	else
	{
		if (pointsVec[pointIndex].x > linesVec[lineIndex].a.x ||
			pointsVec[pointIndex].x < linesVec[lineIndex].b.x)
		{
			return 0;
		}
	}

	if (linesVec[lineIndex].a.y < linesVec[lineIndex].b.y)
	{
		if (pointsVec[pointIndex].y < linesVec[lineIndex].a.y ||
			pointsVec[pointIndex].y > linesVec[lineIndex].b.y)
		{
			return 0;
		}
	}
	else
	{
		if (pointsVec[pointIndex].y > linesVec[lineIndex].a.y ||
			pointsVec[pointIndex].y < linesVec[lineIndex].b.y)
		{
			return 0;
		}
	}

	return liesOnLine(pointIndex, lineIndex);
}

float triangleArea(unsigned pointIndex, unsigned lineIndex)
{
	if (lineIndex >= linesVec.size() || pointIndex >= pointsVec.size())
	{
		return 0.0f;
	}

	float dx = linesVec[lineIndex].a.x - linesVec[lineIndex].b.x;
	float dy = linesVec[lineIndex].a.y - linesVec[lineIndex].b.y;

	float a = sqrt(dx * dx + dy * dy);

	dx = linesVec[lineIndex].a.x - pointsVec[pointIndex].x;
	dy = linesVec[lineIndex].a.y - pointsVec[pointIndex].y;

	float b = sqrt(dx * dx + dy * dy);

	dx = linesVec[lineIndex].b.x - pointsVec[pointIndex].x;
	dy = linesVec[lineIndex].b.y - pointsVec[pointIndex].y;

	float c = sqrt(dx * dx + dy * dy);

	float p = (a + b + c) / 2;

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

float triangleArea2(unsigned point1, unsigned point2, unsigned point3)
{
	if (point1 >= pointsVec.size() || point2 >= pointsVec.size() || point3 >= pointsVec.size())
	{
		return 0.0f;
	}

	float dx = pointsVec[point1].x - pointsVec[point2].x;
	float dy = pointsVec[point1].y - pointsVec[point2].y;

	float a = sqrt(dx * dx + dy * dy);

	dx = pointsVec[point1].x - pointsVec[point3].x;
	dy = pointsVec[point1].y - pointsVec[point3].y;

	float b = sqrt(dx * dx + dy * dy);

	dx = pointsVec[point2].x - pointsVec[point3].x;
	dy = pointsVec[point2].y - pointsVec[point3].y;

	float c = sqrt(dx * dx + dy * dy);

	float p = (a + b + c) / 2;

	return sqrt(p * (p - a) * (p - b) * (p - c));
}