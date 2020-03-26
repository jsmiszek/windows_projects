#pragma once
#include "Sorter.h"
class InsertSort:
	public Sorter
{
public:
	InsertSort(int *t);
	~InsertSort();

	void Sort();
};

