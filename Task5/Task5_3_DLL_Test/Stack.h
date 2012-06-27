#ifndef _STACK_H
#define _STACK_H

#include <Windows.h>

typedef void (*FUNC0)();
typedef bool (*FUNC1)();
typedef bool (*FUNC2)(char);
typedef char (*FUNC3)();

FUNC0 clearStack;

FUNC1 isEmpty;

FUNC2 pushCharacter;

FUNC3 popCharacter;

FUNC3 peekCharacter;

bool loadUpDll()
{
	HINSTANCE hGetProcIDDLL = LoadLibrary("Task5_3_DLL.dll");
	if (!hGetProcIDDLL)
	{
		return false;
	}

	clearStack = (FUNC0)GetProcAddress(hGetProcIDDLL, "clearStack");
	if (!clearStack)
	{
		return false;
	}
	isEmpty = (FUNC1)GetProcAddress(hGetProcIDDLL, "isEmpty");
	if (!isEmpty)
	{
		return false;
	}
	pushCharacter = (FUNC2)GetProcAddress(hGetProcIDDLL, "pushCharacter");
	if (!pushCharacter)
	{
		return false;
	}
	popCharacter = (FUNC3)GetProcAddress(hGetProcIDDLL, "popCharacter");
	if (!popCharacter)
	{
		return false;
	}
	peekCharacter = (FUNC3)GetProcAddress(hGetProcIDDLL, "peekCharacter");
	if (!peekCharacter)
	{
		return false;
	}

	return true;
}

#endif /* _STACK_H */