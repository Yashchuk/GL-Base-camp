/** 
  * @file	Library.h
  * @brief	Simple implementation of logic around 2d lines and points
  *	@author	Vitaliy Sidenko
  * @date	30/06/2012
  */

#ifndef _LIB_H
#define _LIB_H

#include <Windows.h>

/* Point in 2d space */
struct point
{
	float x, y;
};

/* Line in 2d space */
struct line
{
	point a, b;
};

HINSTANCE hLib;

typedef unsigned (*FUNC0)();
typedef void (*FUNC1)();
typedef void (*FUNC2)(point&);
typedef point* (*FUNC3)(unsigned);
typedef bool (*FUNC4)(point&, unsigned);
typedef void (*FUNC5)(line&);
typedef line* (*FUNC6)(unsigned);
typedef float (*FUNC7)(unsigned);
typedef int (*FUNC8)(unsigned, unsigned);
typedef float (*FUNC9)(unsigned, unsigned);
typedef float (*FUNC10)(unsigned, unsigned, unsigned);
typedef bool (*FUNC11)(line&, unsigned);

/**
  * @brief		Gets number of saved points
  */
FUNC0 points;

/**
  * @brief		Gets number of saved lines
  */
FUNC0 lines;

/**
  * @brief		Clear all points
  * @return		void
  */
FUNC1 clearPoints;

/**
  * @brief		Add point
  * @param		[in] p Point to add
  * @return		void
  */
FUNC2 addPoint;

/**
  * @brief		Get point by index
  * @param		[in] index Point index
  * @return		Pointer to point struct
  */
FUNC3 getPoint;

/**
  * @brief		Set point by index
  * @param		[in] p Point data
  * @param		[in] index Point index
  * @return		False if index does not exist
  */
FUNC4 setPoint;

/**
  * @brief		Clear all lines
  * @return		void
  */
FUNC1 clearLines;

/**
  * @brief		Add line
  * @param		[in] l Line to add
  * @return		void
  */
FUNC5 addLine;

/**
  * @brief		Get line by index
  * @param		[in] index Line index
  * @return		Pointer to line struct
  */
FUNC6 getLine;

/**
  * @brief		Set line by index
  * @param		[in] l Line data
  * @param		[in] index Line index
  * @return		False if index does not exist
  */
FUNC11 setLine;

/**
  * @brief		Get line length
  * @param		[in] index Line index
  * @return		Line length or 0 if index does not exist
  */
FUNC7 lineLength;

/**
  * @brief		Check if point lies of the lane
  * @param		[in] pointIndex Point index
  * @param		[in] lineIndex Line index
  * @return		1 if point lies in the line, else 0; -1 if index does not exist
  */
FUNC8 liesOnLine;

/**
  * @brief		Check if point lies of the lane segment
  * @param		[in] pointIndex Point index
  * @param		[in] lineIndex Line index
  * @return		1 if point lies in the line segment, else 0; -1 if index does not exist
  */
FUNC8 liesOnLineSegment;

/**
  * @brief		Get triangle data by given line and a point
  * @param		[in] pointIndex Point index
  * @param		[in] lineIndex Line index
  * @return		Traingle area or 0 if index does not exist
  */
FUNC9 triangleArea;

/**
  * @brief		Get triangle data by given point indexes
  * @param		[in] point1 1st Point index
  * @param		[in] point2 2d Point index
  * @param		[in] point3 3d Point index
  * @return		Traingle area or 0 if index does not exist
  */
FUNC10 triangleArea2;

/**
  * @brief		Load fucntions from dll
  * @return		Flase if error occured
  */
bool loadUpDll();

/**
  * @brief		Unload dll
  * @return		void
  */
void unloadDll();

bool loadUpDll()
{
	hLib = LoadLibrary("Task5_4_DLL.dll");
	if (!hLib)
	{
		return false;
	}

	points = (FUNC0)GetProcAddress(hLib, "points");
	if (!points)
	{
		return false;
	}
	lines = (FUNC0)GetProcAddress(hLib, "lines");
	if (!points)
	{
		return false;
	}
	clearLines = (FUNC1)GetProcAddress(hLib, "clearLines");
	if (!clearLines)
	{
		return false;
	}
	getPoint = (FUNC3)GetProcAddress(hLib, "getPoint");
	if (!getPoint)
	{
		return false;
	}
	getLine = (FUNC6)GetProcAddress(hLib, "getLine");
	if (!getLine)
	{
		return false;
	}
	addPoint = (FUNC2)GetProcAddress(hLib, "addPoint");
	if (!addPoint)
	{
		return false;
	}
	addLine = (FUNC5)GetProcAddress(hLib, "addLine");
	if (!addLine)
	{
		return false;
	}
	setLine = (FUNC11)GetProcAddress(hLib, "setLine");
	if (!setLine)
	{
		return false;
	}
	setPoint = (FUNC4)GetProcAddress(hLib, "setPoint");
	if (!setPoint)
	{
		return false;
	}
	lineLength = (FUNC7)GetProcAddress(hLib, "lineLength");
	if (!lineLength)
	{
		return false;
	}
	liesOnLine = (FUNC8)GetProcAddress(hLib, "liesOnLine");
	if (!liesOnLine)
	{
		return false;
	}
	liesOnLineSegment = (FUNC8)GetProcAddress(hLib, "liesOnLineSegment");
	if (!liesOnLineSegment)
	{
		return false;
	}
	triangleArea = (FUNC9)GetProcAddress(hLib, "triangleArea");
	if (!triangleArea)
	{
		return false;
	}
	triangleArea2 = (FUNC10)GetProcAddress(hLib, "triangleArea2");
	if (!triangleArea2)
	{
		return false;
	}

	return true;
}

void unloadDll()
{
	if (hLib)
	{
		FreeLibrary(hLib);
	}
}


#endif	/* _LIB_H */