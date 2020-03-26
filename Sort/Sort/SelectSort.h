#pragma once
#include "Sorter.h"
class SelectSort:
	public Sorter
{
public:
	SelectSort( int* t );
	~SelectSort();

	void Sort();
};

