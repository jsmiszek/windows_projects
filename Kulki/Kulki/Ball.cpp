#include "stdafx.h"
#include "Ball.h"

#include "stdafx.h"
#include "Ball.h"

#define RED RGB(255, 0, 0)

CBall::CBall( int xLeftTop, int yLeftTop, int xRightBottom, int yRightBottom, COLORREF color, int nOffX, int nOffY )
	: CRect( xLeftTop, yLeftTop, xRightBottom, yRightBottom )
{
	//m_pBallPen = std::make_unique<CPen>(  ); // w nawiasie parametry
	InitObjects( color );
	m_nOffX = nOffX;
	m_nOffY = nOffY;
}

CBall::CBall( const CRect & pRect, COLORREF color )
{
}

CBall::CBall( const CPoint & LeftTop, const CSize & size, COLORREF color )
{
}

CBall::~CBall()
{
	delete m_pBallPen;
	delete m_pBallBrush;
}

inline void CBall::SetColor( COLORREF color )
{
}

inline void CBall::SetBallSize( const CRect & pRect )
{
}

void CBall::PaintBall( CDC * pDC )
{
}

void CBall::SetOffset( int nOffx, int nOffy )
{
	m_nOffX *= nOffx;
	m_nOffY *= nOffy;
}

void CBall::SetBoundRect( const CRect & pRect )
{
	int size = this->right - this->left;
	if( this->right > pRect.right ){
		this->right = pRect.right;
		this->left = this->right - size;
		SetOffset( -1, 1 );
	}

	if( this->left < pRect.left ){
		this->left = pRect.left;
		this->right = this->left + size;
		SetOffset( -1, 1 );
	}

	if( this->bottom > pRect.bottom ){
		this->bottom = pRect.bottom;
		this->top = this->bottom - size;
		SetOffset( 1, -1 );
	}

	if( this->top < pRect.top ){
		this->top = pRect.top;
		this->bottom = this->top + size;
		SetOffset( 1, -1 );
	}
}

CPen* CBall::getBallPen()
{
	return m_pBallPen;
}

CBrush * CBall::getBallBrush()
{
	return m_pBallBrush;
}

int CBall::getOffX()
{
	return m_nOffX;
}

int CBall::getOffY()
{
	return m_nOffY;
}

inline void CBall::CreateObjects( COLORREF BallColor )
{
}

inline void CBall::DeleteObjects()
{
}

void CBall::InitObjects( COLORREF BallColor )
{
	//m_pBallPen = std::make_unique<CPen>(PS_SOLID, 2, BallColor); // w nawiasie parametry
	//m_pBallBrush = std::make_unique<CBrush>(BallColor);
	m_pBallPen = new CPen( PS_SOLID, 2, BallColor );
	m_pBallBrush = new CBrush( BallColor );
}