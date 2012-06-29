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

	return true;
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

	return true;
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

int liesOnLineSegment(unsigned pointIndex, unsigned lineIndex)
{
	if (lineIndex >= lines.size() || pointIndex >= points.size())
	{
		return -1;
	}

	if (lines[lineIndex].a.x < lines[lineIndex].b.x)
	{
		if (points[pointIndex].x < lines[lineIndex].a.x ||
			points[pointIndex].x > lines[lineIndex].b.x)
		{
			return 0;
		}
	}
	else
	{
		if (points[pointIndex].x > lines[lineIndex].a.x ||
			points[pointIndex].x < lines[lineIndex].b.x)
		{
			return 0;
		}
	}

	if (lines[lineIndex].a.y < lines[lineIndex].b.y)
	{
		if (points[pointIndex].y < lines[lineIndex].a.y ||
			points[pointIndex].y > lines[lineIndex].b.y)
		{
			return 0;
		}
	}
	else
	{
		if (points[pointIndex].y > lines[lineIndex].a.y ||
			points[pointIndex].y < lines[lineIndex].b.y)
		{
			return 0;
		}
	}

	return liesOnLine(pointIndex, lineIndex);
}

float triangleArea(unsigned pointIndex, unsigned lineIndex)
{
	if (lineIndex >= lines.size() || pointIndex >= points.size())
	{
		return 0.0f;
	}

	float dx = lines[lineIndex].a.x - lines[lineIndex].b.x;
	float dy = lines[lineIndex].a.y - lines[lineIndex].b.y;

	float a = sqrt(dx * dx + dy * dy);

	dx = lines[lineIndex].a.x - points[pointIndex].x;
	dy = lines[lineIndex].a.y - points[pointIndex].y;

	float b = sqrt(dx * dx + dy * dy);

	dx = lines[lineIndex].b.x - points[pointIndex].x;
	dy = lines[lineIndex].b.y - points[pointIndex].y;

	float c = sqrt(dx * dx + dy * dy);

	float p = (a + b + c) / 2;

	return sqrt(p * (p - a) * (p - b) * (p - c));
}