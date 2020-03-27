
// SortView.cpp : implementation of the CSortView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sort.h"
#endif

//#include "SortDoc.h"
#include "SortView.h"
#include "ColorRect.h"
#include "Coordinates.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CSortView

IMPLEMENT_DYNCREATE(CSortView, CView)

BEGIN_MESSAGE_MAP(CSortView, CView)
END_MESSAGE_MAP()

// CSortView construction/destruction

CSortView::CSortView()
{
	this->m_pClientRect = new CRect;
	
	m_pFontNumbers = new CFont;
	LOGFONT logFontNumbers;
	memset( &logFontNumbers, 0, sizeof( logFontNumbers ) );

	CString sFont( "Arial" );

	lstrcpy( logFontNumbers.lfFaceName, sFont );

	logFontNumbers.lfCharSet = DEFAULT_CHARSET;
	logFontNumbers.lfWeight = FW_NORMAL;
	logFontNumbers.lfHeight = -24;
	logFontNumbers.lfWidth = -10;


	if( !m_pFontNumbers->CreateFontIndirect( &logFontNumbers ) )
	{
		TRACE0( "Could not create font for the trends." );
	}
	// ---------------------------------------------------------
	m_pFontNames = new CFont;
	LOGFONT logFontNames;
	memset( &logFontNames, 0, sizeof( logFontNumbers ) );

	CString sFont1( "Georgia" );

	lstrcpy( logFontNames.lfFaceName, sFont );

	logFontNames.lfCharSet = DEFAULT_CHARSET;
	logFontNames.lfWeight = FW_NORMAL;
	logFontNames.lfHeight = -24;
	logFontNames.lfWidth = -10;


	if( !m_pFontNames->CreateFontIndirect( &logFontNames ) )
	{
		TRACE0( "Could not create font for the trends." );
	}

}

/*
przeniesc rysowanie wykresu do funkcji - nowa metoda w SortView
korzystajac z wektora lines lines.first.first i lines.first.second do liczb
wektor lines wsadzic do .h
metoda do:
	podzialka
	nazwa sortowania
	wywolywanie rectangli


*/



CSortView::~CSortView()
{
	delete m_pClientRect;
	delete m_pFontNumbers;
	delete m_pFontNames;
	//delete sorts;
	/*delete bubbleSort;
	delete heapSort;
	delete insertSort;
	delete quickSort;
	delete selectSort;
	delete halfSort;*/

}

BOOL CSortView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSortView drawing

void CSortView::OnDraw(CDC* pDC)
{
	CSortDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
	// TODO: add draw code for native data here

	GetClientRect( m_pClientRect );
	
	drawPlot( pDC );
	drawSorts( pDC, pDoc );
	drawTime( pDC, pDoc );
	/*
	for( int i = 0; i < pDoc->sorts.size(); ++i )
	{
		CString str;
		str.Format( L"%d", (int) pDoc->sorts[ i ]->GetSortTime() );
		pDC->TextOutW( 10, 30 * ( i + 1 ), str );
	}
	*/
	////////////////////////////////////////////

	
	

	

}


// CSortView diagnostics

#ifdef _DEBUG
void CSortView::AssertValid() const
{
	CView::AssertValid();
}

void CSortView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSortDoc* CSortView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortDoc)));
	return (CSortDoc*)m_pDocument;
}
#endif //_DEBUG


// CSortView message handlers


void CSortView::drawPlot( CDC * pDC )
{

	std::pair<int, int> leftTopPoint( START_COORD, 0.1 * m_pClientRect->Height() );

	std::pair<int, int> rightBottomPoint( ENDX, 0.9 * m_pClientRect->Height() );


	///////////////////////////////////////////

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines;


	for( int i = 0; i < SIZE_LINES + 1; i++ )
	{

		std::pair<std::pair<int, int>, std::pair<int, int>> s;
		s.first.first = START_COORD;
		s.first.second = ( 0.8 * m_pClientRect->Height() / SIZE_LINES ) * i
			+ 0.1 * m_pClientRect->Height();


		s.second.first = ENDX;
		s.second.second = ( 0.8 * m_pClientRect->Height() / SIZE_LINES ) * i
			+ 0.1 * m_pClientRect->Height();


		lines.push_back( s );
	}

	CCoordinates* coord = new CCoordinates( leftTopPoint, rightBottomPoint, lines );

	coord->drawCoordinates( pDC );
}

void CSortView::drawRectangle(CDC* pDC, int num)
{
	for( int i = 0; i < num; ++i )
	{
		POINT leftTop;
		POINT rightBottom;

		leftTop.x = START + i*( RECT_WIDTH + RIGHT_SHIFT );
		leftTop.y = 0.2 * m_pClientRect->Height();
		rightBottom.x = START + i*( RECT_WIDTH + RIGHT_SHIFT ) + RECT_WIDTH;
		rightBottom.y = 0.9 * m_pClientRect->Height();

		CRect r1( leftTop, rightBottom );
		CColorRect rectan( &r1, 1, RED, colors[ i ] );

		rectan.PaintRect( pDC );
	}
}

void CSortView::drawSorts( CDC* pDC, CSortDoc* pDoc )
{
	int status = pDoc->getSortStatus();
	if( status == 3 )			// wszystkie
	{
		drawRectangle( pDC, 6 );
	}
	else if( status == 2 )		// szybkie
	{
		drawRectangle( pDC, 2 );
	}
	else if( status == 1 )		//proste
	{
		drawRectangle( pDC, 4 );
	}
}

void CSortView::drawTime( CDC* pDC, CSortDoc* pDoc )
{
	int status = pDoc->getSortStatus();

	std::vector<std::pair<int, int>> points;

	for( int i = 0; i < SIZE_LINES + 1; ++i )
	{
		std::pair<int, int> s;
		s.first = START_COORD - 40;
		s.second = ( 0.8 * m_pClientRect->Height() / SIZE_LINES ) * i
			+ 0.1 * m_pClientRect->Height();

		points.push_back( s );

		
	}


	CString str = L"1024";
	pDC->TextOutW( points[0].first, points[0].second, str );

}





