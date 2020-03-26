#include "stdafx.h"
#include "Sortowanie.h"
#include <time.h>

Sortowanie::Sortowanie()
{
	table = new int[ TAB_SIZE ];

	srand( time( NULL ) );

	for( int i = 0; i < TAB_SIZE; ++i )
		table[ i ] = rand() % 1000;
}


Sortowanie::~Sortowanie()
{
	delete table;
}

SimpleSortTime* Sortowanie::SimpleSorts()
{
	SimpleSortTime *time = new SimpleSortTime;

	time->insertSortTime = insertSort( table );
	time->halfSortTime = halfSort( table );
	time->selectSortTime = selectSort( table );

	return time;
}

QuickSortTime* Sortowanie::QuickSorts()
{
	QuickSortTime *time = new QuickSortTime;

	time->bubbleSortTime = bubbleSort( table );
	time->heapSortTime = heapSort( table );
	time->quickSortTime = quickSort( table, 0, TAB_SIZE - 1 );

	return time;
}


//=========================================== sortowania proste


unsigned int Sortowanie::insertSort( int *tab )
{
	before = ::GetTickCount();

	for( int i = 1; i < TAB_SIZE; i++ )
	{
		int x = tab[ i ];
		int j = i - 1;
		while( ( j >= 0 ) && ( tab[ j ] > x ) )
			tab[ j + 1 ] = tab[ j-- ];
		tab[ j + 1 ] = x;
	}
	
	after = ::GetTickCount();
	return timeDifference( before, after );
}


//====================================
unsigned int Sortowanie::halfSort( int *tab )
{
	before = ::GetTickCount();

	for( int i = 1; i < TAB_SIZE; i++ ) {

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
	
	after = ::GetTickCount();
	return timeDifference( before, after );
}

//====================================
unsigned int Sortowanie::selectSort( int *tab )
{
	before = GetTickCount();

	for( int i = 0; i < TAB_SIZE - 1; i++ )
	{
		int min = tab[ i ];
		int pozMin = i;

		for( int j = i + 1; j < TAB_SIZE; j++ )
			if( tab[ j ] < min )
			{
				min = tab[ j ];
				pozMin = j;
			}

		tab[ pozMin ] = tab[ i ];
		tab[ i ] = min;
	}

	after = ::GetTickCount();
	return timeDifference( before, after );
}


//====================================== sortownania szybkie


//====================================
unsigned int Sortowanie::bubbleSort( int *tab )
{
	before = ::GetTickCount();

	//od du?ych do ma?ych
	for( int j = 0; j < TAB_SIZE - 1; j++ )
	{
		for( int i = TAB_SIZE - 1; i > j; i-- )
		{
			if( tab[ i ] < tab[ i - 1 ] )
			{
				int temp = tab[ i ];
				tab[ i ] = tab[ i - 1 ];
				tab[ i - 1 ] = temp;
			}
		}
	}
	after = ::GetTickCount();
	return timeDifference( before, after );
}



//====================================
unsigned int Sortowanie::heapSort(int *t)
{
	before = ::GetTickCount();
	//stogowe/kopcowe
	//kopiec: h[i] >= h[2i] oraz h[i] >= h[2i+1]

	for( int j = TAB_SIZE / 2 + 1; j > 0; )
		updateHeap( t, --j, TAB_SIZE - 1 );

	for( int j = TAB_SIZE - 1; j; )
	{
		int x = t[ j ];
		t[ j ] = t[ 0 ];
		t[ 0 ] = x;
		updateHeap( t, 0, --j );
	}
	after = ::GetTickCount();
	return timeDifference( before, after );
}


//====================================
void Sortowanie::updateHeap( int* t, int l, int p )
{
	int i = l;
	int j = 2 * i;
	int x = t[ i ];

	while( j <= p )
	{
		if( j < p )
			if( t[ j ] < t[ j + 1 ] )
				j++;

		if( t[ j ] <= x ) break;

		t[ i ] = t[ j ];
		i = j;
		j = 2 * i;
	}
	t[ i ] = x;
}


//====================================
unsigned int Sortowanie::quickSort( int *t, int l, int p )
{
	before = ::GetTickCount();

	int i = l;
	int j = p;
	int x = t[ ( i + j ) / 2 ];

	while( i < j )
	{
		while( t[ i ] < x ) i++;
		while( t[ j ] > x ) j--;

		if( i <= j )
		{
			int pom = t[ i ];
			t[ i ] = t[ j ];
			t[ j ] = pom;
			i++;
			j--;
		}
	}
	if( l < j )
		quickSort( t, l, j );
	if( i < p )
		quickSort( t, i, p );

	after = ::GetTickCount();
	return timeDifference( before, after );
}



unsigned int Sortowanie::timeDifference( unsigned int start, unsigned int stop )
{
	return stop - start;
}