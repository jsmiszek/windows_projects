#include "stdafx.h"
#include "InsertSort.h"


InsertSort::InsertSort( int *t ): Sorter(t)
{
	type = 1;
	name = "Insert";
}


InsertSort::~InsertSort()
{
}

void InsertSort::Sort()
{
	for( int i = 1; i < size; i++ )
	{
		int x = tab[ i ];
		int j = i - 1;
		while( ( j >= 0 ) && ( tab[ j ] > x ) )
			tab[ j + 1 ] = tab[ j-- ];
		tab[ j + 1 ] = x;
	}
}
