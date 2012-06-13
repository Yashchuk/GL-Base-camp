/* 
 * Enter the data, containing coordinates x, y and z of a single point. 
 * Print your entries in a table, sorting them by z coordinate. 
 * Find two two closest points.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#define N 3

using namespace std;

// Struct represents a point in 3d space
struct point
{
	float x;
	float y;
	float z;
};

/* Input points into predefined buffer */
void inputData(point *points, int count);

/* Print points */
void printData(point *points, int count);

/* Prints a single point */
void printPoint(point &point);

/* Sort point array by z coordinate */
void sortByCoordinate(point *points, int count);

/* Gets distance between to given points */
float getDistance(point &a, point &b);

/* Prints coordinates of two closest points */
void printTwoClosestPoints(point *points, int count);

int main()
{
	point points[N];
	inputData(points, N);
	sortByCoordinate(points, N);
	printData(points, N);
	printTwoClosestPoints(points, N);
}

void inputData(point *points, int count)
{
	cout << "Enter x, y and z coordinates of a point" << endl;
	for(int i = 0; i < count; i++)
	{
		cin >> points[i].x >> points[i].y >> points[i].z;
		cout.fill('*');
		cout << setw(50) << '*' << endl; 
	}
}

void printData(point *points, int count)
{
	cout << "Point coordinates (x, y, z):" << endl;
	for(int i = 0; i < count; i++)
	{
		printPoint(points[i]);
	}
}

void printPoint(point &point)
{
	cout << "(" << point.x << ", " 
				<< point.y << ", "
			    << point.z << ")" << endl;
}

void sortByCoordinate(point *points, int count)
{
	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			if(points[i].z < points[j].z)
			{
				point temp = points[j];
				points[j] = points[i];
				points[i] = temp;
			}
		}
	}
}

float getDistance(point &a, point &b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;

	return sqrt(dx * dx + dy * dy + dz * dz);
}

void printTwoClosestPoints(point *points, int count)
{
	int firstPoint = 0, secondPoint = 0;
	float minDistance = FLT_MAX;

	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			float distance = getDistance(points[i], points[j]);

			if(distance < minDistance)
			{
				minDistance = distance;
				firstPoint = i;
				secondPoint = j;
			}
		}
	}

	cout << "Closest points are: " << endl;
	printPoint(points[firstPoint]);
	printPoint(points[secondPoint]);
}