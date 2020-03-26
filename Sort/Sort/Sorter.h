#pragma once
#define TAB_SIZE 150000

class Sorter
{
public:
	Sorter();
	Sorter(int *t);
	virtual ~Sorter();

public:
	virtual void Sort() = 0;
	unsigned int GetSortTime();
	CString GetSortName();

protected:
	unsigned int sortingTime = -1;
	int type; // 1 - proste 2 - szybkie
	int tab[TAB_SIZE];
	int size = TAB_SIZE;
	CString name;

};

