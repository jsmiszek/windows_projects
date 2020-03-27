
// SortView.h : interface of the CSortView class
//

#pragma once

#include "SortDoc.h"
//#include "Sortowanie.h"


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
#define START 120
#define START_COORD 80

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
	CFont* m_pFontNumbers;
	CFont* m_pFontNames;

	//struct SimpleSortTime* simpleSortTime;
	//struct QuickSortTime* quickSortTime;
	//Sortowanie* sort;


private:
	void drawPlot(CDC* pDC);
	void drawRectangle(CDC* pDC, int num);
private:
	void drawSorts( CDC* pDC, CSortDoc* pDoc );
	void drawTime(CDC* pDC, CSortDoc* pDoc );

};

#ifndef _DEBUG  // debug version in SortView.cpp
inline CSortDoc* CSortView::GetDocument() const
   { return reinterpret_cast<CSortDoc*>(m_pDocument); }
#endif

