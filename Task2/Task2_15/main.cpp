/* 
 * Enter the data containing the coordinates of vertices of triangles. 
 * Print your entries in a table, sorting them in descending order 
 * by perimeters of these triangles. 
 * Determine the percentage of triangles, which perimeter exceeds the 
 * minimum more than 2 times.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#define N 3

using namespace std;

struct point
{
	float x;
	float y;
};

struct triangle
{
	point a;
	point b;
	point c;
};

/* Input triangle data into predefined buffer */
void inputData(triangle *triangles, int count);

/* Print triangle data */
void printData(triangle *triangles, int count);

/* Get perimeter of a single triangle */
float getPerimeter(const triangle &triangle);

/* Sort triangle array by perimeter value */
void sortByPerimeter(triangle *triangles, int count);

/* 
 Determine the percentage of triangles, 
 that have perimeter 2 times greater then the smallest one.
 */
float calculatePercentage(triangle *triangles, int count);

int main()
{
	triangle triangles[N];
	inputData(triangles, N);
	cout << "Percentage of triangles with perimeter 2 times greater than min: " 
		 << calculatePercentage(triangles, N) << endl;
	printData(triangles, N);
	return 0;
}

void inputData(triangle *triangles, int count)
{
	cout << "Enter triangle coordinates (x and y):" << endl;
	for(int i = 0; i < count; i++)
	{
		cin >> triangles[i].a.x >> triangles[i].a.y;
		cin >> triangles[i].b.x >> triangles[i].b.y;
		cin >> triangles[i].c.x >> triangles[i].c.y;
		cout.fill('*');
		cout << setw(50) << '*' << endl; 
	}
}

void printData(triangle *triangles, int count)
{
	for(int i = 0; i < count; i++)
	{
		cout << endl << "triangle " << i << ": " << endl;
		cout << '(' << triangles[i].a.x << ", " << triangles[i].a.y << ')' << endl;
		cout << '(' << triangles[i].b.x << ", " << triangles[i].b.y << ')' << endl;
		cout << '(' << triangles[i].c.x << ", " << triangles[i].c.y << ')' << endl;
	}
}

void sortByPerimeter(triangle *triangles, int count)
{
	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			if(getPerimeter(triangles[j]) <= getPerimeter(triangles[i]))
			{
				triangle temp = triangles[j];
				triangles[j] = triangles[i];
				triangles[i] = temp;
			}
		}
	}
}

float getPerimeter(const triangle &triangle)
{
	point ab, bc, ac;

	// Calculate vector for each side
	ab.x = abs(triangle.a.x - triangle.b.x);
	ab.y = abs(triangle.a.y - triangle.b.y);

	bc.x = abs(triangle.b.x - triangle.c.x);
	bc.y = abs(triangle.b.y - triangle.c.y);

	ac.x = abs(triangle.a.x - triangle.c.x);
	ac.y = abs(triangle.a.y - triangle.c.y);

	// Return sum of vector lengths
	return sqrt(ab.x * ab.x + ab.y * ab.y) + 
		   sqrt(bc.x * bc.x + bc.y * bc.y) + 
		   sqrt(ac.x * ac.x + ac.y * ac.y);
}

float calculatePercentage(triangle *triangles, int count)
{
	if(count <= 0)
		return 0.0f;

	// Sort by perimeter (descending)
	sortByPerimeter(triangles, count);

	float min = getPerimeter(triangles[count - 1]) * 2;

	// Get number of triangles with perimeter 2 times greater than min
	int n = 0;
	for(int i = 0; i < count; i++)
	{
		if(getPerimeter(triangles[i]) > min)
			++n;
		else
			break;
	}

	// Return percentage of n within traingles count
	return (n / (float)count) * 100.0f;
}