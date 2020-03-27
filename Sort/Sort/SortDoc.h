
// SortDoc.h : interface of the CSortDoc class
//

#include <vector>
#include "BubbleSort.h"
#include "HalfSort.h"
#include "HeapSort.h"
#include "InsertSort.h"
#include "QuickSort.h"
#include "SelectSort.h"

#pragma once


class CSortDoc : public CDocument
{
protected: // create from serialization only
	CSortDoc();
	DECLARE_DYNCREATE(CSortDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSortDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:
	int *tab;
	int status; //1- proste, 2-szybkie, 3-all
	unsigned int maxSimpleSortTime;
	unsigned int maxQuickSortTime;
public:
	std::vector<Sorter *> sorts;

public:
	int getSortStatus();
	unsigned int getMaxSortTime();
	afx_msg void OnSimpleSorts();
	afx_msg void OnQuickSorts();
	afx_msg void OnAllSorts();

private:
	void countMaxSortTime();
	unsigned int roundMaxSortTime( unsigned int sortTime );
};
