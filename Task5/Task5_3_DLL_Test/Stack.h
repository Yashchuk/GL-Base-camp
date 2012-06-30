#ifndef _STACK_H
#define _STACK_H

#include <Windows.h>

typedef void (*FUNC0)();
typedef bool (*FUNC1)();
typedef bool (*FUNC2)(char);
typedef char (*FUNC3)();

HINSTANCE hLib;

/**
  * @brief		Clear stack
  * @return		void
  */
FUNC0 clearStack;

/**
  * @brief		Check if stack is empty
  * @return		Boolean value
  */
FUNC1 isEmpty;

/**
  * @brief		Push charcter into stack
  * @param		[in] c Character to push
  * @return		False if stack is full
  */
FUNC2 pushCharacter;

/**
  * @brief		Pop charcter from stack
  * @return		Character or 0 if stack was empty
  */
FUNC3 popCharacter;

/**
  * @brief		Get charcter from the top of stack
  * @return		Character or 0 if stack was empty
  */
FUNC3 peekCharacter;

/**
  * @brief		Load fucntions from dll
  * @return		Flase if error occured
  */
bool loadUpDll();

/**
  * @brief		Unload dll
  * @return		void
  */
void unloadDll();

bool loadUpDll()
{
	hLib = LoadLibrary("Task5_3_DLL.dll");
	if (!hLib)
	{
		return false;
	}

	clearStack = (FUNC0)GetProcAddress(hLib, "clearStack");
	if (!clearStack)
	{
		return false;
	}
	isEmpty = (FUNC1)GetProcAddress(hLib, "isEmpty");
	if (!isEmpty)
	{
		return false;
	}
	pushCharacter = (FUNC2)GetProcAddress(hLib, "pushCharacter");
	if (!pushCharacter)
	{
		return false;
	}
	popCharacter = (FUNC3)GetProcAddress(hLib, "popCharacter");
	if (!popCharacter)
	{
		return false;
	}
	peekCharacter = (FUNC3)GetProcAddress(hLib, "peekCharacter");
	if (!peekCharacter)
	{
		return false;
	}

	return true;
}

void unloadDll()
{
	if (hLib)
	{
		FreeLibrary(hLib);
	}
}

#endif /* _STACK_H */