#include <iostream>
#include <iomanip>
#define N 2

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

int main()
{
	triangle triangles[N];
	inputData(triangles, N);
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
		cout << triangles[i].a.x << "; " << triangles[i].a.y << endl;
		cout << triangles[i].b.x << "; " << triangles[i].b.y << endl;
		cout << triangles[i].c.x << "; " << triangles[i].c.y << endl;
	}
}