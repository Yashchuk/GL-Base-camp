#include <iostream>
#include <fstream>
#include "BSPTree.h"

using namespace std;

Object *objects = NULL;
unsigned nObjects = 0;
Plane *planes = NULL;
unsigned nPlanes = 0;

bool loadFromFile(const char *fileName);
unsigned readObjects(Object **objects, ifstream &stream);
unsigned readPlanes(Plane **planes, ifstream &stream);
void CleanUp();

int main()
{
	if (!loadFromFile("..\\Task4_332\\data.txt"))
	{
		cout << "Error while loading data from file" << endl;
		return 1;
	}

	generateTree(objects, nObjects, planes, nPlanes);

	CleanUp();

	return 0;
}

void CleanUp()
{
	if (objects)
	{
		for (int i = 0; i < nObjects; i++)
		{
			delete[] objects[i].vertices;
		}
		delete[] objects;
	}

	if (planes)
	{
		delete[] planes;
	}
}

bool loadFromFile(const char *fileName)
{
	ifstream file(fileName, ios_base::binary);
	if (!file.is_open())
	{
		return false;
	}

	nObjects = readObjects(&objects, file);

	nPlanes = readPlanes(&planes, file);

	file.close();

	return true;
}


unsigned readObjects(Object **objects, ifstream &stream)
{
	int n = 0;

	stream >> n;
	if (!n)
	{
		return 0;
	}

	*objects = new Object[n];

	int j = 0;
	while (!stream.eof() && (j < n))
	{
		int k = 0;
		stream >> k;
		if (k < 3)
		{
			continue;
		}

		(*objects)[j].id = 'A' + j;
		(*objects)[j].nVertices = k;
		(*objects)[j].vertices = new Vertex[k];

		for (int i = 0; i < k; i++)
		{
			stream >> (*objects)[j].vertices[i].x;
			stream >> (*objects)[j].vertices[i].z;
		}

		j++;
	}

	return n;
}

unsigned readPlanes(Plane **planes, ifstream &stream)
{
	int n = 0;

	stream >> n;
	if (!n)
	{
		return 0;
	}

	*planes = new Plane[n];

	int j = 0;
	while (!stream.eof() && (j < n))
	{
		stream >> (*planes)[j].x1 >> (*planes)[j].z1;
		stream >> (*planes)[j].x2 >> (*planes)[j].z2;
		j++;
	}

	return n;
}