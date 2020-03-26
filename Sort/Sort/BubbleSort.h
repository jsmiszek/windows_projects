#pragma once
#include "Sorter.h"
class BubbleSort:
	public Sorter
{
public:
	BubbleSort(int *tab);
	~BubbleSort();
	void Sort();
};

