/** 
  * @file	Set.h
  * @brief	Module providing C interface for multiple set work
  * @author	Vitaliy Sidenko
  * @date	2/06/2012
  */

#ifndef _SET_H
#define _SET_H

#include <Windows.h>

struct SetElement
{
	unsigned nOccurrences;
	unsigned number;
};

typedef SetElement* (*FUNC0)(unsigned);
typedef unsigned (*FUNC1)(unsigned);
typedef bool (*FUNC2)(unsigned);
typedef unsigned (*FUNC3)();
typedef void (*FUNC4)(unsigned);
typedef bool (*FUNC5)(unsigned, unsigned);
typedef unsigned (*FUNC6)(unsigned, unsigned);

HMODULE hLib = NULL;

/**
  * @brief		Get set data as array
  * @param		[in] setId Set id
  * @return		Pointer to data array
  */
FUNC0 getData;

/**
  * @brief		Get data set size
  * @param		[in] setId Set id
  * @return		Number of elements
  */
FUNC1 dataSize;

/**
  * @brief		Check if set by fiven id exists
  * @param		[in] setId Set id
  * @return		False if set does not exist
  */
FUNC2 exists;

/**
  * @brief		Add new set
  * @return		Set id
  */
FUNC3 addSet;

/**
  * @brief		Remove set by id
  * @param		[in] setId Set id
  * @return		False if set not found
  */
FUNC2 removeSet;

/**
  * @brief		Clear set by id
  * @param		[in] setId Set id
  * @return		void
  */
FUNC4 clear;

/**
  * @brief		Check if set is empty
  * @param		[in] setId Set id
  * @return		True if empty
  */
FUNC2 isEmpty;

/**
  * @brief		Add element to set
  * @param		[in] setId Set id
  * @param		[in] num Number
  * @return		False if error occured
  */
FUNC5 addElement;

/**
  * @brief		Remove element from set
  * @param		[in] setId Set id
  * @param		[in] num Number
  * @return		False if error occured
  */
FUNC5 removeElement;

/**
  * @brief		Get number of element occurrences in set
  * @param		[in] setId Set id
  * @param		[in] num Number
  * @return		Number of occurrences
  */
FUNC6 getOccurrences;

/**
  * @brief		Merge two sets
  * @param		[in] setId1 First set id
  * @param		[in] setId2 Second set id
  * @return		Id of new set
  */
FUNC6 mergeSets;

/**
  * @brief		Intersect two sets
  * @param		[in] setId1 First set id
  * @param		[in] setId2 Second set id
  * @return		Id of new set
  */
FUNC6 intersectSets;

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
	hLib = LoadLibrary("Task5_2_DLL.dll");
	if (!hLib)
	{
		return false;
	}

	getData = (FUNC0)GetProcAddress(hLib, "getData");
	if (!getData)
	{
		unloadDll();
		return false;
	}
	dataSize = (FUNC1)GetProcAddress(hLib, "dataSize");
	if (!dataSize)
	{
		unloadDll();
		return false;
	}
	exists = (FUNC2)GetProcAddress(hLib, "exists");
	if (!exists)
	{
		unloadDll();
		return false;
	}
	addSet = (FUNC3)GetProcAddress(hLib, "addSet");
	if (!addSet)
	{
		unloadDll();
		return false;
	}
	removeSet = (FUNC2)GetProcAddress(hLib, "removeSet");
	if (!removeSet)
	{
		unloadDll();
		return false;
	}
	clear = (FUNC4)GetProcAddress(hLib, "clear");
	if (!clear)
	{
		unloadDll();
		return false;
	}
	isEmpty = (FUNC2)GetProcAddress(hLib, "isEmpty");
	if (!isEmpty)
	{
		unloadDll();
		return false;
	}
	addElement = (FUNC5)GetProcAddress(hLib, "addElement");
	if (!addElement)
	{
		unloadDll();
		return false;
	}
	removeElement = (FUNC5)GetProcAddress(hLib, "removeElement");
	if (!removeElement)
	{
		unloadDll();
		return false;
	}
	getOccurrences = (FUNC6)GetProcAddress(hLib, "getOccurrences");
	if (!getOccurrences)
	{
		unloadDll();
		return false;
	}
	mergeSets = (FUNC6)GetProcAddress(hLib, "mergeSets");
	if (!mergeSets)
	{
		unloadDll();
		return false;
	}
	intersectSets = (FUNC6)GetProcAddress(hLib, "intersectSets");
	if (!intersectSets)
	{
		unloadDll();
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

#endif	/* _SET_H */