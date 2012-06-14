/* 
 * Input data, containing the coordinates (x, y) and color of points on screen. 
 * Print data in a table grouped by color. Identify two points of same color, 
 * the distance between which is greatest.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#define N 5

using namespace std;

/* Struct represents a single screen point (coordinates and color) */
struct ScreenPoint
{
	unsigned x;		// x pos
	unsigned y;		// y pos

	/* color in argb format */
	union 
	{
		unsigned long color;
		struct
		{
			unsigned char alpha;
			unsigned char red;
			unsigned char green;
			unsigned char blue;
		};
	};
};

void inputData(ScreenPoint *points, int count);

/* Print points grouped by color */
void printData(ScreenPoint *points, int count);

void printScreenPoint(ScreenPoint &point);

/* Sort array of points by color */
void sortPointsByColor(ScreenPoint *points, int count);

void printTwoMostDistantPoints(ScreenPoint *points, int count);

/* Return a length of vector represented by coordinates */
float vectorLength(int x1, int y1, int x2, int y2);

int main()
{
	ScreenPoint points[N];
	inputData(points, N);
	sortPointsByColor(points, N);
	printData(points, N);
	printTwoMostDistantPoints(points, N);
	return 0;
}

void inputData(ScreenPoint *points, int count)
{
	unsigned r, g, b;

	cout << "Input point data" << endl;
	for(int i = 0; i < count; i++)
	{
		cout << "Point coordinates (x and y): " << endl;
		cin >> points[i].x >> points[i].y;

		cout << "Point color: " << endl;
		cin >> points[i].color;
	}
}

void sortPointsByColor(ScreenPoint *points, int count)
{
	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			if(points[i].color < points[j].color)
			{
				ScreenPoint temp = points[j];
				points[j] = points[i];
				points[i] = temp;
			}
		}
	}
}

void printScreenPoint(ScreenPoint &point)
{
	cout << point.x << "\t\t" << point.y << "\t\t"
		 << (unsigned)point.alpha << " " << (unsigned)point.red << " "
		 << (unsigned)point.green << " " << (unsigned)point.blue << endl;
}

void printData(ScreenPoint *points, int count)
{
	cout.fill('*');
	cout << setw(50) << '*' << endl;
	cout << "X\t\t" << "Y\t\t" << "Color(A, R, G, B)" << endl;
	for(int i = 0; i < count; i++)
	{
		printScreenPoint(points[i]);
	}
}

float vectorLength(int x1, int y1, int x2, int y2)
{
	x1 -= x2;
	y1 -= y2;
	return sqrt((float)x1 * x1 + (float)y1 * y1);
}

void printTwoMostDistantPoints(ScreenPoint *points, int count)
{
	bool found = false;
	float maxLength = 0.0f;
	int point1, point2;

	for(int i = 0; i < count - 1; i++)
	{
		for(int j = i + 1; j < count; j++, i++)
		{
			if(points[i].color == points[j].color)
			{
				found = true;

				float length = vectorLength(points[i].x, points[i].y, points[j].x, points[j].y);
				if(length > maxLength)
				{
					point1 = i;
					point2 = j;
					maxLength = length;
				}
			}
			else
				break;
		}
	}

	if(found)
	{
		cout << "Two most distant are: " << endl;
		printScreenPoint(points[point1]);
		printScreenPoint(points[point2]);
	}
}