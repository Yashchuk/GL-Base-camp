#ifndef _LIB_H
#define _LIB_H

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

/**
  * @brief		Clear all points
  * @return		void
  */
void clearPoints();

/**
  * @brief		Add point
  * @param		[in] p Point to add
  * @return		void
  */
void addPoint(point &p);

/**
  * @brief		Get point by index
  * @param		[in] index Point index
  * @return		Pointer to point struct
  */
point* getPoint(unsigned index);

/**
  * @brief		Set point by index
  * @param		[in] p Point data
  * @param		[in] index Point index
  * @return		False if index does not exist
  */
bool setPoint(point &p, unsigned index);

/**
  * @brief		Clear all lines
  * @return		void
  */
void clearLines();

/**
  * @brief		Add line
  * @param		[in] l Line to add
  * @return		void
  */
void addLine(line &l);

/**
  * @brief		Get line by index
  * @param		[in] index Line index
  * @return		Pointer to line struct
  */
line* getLine(unsigned index);

/**
  * @brief		Set line by index
  * @param		[in] l Line data
  * @param		[in] index Line index
  * @return		False if index does not exist
  */
bool setLine(line &l, unsigned index);

/**
  * @brief		Get line length
  * @param		[in] index Line index
  * @return		Line length or 0 if index does not exist
  */
float lineLength(unsigned index);

/**
  * @brief		Check if point lies of the lane
  * @param		[in] pointIndex Point index
  * @param		[in] lineIndex Line index
  * @return		1 if point lies in the line, else 0; -1 if index does not exist
  */
int liesOnLine(unsigned pointIndex, unsigned lineIndex);

/**
  * @brief		Check if point lies of the lane segment
  * @param		[in] pointIndex Point index
  * @param		[in] lineIndex Line index
  * @return		1 if point lies in the line segment, else 0; -1 if index does not exist
  */
int liesOnLineSegment(unsigned pointIndex, unsigned lineIndex);

/**
  * @brief		Get triangle data by given line and a point
  * @param		[in] pointIndex Point index
  * @param		[in] lineIndex Line index
  * @return		Traingle area or 0 if index does not exist
  */
float triangleArea(unsigned pointIndex, unsigned lineIndex);

#endif	/* _LIB_H */