#include <iostream>
#include <climits>
#include <ctime>
#include <iterator>

using namespace std;

struct Point
{
	int x, y;
};

void initBoard(char *data, unsigned width, unsigned height, bool randomWalls = true);

void printBoard(char *data, unsigned width, unsigned height);

bool findPath(char *pData, unsigned width, unsigned height, Point &start, Point &finish);

int main()
{
	char *data;

	unsigned width = 0, height = 0;

	cout << "Enter matrix width" << endl;
	while (true)
	{
		cin >> width;
		if (!cin.fail())
		{
			break;
		}
		cout << "Invalid input" << endl;
		cin.clear();
		cin.sync();
	}

	cout << "Enter matrix height" << endl;
	while (true)
	{
		cin >> height;
		if (!cin.fail())
		{
			break;
		}
		cout << "Invalid input" << endl;
		cin.clear();
		cin.sync();
	}

	try
	{
		data = new char[width * height];
	}
	catch(bad_alloc)
	{
		cout << "memory allocation error" << endl;
		return 1;
	}

	initBoard(data, width, height);
	printBoard(data, width, height);

	Point start, finish;

	cout << "Enter start point coordinates" << endl;
	while (true)
	{
		cout << "X:" << endl;
		cin >> start.x;
		if (cin.fail() || start.x >= width)
		{
			cout << "Invalid input" << endl;
			cin.clear();
			cin.sync();
			continue;
		}
		break;
	}
	while (true)
	{
		cout << "Y:" << endl;
		cin >> start.y;
		if (cin.fail() || start.y >= height)
		{
			cout << "Invalid input" << endl;
			cin.clear();
			cin.sync();
			continue;
		}
		break;
	}

	cout << "Enter destination point coordinates" << endl;
	while (true)
	{
		cout << "X:" << endl;
		cin >> finish.x;
		if (cin.fail() || finish.x >= width)
		{
			cout << "Invalid input" << endl;
			cin.clear();
			cin.sync();
			continue;
		}
		break;
	}
	while (true)
	{
		cout << "Y:" << endl;
		cin >> finish.y;
		if (cin.fail() || finish.y >= height)
		{
			cout << "Invalid input" << endl;
			cin.clear();
			cin.sync();
			continue;
		}
		break;
	}

	findPath(data, width, height, start, finish);

	printBoard(data, width, height);

	delete[] data;

	return 0;
}

#include <vector>

bool findPath(char *pData, unsigned width, unsigned height, Point &start, Point &finish)
{
	if (!pData || start.x >= width - 1 || start.y >= height - 1 || 
		finish.x >= width - 1|| finish.y >= height - 1)
	{
		return false;
	}

	if (*(pData + start.y * width + start.x) == CHAR_MAX ||
		*(pData + finish.y * width + finish.x) == CHAR_MAX)
	{
		return false;
	}

	int *data = new int[width * height];

	for (int i = 0; i < width * height; i++)
	{
		data[i] = pData[i];
	}

	vector<Point> wave, oldWave;
	Point p = {start.x, start.y};

	oldWave.push_back(p);

	int nstep = 2;

	*(data + start.y * width + start.x) = nstep;

	int dx[] = {-1, 1, 1, -1};
	int dy[] = {-1, 1, -1, 1};

	bool quit = false;
	while (oldWave.size() > 0)
	{
		nstep++;
		wave.clear();
		for (vector<Point>::iterator it = oldWave.begin(); it != oldWave.end(); it++)
		{
			for (int i = 0; i < 4; i++)
			{
				int nx = it->x + dx[i];
				int ny = it->y + dy[i];

				if (nx == finish.x && ny == finish.y)
				{
					*(data + ny * width + nx) = nstep;
					quit = true;
					break;
				}

				if (*(data + ny * width + nx) < 2)
				{
					p.x = nx;
					p.y = ny;
					wave.push_back(p);
					*(data + ny * width + nx) = nstep;
				}
			}
			if (quit)
			{
				break;
			}
		}
		if (quit)
		{
			break;
		}
		oldWave = wave;
	}
	
    wave.clear();
    wave.push_back(finish);
    while (*(data + finish.y * width + finish.x) != 2)
    {
        for (int d = 0; d < 4; ++d)
        {
            int nx = finish.x + dx[d];
            int ny = finish.y + dy[d];
            if (*(data + finish.y * width + finish.x) - 1 == *(data + ny * width + nx))
            {
                finish.x = nx;
                finish.y = ny;
                wave.push_back(finish);
                break;
            }
        }
    }

	for (vector<Point>::iterator it = wave.begin(); it != wave.end(); it++)
	{
		*(pData + it->y * width + it->x) = 2;
	}
	
	delete[] data;

	return true;
}

void initBoard(char *data, unsigned width, unsigned height, bool randomWalls)
{
	if (!data)
	{
		return;
	}

	for (unsigned i = 0; i < height; i++)
	{
		for (unsigned j = 0; j < width; j++)
		{
			*(data + i * width + j) = ((j % 2) ^ (i % 2)) ? 1 : 0;
		}
	}

	if (randomWalls)
	{
		srand(time(NULL));
		
		unsigned k = (width * height) / 10 + rand() % ((width * height) / 6);
		unsigned x, y;
		for (unsigned i = 0; i < k; i++)
		{
			x = rand() % width;
			y = rand() % height;
			*(data + y * width + x) = CHAR_MAX;
		}
	}

	memset(data, CHAR_MAX, width);
	for (unsigned i = 1; i < height - 1; i++)
	{
		*(data + i * width) = CHAR_MAX;
		*(data + i * width + width - 1) = CHAR_MAX;
	}
	memset(data + (height - 1) * width, CHAR_MAX, width);
}

void printBoard(char *data, unsigned width, unsigned height)
{
	if (!data)
	{
		return;
	}

	for (unsigned i = 0; i < height; i++)
	{
		for (unsigned j = 0; j < width; j++)
		{
			if (*(data + i * width + j) == 1)
			{
				cout << (char)219 << (char)219;
			}
			else if (*(data + i * width + j) == 0)
			{
				cout << "  ";
			}
			else if (*(data + i * width + j) == CHAR_MAX)
			{
				cout << (char)206 << (char)206;
			}
			else if (*(data + i * width + j) == 2)
			{
				cout << "PP";
			}
		}
		cout << endl;
	}
}