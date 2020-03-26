#include "stdafx.h"
#include "ColorRect.h"


CColorRect::CColorRect( CRect* pRect, int penWidth, COLORREF penColor, COLORREF bkgColor ): CRect( pRect )
{
	this->m_pPen = new CPen( PS_NULL, penWidth, penColor );
	this->m_pBrush = new CBrush( bkgColor );
}

CColorRect::CColorRect( const CRect &pRect, int penWidth, COLORREF penColor, COLORREF bkgColor ): CRect( pRect )
{
	this->m_pPen = new CPen( PS_SOLID, penWidth, penColor );
	this->m_pBrush = new CBrush( bkgColor );
}

CColorRect::CColorRect( const CPoint &LeftTop, const CPoint &RightBottom, int penWidth, COLORREF penColor, COLORREF bkgColor ): CRect( LeftTop, RightBottom )
{
	this->m_pPen = new CPen( PS_SOLID, penWidth, penColor );
	this->m_pBrush = new CBrush( bkgColor );
}

CColorRect::CColorRect( const CPoint &LeftTop, const CSize &size, int penWidth, COLORREF penColor, COLORREF bkgColor ): CRect( LeftTop, size )
{
	this->m_pPen = new CPen( PS_SOLID, penWidth, penColor );
	this->m_pBrush = new CBrush( bkgColor );
}

CColorRect::~CColorRect()
{
	delete m_pPen;
	delete m_pBrush;
}

void CColorRect::PaintRect( CDC* pDC )
{
	/*pDC->SelectObject( this->m_pPen );
	pDC->MoveTo( 50, 50 );
	pDC->LineTo( 50, 300 );*/

	CPen* pOldPen = pDC->SelectObject( m_pPen );

	CBrush* pOldBrush = pDC->SelectObject( m_pBrush );

	//CRect rect( 50, 50, 400, 400 );
	//GetClientRect( (HWND)pDC, &rect );
	//pDC->Rectangle( &rect );
	//pDC->SelectObject( pOldBrush );

	pDC->SelectObject( m_pBrush );
	pDC->Rectangle( this );

	pDC->SelectObject( pOldPen );

	pDC->SelectObject( pOldBrush );
}

CPen* CColorRect::getRectPen()
{
	return this->m_pPen;
}

CBrush * CColorRect::getRectBrush()
{
	return this->m_pBrush;
}

void CColorRect::initAttr()
{
}

void CColorRect::setAttr( int penWidth, COLORREF penColor, COLORREF bkgColor )
{
	this->m_pPen->DeleteObject();
	this->m_pBrush->DeleteObject();

	createAttr( penWidth, penColor, bkgColor );
}

void CColorRect::createAttr( int penWidth, COLORREF penColor, COLORREF bkgColor )
{
	this->m_pPen->CreatePen( PS_NULL, penWidth, penColor );
	this->m_pBrush->CreateSolidBrush( bkgColor );
}



// ColorRect message handlers


