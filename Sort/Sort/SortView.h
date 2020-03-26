
// SortView.h : interface of the CSortView class
//

#pragma once

#include "SortDoc.h"
//#include "Sortowanie.h"
#include "BubbleSort.h"
#include "HalfSort.h"
#include "HeapSort.h"
#include "InsertSort.h"
#include "QuickSort.h"
#include "SelectSort.h"

#include <vector>

#define RED RGB(255, 0, 0)
#define BLUE RGB(128, 179, 255)
#define PINK RGB(255, 128, 255)
#define GREEN RGB(102, 255, 102)
#define PEACH RGB(255, 179, 102)
#define PURPLE RGB(230, 153, 255)
#define YELLOW RGB(255, 255, 102)

#define RIGHT_SHIFT 30
#define RECT_WIDTH 50 
#define START 100
#define START_COORD 50
#define ENDY 500

#define SIZE_LINES 20

static COLORREF colors[] = { BLUE, PINK, GREEN, PEACH, PURPLE, YELLOW };

class CSortView : public CView
{
protected: // create from serialization only
	CSortView();
	DECLARE_DYNCREATE(CSortView)

// Attributes
public:
	CSortDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSortView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	CRect* m_pClientRect;

	//struct SimpleSortTime* simpleSortTime;
	//struct QuickSortTime* quickSortTime;
	//Sortowanie* sort;

	int *tab;

	Sorter* bubbleSort;
	Sorter* halfSort;
	Sorter* heapSort;
	Sorter* insertSort;
	Sorter* quickSort;
	Sorter* selectSort;

public:
	afx_msg void OnSimpleSort();
	afx_msg void OnQuickSort();
	afx_msg void OnAllSort();
};

#ifndef _DEBUG  // debug version in SortView.cpp
inline CSortDoc* CSortView::GetDocument() const
   { return reinterpret_cast<CSortDoc*>(m_pDocument); }
#endif

