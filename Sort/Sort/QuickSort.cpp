#include "stdafx.h"
#include "QuickSort.h"


QuickSort::QuickSort( int* t ): Sorter(t)
{
	type = 2;
	name = "Quick";
}


QuickSort::~QuickSort()
{
}

void QuickSort::Sort()
{
	Quick( tab, 0, TAB_SIZE - 1 );
}


void QuickSort::Quick( int *tab, int l, int p )
{

	int i = l;
	int j = p;
	int x = tab[ ( i + j ) / 2 ];

	while( i < j )
	{
		while( tab[ i ] < x ) i++;
		while( tab[ j ] > x ) j--;

		if( i <= j )
		{
			int pom = tab[ i ];
			tab[ i ] = tab[ j ];
			tab[ j ] = pom;
			i++;
			j--;
		}
	}
	if( l < j )
		Quick( tab, l, j );
	if( i < p )
		Quick( tab, i, p );
}
