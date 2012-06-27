#include "Stack.h"
#include <vector>

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
	if(!isEmpty)
	{
		return 0;
	}
	
	char c = data.back();
	data.pop_back();

	return c;
}

char peekCharacter()
{
	if(!isEmpty)
	{
		return 0;
	}
	
	return data.back();
}