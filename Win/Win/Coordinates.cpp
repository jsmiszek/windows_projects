#include "stdafx.h"
#include "Coordinates.h"

CCoordinates::CCoordinates( /*CPen * pPen*/std::pair<int, int> leftTop, std::pair<int, int> rightBottom )
{
	this->m_pPen = new CPen( PS_SOLID, 3, RGB( 0, 0, 0 ) );
	this->leftTop.first = leftTop.first;
	this->leftTop.second = leftTop.second;
	this->rightBottom.first = rightBottom.first;
	this->rightBottom.second = rightBottom.second;
}

CCoordinates::CCoordinates( std::pair<int, int> leftTop, std::pair<int, int> rightBottom, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> cLines2 )
{
	this->m_pPen = new CPen( PS_SOLID, 3, RGB( 0, 0, 0 ) );
	this->leftTop.first = leftTop.first;
	this->leftTop.second = leftTop.second;
	this->rightBottom.first = rightBottom.first;
	this->rightBottom.second = rightBottom.second;

	for( int i = 0; i < cLines2.size(); i++ )
	{
		std::pair<std::pair<int, int>, std::pair<int, int>> s;
		s.first.first = cLines2[ i ].first.first;
		s.first.second = cLines2[ i ].first.second;
		s.second.first = cLines2[ i ].second.first;
		s.second.second = cLines2[ i ].second.second;

		lines2.push_back( s );
	}
}

CCoordinates::~CCoordinates()
{
	delete m_pPen;
}

void CCoordinates::drawCoordinates( CDC * pDC )
{
	CPen* pOldPen = pDC->SelectObject( getCPen() );
	pDC->MoveTo( this->leftTop.first, this->leftTop.second );
	pDC->LineTo( this->leftTop.first, this->rightBottom.second );
	pDC->LineTo( this->rightBottom.first, this->rightBottom.second );

	//rysujemy kreski
	CPen* m_pPenLines = new CPen( PS_DOT, 1, RGB(173, 173, 133) );
	pOldPen = pDC->SelectObject( m_pPenLines );
/*
	pDC->MoveTo( this->leftTop.first, this->rightBottom.second );
	for( int i = 1; i < 10; ++i )
	{
		pDC->MoveTo( this->leftTop.first, this->rightBottom.second - i * SHIFT );
		pDC->LineTo( ENDX, this->rightBottom.second - i * SHIFT );
		
	}
	*/
	////////////////////////////////////////////
	for( int i = 2; i < lines2.size()-1; i++ )
	{
		pDC->MoveTo( lines2[ i ].first.first, lines2[ i ].first.second );
		pDC->LineTo( lines2[ i ].second.first, lines2[ i ].second.second );
	}
	///////////////////////////////////////////////
	pDC->SelectObject( pOldPen );
}

CPen* CCoordinates::getCPen()
{
	return this->m_pPen;
}
