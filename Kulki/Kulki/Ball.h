#pragma once
#include "atltypes.h"
#include <memory>

#define BLACK RGB(0, 0, 0)

class CBall: public CRect
{

public:
	CBall( int xLeftTop = 0, int yLeftTop = 0, int xRightBottom = 0, int yRightBottom = 0, COLORREF color = BLACK, int nOffX = 3, int nOffY = 3 );
	CBall( const CRect& pRect, COLORREF color = BLACK );
	CBall( const CPoint& LeftTop, const CSize& size, COLORREF color = BLACK );

	~CBall();

public:
	inline void SetColor( COLORREF color ); // ustaw kolor ( Delete + Create ), nie usuwac tu pamieci
	inline void SetBallSize( const CRect& pRect ); // ustaw rozmiar ( referencja do recta )
	void PaintBall( CDC* pDC ); // narysuj kulke

								/////
	void SetBall( const CRect& pRect, COLORREF color, int nOffX, int nOffY ); // zmodyfikowac
	void SetOffset( int nOffx, int nOffy ); // ustawia wektory ruchu
	void SetBoundRect( const CRect& pRect ); // ustawia prostokat ograniczajacy ruch - obszar klienta

	CPen* getBallPen();
	CBrush* getBallBrush();

	int getOffX();
	int getOffY();



private:
	inline void CreateObjects( COLORREF BallColor = BLACK );
	// kolor pedzla i piora ten sam
	// CreatePen
	// CreateSolidBrush

	inline void DeleteObjects(); // DeleteObject() dla piora i pedzla
	void InitObjects( COLORREF BallColor = BLACK ); // przydziela pamiec i wykreowac

private:
	CPen* m_pBallPen;
	CBrush* m_pBallBrush;
	//std::unique_ptr<CPen> m_pBallPen;
	//std::unique_ptr<CBrush> m_pBallBrush;

	// zmodyfikowac konstruktory o te nowe parametry
	int m_nOffX;
	int m_nOffY;
	std::unique_ptr<CRect> m_BoundRect;
};