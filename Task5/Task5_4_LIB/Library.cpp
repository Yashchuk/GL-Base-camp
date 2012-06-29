#include "Library.h"
#include <vector>
#include <cmath>

#define EPS .0001

std::vector<point> points;
std::vector<line> lines;

void clearPoints()
{
	points.clear();
}

void addPoint(point &p)
{
	points.push_back(p);
}

point* getPoint(unsigned index)
{
	if (index >= points.size())
	{
		return NULL;
	}

	return &points[index];
}

bool setPoint(point &p, unsigned index)
{
	if (index >= points.size())
	{
		return false;
	}

	points[index] = p;
}

void clearLines()
{
	lines.clear();
}

void addLine(line &l)
{
	lines.push_back(l);
}

line* getLine(unsigned index)
{
	if (index >= lines.size())
	{
		return NULL;
	}

	return &lines[index];
}

bool setLine(line &l, unsigned index)
{
	if (index >= lines.size())
	{
		return false;
	}

	lines[index] = l;
}

float lineLength(unsigned index)
{
	if (index >= lines.size())
	{
		return 0;
	}

	float dx = lines[index].a.x - lines[index].b.x;
	float dy = lines[index].a.y - lines[index].b.y;

	return sqrt(dx * dx + dy * dy);
}

int liesOnLine(unsigned pointIndex, unsigned lineIndex)
{
	if (lineIndex >= lines.size() || pointIndex >= points.size())
	{
		return -1;
	}

	float res = (points[pointIndex].x - lines[lineIndex].a.x) / 
				(lines[pointIndex].b.x - lines[lineIndex].a.x);

	res -= (points[pointIndex].y - lines[lineIndex].a.y) / 
		   (lines[pointIndex].b.y - lines[lineIndex].a.y);

	if (res < EPS && res > -EPS)
	{
		return 1;
	}

	return 0;
}