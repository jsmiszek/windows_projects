
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
	logFontNumbers.lfHeight = -12;
	logFontNumbers.lfWidth = -5;

	if( !m_pFontNumbers->CreateFontIndirect( &logFontNumbers ) )
	{
		TRACE0( "Could not create font for the trends." );
	}
	// ---------------------------------------------------------

	m_pFontNames = new CFont;
	LOGFONT logFontNames;
	memset( &logFontNames, 0, sizeof( logFontNumbers ) );

	CString sFont1( "Georgia" );

	lstrcpy( logFontNames.lfFaceName, sFont1 );

	logFontNames.lfCharSet = DEFAULT_CHARSET;
	logFontNames.lfWeight = FW_NORMAL;
	logFontNames.lfHeight = -12;
	logFontNames.lfWidth = -6;


	if( !m_pFontNames->CreateFontIndirect( &logFontNames ) )
	{
		TRACE0( "Could not create font for the trends." );
	}

}


CSortView::~CSortView()
{
	delete m_pClientRect;
	delete m_pFontNumbers;
	delete m_pFontNames;
}

BOOL CSortView::PreCreateWindow(CREATESTRUCT& cs)
{
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
	drawScale( pDC, pDoc );
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

void CSortView::drawSorts(CDC* pDC, CSortDoc* pDoc)
{
	int status = pDoc->getSortStatus();
	unsigned int time = 0;
	CString name;

	CFont* pOldFont = pDC->SelectObject( m_pFontNames );

	int i = 0;
	for( Sorter* sort : pDoc->sorts )
	{
		if( status == 1 )
		{
			if( sort->GetType() == 1 )
			{
				time = sort->GetSortTime();
				name = sort->GetSortName();
			}
			else
				continue;
		}
		else if( status == 2 )
		{
			if( sort->GetType() == 2 )
			{
				time = sort->GetSortTime();
				name = sort->GetSortName();
			}
			else
				continue;
		}
		else if( status == 3 )
		{
			time = sort->GetSortTime();
			name = sort->GetSortName();
		}
		CString str;
		str.Format( L"%d", sort->GetSortTime() );
		pDC->TextOutW( 600, 30*(i+1), str );

		POINT leftTop;
		POINT rightBottom;

		leftTop.x = START + i*( RECT_WIDTH + RIGHT_SHIFT ); 
		//leftTop.y = ( 0.2 * m_pClientRect->Height() );// *( time / pDoc->getMaxSortTime() ); //tu wsadzic time
		//leftTop.y =  (0.8*m_pClientRect->Height() )
		leftTop.y = 0.8*m_pClientRect->Height() * (double)( 1 - (double)time / (double)pDoc->getMaxSortTime() ) +0.1*m_pClientRect->Height();
		rightBottom.x = START + i*( RECT_WIDTH + RIGHT_SHIFT ) + RECT_WIDTH;
		rightBottom.y = 0.9 * m_pClientRect->Height();

		CRect r1( leftTop, rightBottom );
		CColorRect rectan( &r1, 1, RED, colors[ i ] );
		rectan.PaintRect( pDC );

		
		pDC->TextOutW( rightBottom.x - RECT_WIDTH, rightBottom.y + 8, name );
		
		i++;
	}
	pDC->SelectObject( pOldFont );
}


void CSortView::drawScale( CDC* pDC, CSortDoc* pDoc )
{
	CFont* pOldFont = pDC->SelectObject( m_pFontNumbers );

	std::vector<std::pair<int, int>> points;
	std::vector<unsigned int> times = pDoc->getTimeVector();

	for( int i = 0; i < SIZE_LINES + 1; ++i )
	{
		std::pair<int, int> s;
		s.first = START_COORD - 40;
		s.second = ( 0.8 * m_pClientRect->Height() / SIZE_LINES ) * i
			+ 0.1 * m_pClientRect->Height() - 7;

		points.push_back( s );

		CString str;
		str.Format( L"%d", (int) times[ i ] );
		pDC->TextOutW( points[ i ].first, points[ i ].second, str );
	}

	pDC->SelectObject( pOldFont );

	/*
	for( int i = 0; i < SIZE_LINES + 1; ++i )
	{
		CString str;
		str.Format( L"%d", (int) times[ i ] );
		pDC->TextOutW( points[ i ].first, points[ i ].second, str );
	}/*
	str = L"0";
	pDC->TextOutW( points[ 20 ].first, points[ 20 ].second, L"0" );
	pDC->SelectObject( pOldFont );
	/*
	CFont* pOldFont2 = pDC->SelectObject( m_pFontNames );
	//COLORREF oldColor2 = pDC->SetTextColor( RGB( 0, 0, 0 ) );
	pDC->TextOutW( points[ 1 ].first, points[ 1 ].second, pDoc->sorts[ 2 ]->GetSortName() );
	pDC->SelectObject( pOldFont2 );
	*/
}





