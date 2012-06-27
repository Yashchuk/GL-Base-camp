#include "Stack.h"
#include <vector>
#include <iostream>
std::vector<char> data;

void clearStack()
{
	data.clear();
}

bool isEmpty()
{
	return !data.size();
}

bool pushCharacter(char c)
{
	try
	{
		data.push_back(c);
	}
	catch(std::bad_alloc)
	{
		return false;
	}
	return true;
}

char popCharacter()
{
	if(!data.size())
	{
		return 0;
	}
	
	char c = data.back();
	data.pop_back();

	return c;
}

char peekCharacter()
{
	if(!data.size())
	{
		return 0;
	}
	
	return data.back();
}