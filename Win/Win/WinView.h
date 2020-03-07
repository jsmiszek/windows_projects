
// WinView.h : interface of the CWinView class
//

#pragma once

#define RED RGB(255, 0, 0)
#define BLUE RGB(128, 179, 255)
#define PINK RGB(255, 128, 255)
#define GREEN RGB(102, 255, 102)
#define PEACH RGB(255, 179, 102)
#define PURPLE RGB(230, 153, 255)
#define YELLOW RGB(255, 255, 102)

#include <vector>

//static COLORREF colors[] = { RGB( 128, 179, 255 ),RGB( 255, 128, 255 ),RGB( 102, 255, 102 ),RGB( 255, 179, 102 ),RGB( 230, 153, 255 ),RGB( 255, 255, 102 ) };

static COLORREF colors[] = { BLUE, PINK, GREEN, PEACH, PURPLE, YELLOW };

//enum colors{ BLUE=RGB( 128, 179, 255 ), PINK, GREEN, PEACH, PURPLE, YELLOW};
//enum colors{
//	1=RGB( 128, 179, 255 ),
//	2=RGB(255, 128, 255),3=RGB(102, 255, 102),
//4=RGB(255, 179, 102),
//5=RGB(230, 153, 255),
//6=RGB(255, 255, 102)
//};

class CWinView : public CView
{
protected: // create from serialization only
	CWinView();
	DECLARE_DYNCREATE(CWinView)

// Attributes
public:
	CWinDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CWinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	CRect* m_pClientRect;
};

#ifndef _DEBUG  // debug version in WinView.cpp
inline CWinDoc* CWinView::GetDocument() const
   { return reinterpret_cast<CWinDoc*>(m_pDocument); }
#endif

