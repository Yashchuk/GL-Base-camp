#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

typedef int (*ExecFunc)(int *arg, unsigned nArgs);

struct Command
{
	int id;
	ExecFunc Execute;
};

int *matrix = NULL;
unsigned size = 0;
unsigned nCommands = 4;

Command* init();

int main()
{
	Command *commands = init();

	vector<int> v;

	while (true)
	{
		v.clear();
		cin.clear();
		cin.sync();
		copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(v));
		if (v.size() > 1)
		{
			for (int i = 0; i < nCommands; i++)
			{
				if (commands[i].id == v[0])
				{
					cout << "Command result: " << commands[i].Execute(&v[1], v.size() - 1) << endl;
					for (int i = 0; i < size; i++)
					{
						for (int j = 0; j < size; j++)
						{
							cout << matrix[i * size + j];
						}
						cout << endl;
					}
				}
			}
		}
	}
	delete[] commands;
	return 0;
}

int initializeMatrix(int *arg, unsigned nArgs)
{
	if (nArgs > 0 && arg)
	{
		if (matrix)
		{
			delete[] matrix;
		}

		size = arg[0];
		matrix = new int[size * size];
		memset(matrix, 0, (size * size) * sizeof(int));
	}

	return 0;
}

int changeMatrix(int *arg, unsigned nArgs)
{
	if (nArgs >= 3 && arg)
	{
		if (!matrix)
		{
			return -1;
		}

		int x = arg[0];
		int y = arg[1];

		if ((x < 0 || x >= size) ||
			(y < 0 || y >= size))
		{
			return -1;
		}

		for (int i = x; i < size; i++)
		{
			matrix[y * size + i] += arg[2];
			if (matrix[y * size + i] < 0)
			{
				matrix[y * size + i] = 0;
			}
		}
	}

	return 0;
}

int getSum(int *arg, unsigned nArgs)
{
	int sum = -1;

	if (nArgs >= 4 && arg)
	{
		if (!matrix)
		{
			return -1;
		}

		int x1 = arg[0];
		int y1 = arg[1];
		int x2 = arg[2];
		int y2 = arg[3];

		if (x2 < x1 || y2 < y1)
		{
			return -1;
		}

		if ((x1 < 0 || x2 >= size) ||
			(y1 < 0 || y2 >= size))
		{
			return -1;
		}

		sum = 0;
		for (int i = y1; i <= y2; i++)
		{
			sum += matrix[i * size + x2] - matrix[i * size + x1];
		}
	}

	return sum;
}

int quit(int *arg, unsigned nArgs)
{
	if (matrix)
	{
		delete[] matrix;
	}
	exit(0);
}

Command* init()
{
	Command *commands = new Command[4];
	commands[0].id = 0;
	commands[0].Execute = initializeMatrix;
	commands[1].id = 1;
	commands[1].Execute = changeMatrix;
	commands[2].id = 2;
	commands[2].Execute = getSum;
	commands[3].id = 3;
	commands[3].Execute = quit;
	return commands;
}