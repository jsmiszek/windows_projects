#pragma once

#include "afxdialogex.h"
#define BLACK	RGB(0, 0, 0)


class CColorRect: public CRect
{

public:
	CColorRect( CRect* pRect = NULL, int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK );
	CColorRect( const CRect& /*...""...*/ );
	CColorRect( const CPoint& LeftTop, const CPoint& RightBottom /*...""...*/ ); //x, y
	CColorRect( const CPoint&, const CSize& /*...""...*/ );

	~CColorRect();

public:
	void PointRect( CDC* pDC );
	void setAttr( int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK );
	CPen* getRectPen();
	CBrush* getRectBrush();

private:
	void initAttr();
	void createAttr( int penWidth = 0, COLORREF penColor = BLACK, COLORREF bkgColor = BLACK );

private:
	CPen* m_pPen;
	CBrush* m_pBrush;

};




