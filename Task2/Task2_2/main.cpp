/* 
 * Enter data, containing coordinates of opposite vertices of rectangle. 
 * Print data in a table, sorting by left x coordinate. 
 * Identify rectangles with the largest and the smallest area.
 */

#include <iostream>
#include <iomanip>
#include <climits>
#define N 3

using namespace std;

/* point i 2d space */
struct point
{
	int x;
	int y;
};

/* Rectangle with opposite vectices coordinates */
struct rectangle
{
	point topLeft;
	point bottomRight;
};

void inputData(rectangle *rectangles, int count);
void printData(rectangle *rectangles, int count);

/* Soft rectangles by top left x coordinate */
void sortByTopLeftX(rectangle *rectangles, int count);

/* Returns rectangle with the biggest area */
rectangle* getBiggestRectangle(rectangle *rectangles, int count);

/* Returns rectangle with the smallest area */
rectangle* getSmallestRectangle(rectangle *rectangles, int count);

/* Returs area of given rectangle */
unsigned getArea(rectangle &rect);

int main()
{
	rectangle rectangles[N];
	inputData(rectangles, N);
	sortByTopLeftX(rectangles, N);
	printData(rectangles, N);
	return 0;
}

void inputData(rectangle *rectangles, int count)
{
	if(count <= 0)
		return;
	
	int i = 0;
	int tempX, tempY;

	cout << "Input rectangle opposite vecrtices coordinates: " << endl;

	while(i < count)
	{
		cout << "Top left (x, y): ";
		cin >> rectangles[i].topLeft.x >> rectangles[i].topLeft.y;

		// Check input (if bottom right is coordinates are lower then top left)
		for(;;)
		{
			cout << "Bottom right (x, y): ";
			cin >> tempX >> tempY;

			if(tempX < rectangles[i].topLeft.x)
			{
				cout << "x coordinate is less then the top left one, try again" << endl;
				continue;
			}

			if(tempY < rectangles[i].topLeft.y)
			{
				cout << "y coordinate is less then the top left one, try again" << endl;
				continue;
			}

			break;
		}

		rectangles[i].bottomRight.x = tempX;
		rectangles[i].bottomRight.y = tempY;

		cout.fill('*');
		cout << setw(50) << '*' << endl;

		i++;
	}
}

void printData(rectangle *rectangles, int count)
{
	if(count <= 0)
		return;

	cout << "Top Left(x, y)\t\tBottom right(x, y)" << endl;

	for(int i = 0; i < count; i++)
	{
		cout << rectangles[i].topLeft.x << " " << rectangles[i].topLeft.y << "\t\t\t\t";
		cout << rectangles[i].bottomRight.x << " " << rectangles[i].bottomRight.y << endl;
	}

	rectangle *rect = getSmallestRectangle(rectangles, count);
	
	cout << "Rectangle with the smallest area" << endl;
	cout << rect->topLeft.x << " " << rect->topLeft.y << "\t\t\t\t";
	cout << rect->bottomRight.y << " " << rect->bottomRight.y << endl;

	rect = getBiggestRectangle(rectangles, count);
	
	cout << endl << "Rectangle with the biggest area" << endl;
	cout << rect->topLeft.x << " " << rect->topLeft.y << "\t\t\t\t";
	cout << rect->bottomRight.y << " " << rect->bottomRight.y << endl;
}

void sortByTopLeftX(rectangle *rectangles, int count)
{
	for(int i = count - 1; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{ 
			if(rectangles[i].topLeft.x < rectangles[j].topLeft.x)
			{
				rectangle temp = rectangles[j];
				rectangles[j] = rectangles[i];
				rectangles[i] = temp;
			}
		}
	}
}

unsigned getArea(rectangle &rect)
{
	unsigned dx = rect.bottomRight.x - rect.topLeft.x;
	unsigned dy = rect.bottomRight.y - rect.topLeft.y;

	return dx * dy;
}

rectangle* getBiggestRectangle(rectangle *rectangles, int count)
{
	unsigned max = 0;
	int index = 0;

	for(int i = 0; i < count; i++)
	{
		unsigned area = getArea(rectangles[i]);
		if(area > max)
		{
			max = area;
			index = i;
		}
	}

	return &rectangles[index];
}

rectangle* getSmallestRectangle(rectangle *rectangles, int count)
{
	unsigned min = UINT_MAX;
	int index = 0;

	for(int i = 0; i < count; i++)
	{
		unsigned area = getArea(rectangles[i]);
		if(area < min)
		{
			min = area;
			index = i;
		}
	}

	return &rectangles[index];
}