#pragma once
#include "Sorter.h"
class HalfSort:
	public Sorter
{
public:
	HalfSort( int* t );
	~HalfSort();
	void Sort();

};

