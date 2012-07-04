#include "Set.h"
#include <vector>
#include <list>
#include <iterator>

using namespace std;

struct MultiSet
{
	unsigned setId;
	vector<SetElement> data;
};

vector<MultiSet> sets;

SetElement* getData(unsigned setId)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			return it->data.data();
		}
	}

	return NULL;
}

unsigned dataSize(unsigned setId)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			return it->data.size();
		}
	}

	return 0;
}

bool exists(unsigned setId)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			return true;
		}
	}

	return false;
}

unsigned addSet()
{
	MultiSet m;

	unsigned prevId = 0;
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId > prevId + 1)
		{
			m.setId = ++prevId;
			sets.insert(it, m);
			return m.setId;
		}
		else
		{
			prevId = it->setId;
		}
	}

	m.setId = ++prevId;
	sets.push_back(m);

	return m.setId;
}

bool removeSet(unsigned setId)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			sets.erase(it);
			return true;
		}
	}
	
	return false;
}

void clear(unsigned setId)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			it->data.clear();
			return;
		}
	}
}

bool isEmpty(unsigned setId)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			return (it->data.size() == 0);
		}
	}

	return false;
}

bool addElement(unsigned setId, unsigned num)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			try
			{
				for (vector<SetElement>::iterator it2 = it->data.begin(); it2 != it->data.end(); it2++)
				{
					if (it2->number == num)
					{
						it2->nOccurrences++;
						return true;
					}
				}

				SetElement me = {0};
				me.number = num;
				me.nOccurrences = 1;
				it->data.push_back(me);
			}
			catch(bad_alloc)
			{
				return false;
			}
			
			return true;
		}
	}

	return false;
}

bool removeElement(unsigned setId, unsigned num)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			for (vector<SetElement>::iterator it2 = it->data.begin(); it2 != it->data.end(); it2++)
			{
				if (it2->number == num)
				{
					it2->nOccurrences--;
					if (!it2->nOccurrences)
					{
						it->data.erase(it2);
					}

					return true;
				}
			}
			
			return false;
		}
	}

	return false;
}

unsigned getOccurrences(unsigned setId, unsigned num)
{
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId)
		{
			for (vector<SetElement>::iterator it2 = it->data.begin(); it2 != it->data.end(); it2++)
			{
				if (it2->number == num)
				{
					return it2->nOccurrences;
				}
			}
			
			return 0;
		}
	}

	return 0;
}

unsigned mergeSets(unsigned setId1, unsigned setId2)
{
	vector<MultiSet>::iterator setIt1, setIt2;
	bool f1, f2;
	f1 = f2 = false;

	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId1)
		{
			setIt1 = it;
			f1 = true;
		}

		if (it->setId == setId2)
		{
			setIt2 = it;
			f2 = true;
		}
	}

	if (!f1 || !f2)
	{
		return 0;
	}

	vector<SetElement> temp;
	for (vector<SetElement>::iterator it2 = setIt2->data.begin(); it2 != setIt2->data.end(); it2++)
	{
		SetElement el = *it2;
		for (vector<SetElement>::iterator it1 = setIt1->data.begin(); it1 != setIt1->data.end(); it1++)
		{
			if (el.number == it1->number && el.nOccurrences < it1->nOccurrences)
			{
				el.nOccurrences = it1->nOccurrences;
			}
		}

		temp.push_back(el);
	}

	for (vector<SetElement>::iterator it1 = setIt1->data.begin(); it1 != setIt1->data.end(); it1++)
	{
		bool f = false;
		for (vector<SetElement>::iterator it2 = setIt2->data.begin(); it2 != setIt2->data.end(); it2++)
		{
			if (it1->number == it2->number)
			{
				f = true;
			}
		}

		if (!f)
		{
			temp.push_back(*it1);
		}
	}

	unsigned newSetId = addSet();
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == newSetId)
		{
			it->data = temp;
			return newSetId;
		}
	}

	return 0;
}


unsigned intersectSets(unsigned setId1, unsigned setId2)
{
	vector<MultiSet>::iterator setIt1, setIt2;
	bool f1, f2;
	f1 = f2 = false;

	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == setId1)
		{
			setIt1 = it;
			f1 = true;
		}

		if (it->setId == setId2)
		{
			setIt2 = it;
			f2 = true;
		}
	}

	if (!f1 || !f2)
	{
		return 0;
	}

	vector<SetElement> temp;

	for (vector<SetElement>::iterator it1 = setIt1->data.begin(); it1 != setIt1->data.end(); it1++)
	{
		for (vector<SetElement>::iterator it2 = setIt2->data.begin(); it2 != setIt2->data.end(); it2++)
		{
			if (it1->number == it2->number)
			{
				if (it1->nOccurrences < it2->nOccurrences)
				{
					temp.push_back(*it1);
				}
				else
				{
					temp.push_back(*it2);
				}
			}
		}
	}

	unsigned newSetId = addSet();
	for (vector<MultiSet>::iterator it = sets.begin(); it != sets.end(); it++)
	{
		if (it->setId == newSetId)
		{
			it->data = temp;
			return newSetId;
		}
	}

	return 0;
}