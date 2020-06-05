
// KulkiView.h : interface of the CKulkiView class
//

#pragma once
#include <vector>
#include "Ball.h"

class CKulkiView : public CView
{
protected: // create from serialization only
	CKulkiView();
	DECLARE_DYNCREATE(CKulkiView)

// Attributes
public:
	CKulkiDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CKulkiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStartStop();
	afx_msg void OnAddBall();
	afx_msg void OnDeleteBall();

private:
	bool m_bStartStop;
	CRect* m_pClientRect;
	UINT_PTR m_nTimerID;

	CRect* m_pBall;
	CPen* m_pBallPen;
	CBrush* m_pBallBrush;

	short int amountBalls;

	std::vector<CBall*> m_pBalls;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer( UINT_PTR nIDEvent );
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL );
	afx_msg void OnSize( UINT nType, int cx, int cy );
};

#ifndef _DEBUG  // debug version in KulkiView.cpp
inline CKulkiDoc* CKulkiView::GetDocument() const
   { return reinterpret_cast<CKulkiDoc*>(m_pDocument); }
#endif

