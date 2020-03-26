#pragma once
#include "Sorter.h"
class HeapSort:
	public Sorter
{
public:
	HeapSort(int *t);
	~HeapSort();
	void Sort();
private:
	void updateHeap( int *tab, int l, int p );
};

