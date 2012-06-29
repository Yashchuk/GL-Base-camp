#ifndef _LIB_H
#define _LIB_H

struct point
{
	float x, y;
};

struct line
{
	point a, b;
};

void clearPoints();

void addPoint(point &p);

point* getPoint(unsigned index);

bool setPoint(point &p, unsigned index);

void clearLines();

void addLine(line &l);

line* getLine(unsigned index);

bool setLine(line &l, unsigned index);

float lineLength(unsigned index);

int liesOnLine(unsigned pointIndex, unsigned lineIndex);

#endif	/* _LIB_H */