#pragma once

#include <utility>
#include "afxdialogex.h"

#define TAB_SIZE 50000

struct SimpleSortTime{
	unsigned int insertSortTime;
	unsigned int halfSortTime;
	unsigned int selectSortTime;
};

struct QuickSortTime{
	unsigned int bubbleSortTime;
	unsigned int heapSortTime;
	unsigned int quickSortTime;
};


class Sortowanie
{
public:
	Sortowanie();
	~Sortowanie();

public:
	SimpleSortTime* SimpleSorts();
	QuickSortTime* QuickSorts();

private:
	unsigned int insertSort( int *tab );
	unsigned int halfSort( int *tab );
	unsigned int selectSort( int *tab );

	unsigned int bubbleSort( int *tab );
	unsigned int heapSort(int *t);
	unsigned int quickSort( int *tab, int l, int p );

	void updateHeap( int* tab, int l, int p );

private:
	unsigned int timeDifference( unsigned int start, unsigned int stop );

private:
	int *table;
	unsigned int before;
	unsigned int after;
};

