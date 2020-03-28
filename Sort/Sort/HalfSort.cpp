#include "stdafx.h"
#include "HalfSort.h"


HalfSort::HalfSort( int* t ): Sorter(t)
{
	type = 1;
	name.LoadStringW( IDS_HALF_SORT );
}


HalfSort::~HalfSort()
{
}

void HalfSort::Sort()
{
	for( int i = 1; i < size; i++ ) {

		int x = tab[ i ];
		int l = 0;
		int p = i - 1;
		int sr;

		while( l <= p )
		{
			sr = ( l + p ) / 2;
			if( x < tab[ sr ] )
				p = sr - 1;
			else
				l = sr + 1;
		}
		if( l < i )
		{
			memcpy( tab + l + 1, tab + l, ( i - l ) * sizeof( int ) ); // MEGAFAST!
																	   //for ( int j = i - 1; j >= sr; j-- )
																	   //tab[ j + 1 ] = tab[ j ];
			tab[ l ] = x;
		}
	}
}
