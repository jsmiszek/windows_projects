
// SortView.cpp : implementation of the CSortView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sort.h"
#endif

#include "SortDoc.h"
#include "SortView.h"
#include "ColorRect.h"
#include "Coordinates.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CSortView

IMPLEMENT_DYNCREATE(CSortView, CView)

BEGIN_MESSAGE_MAP(CSortView, CView)
	ON_COMMAND( ID_PROSTE, &CSortView::OnSimpleSort )
	ON_COMMAND( ID_SZYBKIE, &CSortView::OnQuickSort )
	ON_COMMAND( ID_WSZYSTKIE, &CSortView::OnAllSort )
END_MESSAGE_MAP()

// CSortView construction/destruction

CSortView::CSortView()
{
	// TODO: add construction code here
	this->m_pClientRect = new CRect;
	//this->simpleSortTime = new SimpleSortTime;
	//this->quickSortTime = new QuickSortTime;
	//this->sort = new Sortowanie;


	//this->bubbleSort = new BubbleSort( tab );
	//this->halfSort = new HalfSort( tab );
	//this->insertSort = new InsertSort( tab );
	//this->selectSort = new SelectSort( tab );

	//this->heapSort = new HeapSort( tab );
	//this->quickSort = new QuickSort( tab );
	

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
	drawRectangle( pDC );

	for( int i = 0; i < pDoc->sorts.size(); ++i )
	{
		CString str;
		str.Format( L"%d", (int) pDoc->sorts[ i ]->GetSortTime() );
		pDC->TextOutW( 10, 30 * ( i + 1 ), str );
	}

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

void CSortView::drawRectangle(CDC* pDC)
{
	for( int i = 0; i < 6; ++i )
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

void CSortView::OnSimpleSort()
{
		
}


void CSortView::OnQuickSort()
{
	
}


void CSortView::OnAllSort()
{
	
}
