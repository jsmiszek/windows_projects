#include "stdafx.h"
#include "ColorRect.h"

// ColorRect.cpp : implementation file
//

#include "stdafx.h"
#include "Win.h"
#include "ColorRect.h"


// ColorRect

CColorRect::CColorRect( CRect * pRect, int penWidth, COLORREF penColor, COLORREF bkgColor )
{
	return;
}

CColorRect::CColorRect( const CRect & )
{
	return;
}

CColorRect::CColorRect( const CPoint & LeftTop, const CPoint & RightBottom )
{
	return;
}

CColorRect::CColorRect( const CPoint &, const CSize & )
{
	return;
}

CColorRect::~CColorRect()
{
	return;
}

void CColorRect::PointRect( CDC * pDC )
{
}

void CColorRect::setAttr( int penWidth, COLORREF penColor, COLORREF bkgColor )
{
}

CPen * CColorRect::getRectPen()
{
	return nullptr;
}

CBrush * CColorRect::getRectBrush()
{
	return nullptr;
}

void CColorRect::initAttr()
{
}

void CColorRect::createAttr( int penWidth, COLORREF penColor, COLORREF bkgColor )
{
}



// ColorRect message handlers


