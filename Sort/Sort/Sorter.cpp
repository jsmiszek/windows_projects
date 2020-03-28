#include "stdafx.h"
#include "Sorter.h"

Sorter::Sorter(){}

Sorter::Sorter(int *t)
{
	for( int i = 0; i < TAB_SIZE; i++ )
		tab[ i ] = t[ i ];
}


Sorter::~Sorter()
{
}

unsigned int Sorter::GetSortTime()
{
	if( sortingTime == -1 ) {
		unsigned int beforeSorting = ::GetTickCount();
		Sort();
		unsigned int afterSorting = ::GetTickCount();
		sortingTime = afterSorting - beforeSorting;
		return sortingTime;
	}
	else
		return sortingTime;
}

CString Sorter::GetSortName()
{
	return name;
}

int Sorter::GetType()
{
	return type;
}
