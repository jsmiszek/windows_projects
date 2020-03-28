#include "stdafx.h"
#include "HeapSort.h"


HeapSort::HeapSort( int *t ): Sorter(t)
{
	type = 2;
	name.LoadStringW( IDS_HEAP_SORT );
}


HeapSort::~HeapSort()
{
}

void HeapSort::Sort()
{
	//stogowe/kopcowe
	//kopiec: h[i] >= h[2i] oraz h[i] >= h[2i+1]
	//
	//
	for( int j = size / 2 + 1; j > 0; )
		updateHeap( tab, --j, size - 1 );

	for( int j = size - 1; j; )
	{
		int x = tab[ j ];
		tab[ j ] = tab[ 0 ];
		tab[ 0 ] = x;
		updateHeap( tab, 0, --j );
	}
}



void HeapSort::updateHeap( int * tab, int l, int p )
{
	{
		int i = l;
		int j = 2 * i;
		int x = tab[ i ];

		while( j <= p )
		{
			if( j < p )
				if( tab[ j ] < tab[ j + 1 ] )
					j++;

			if( tab[ j ] <= x ) break;

			tab[ i ] = tab[ j ];
			i = j;
			j = 2 * i;
		}
		tab[ i ] = x;
	}
}
