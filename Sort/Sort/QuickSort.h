#pragma once
#include "Sorter.h"
class QuickSort:
	public Sorter
{
public:
	QuickSort(int *t);
	~QuickSort();

	void Sort();
	void Quick( int *tab, int l, int p );
/*private:
	int l;
	int p;*/
};

