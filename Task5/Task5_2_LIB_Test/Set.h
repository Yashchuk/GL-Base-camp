/** 
  * @file	Set.h
  * @brief	Module providing C interface for multiple set work
  * @author	Vitaliy Sidenko
  * @date	2/06/2012
  */

#ifndef _SET_H
#define _SET_H

struct SetElement
{
	unsigned nOccurrences;
	unsigned number;
};

/**
  * @brief		Get set data as array
  * @param		[in] setId Set id
  * @return		Pointer to data array
  */
SetElement* getData(unsigned setId);

/**
  * @brief		Get data set size
  * @param		[in] setId Set id
  * @return		Number of elements
  */
unsigned dataSize(unsigned setId);

/**
  * @brief		Check if set by fiven id exists
  * @param		[in] setId Set id
  * @return		False if set does not exist
  */
bool exists(unsigned setId);

/**
  * @brief		Add new set
  * @return		Set id
  */
unsigned addSet();

/**
  * @brief		Remove set by id
  * @param		[in] setId Set id
  * @return		False if set not found
  */
bool removeSet(unsigned setId);

/**
  * @brief		Clear set by id
  * @param		[in] setId Set id
  * @return		void
  */
void clear(unsigned setId);

/**
  * @brief		Check if set is empty
  * @param		[in] setId Set id
  * @return		True if empty
  */
bool isEmpty(unsigned setId);

/**
  * @brief		Add element to set
  * @param		[in] setId Set id
  * @param		[in] num Number
  * @return		False if error occured
  */
bool addElement(unsigned setId, unsigned num);

/**
  * @brief		Remove element from set
  * @param		[in] setId Set id
  * @param		[in] num Number
  * @return		False if error occured
  */
bool removeElement(unsigned setId, unsigned num);

/**
  * @brief		Get number of element occurrences in set
  * @param		[in] setId Set id
  * @param		[in] num Number
  * @return		Number of occurrences
  */
unsigned getOccurrences(unsigned setId, unsigned num);

/**
  * @brief		Merge two sets
  * @param		[in] setId1 First set id
  * @param		[in] setId2 Second set id
  * @return		Id of new set
  */
unsigned mergeSets(unsigned setId1, unsigned setId2);

/**
  * @brief		Intersect two sets
  * @param		[in] setId1 First set id
  * @param		[in] setId2 Second set id
  * @return		Id of new set
  */
unsigned intersectSets(unsigned setId1, unsigned setId2);

#endif	/* _SET_H */