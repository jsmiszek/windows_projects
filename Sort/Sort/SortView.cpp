
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

	tab = new int[ TAB_SIZE ];

	srand( time( NULL ) );

	for( int i = 0; i < TAB_SIZE; ++i )
		tab[ i ] = rand() % 1000;

	this->bubbleSort = new BubbleSort( tab );
	this->halfSort = new HalfSort( tab );
	this->heapSort = new HeapSort( tab );
	this->insertSort = new InsertSort( tab );
	this->quickSort = new QuickSort( tab );
	this->selectSort = new SelectSort( tab );

}

CSortView::~CSortView()
{
	delete m_pClientRect;
	delete tab;
	delete bubbleSort;
	delete heapSort;
	delete insertSort;
	delete quickSort;
	delete selectSort;
	delete halfSort;

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

	//Sortowanie* sort = new Sortowanie;
	//sort->rysuj( pDC );

	GetClientRect( m_pClientRect );

	//CRect* rect;

	std::pair<int, int> leftTopPoint( START_COORD, 0.1 * m_pClientRect->Height() );
	////std::pair<int, int> leftTopPoint( START_COORD, m_pClientRect->bottom );

	std::pair<int, int> rightBottomPoint( ENDX, 0.9 * m_pClientRect->Height() );
	////std::pair<int, int> rightBottomPoint( ENDX, 0.9 * m_pClientRect->bottom );
	//CCoordinates coord( leftTopPoint, rightBottomPoint );

	///////////////////////////////////////////

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines;

	for( int i = 0; i < SIZE_LINES + 1; i++ )
	{

		std::pair<std::pair<int, int>, std::pair<int, int>> s;
		s.first.first = START_COORD;
		//s.first.second = (( m_pClientRect->bottom - m_pClientRect->top) * i / SIZE_LINES);
		s.first.second = ( 0.8 * m_pClientRect->Height() / SIZE_LINES ) * i
			+ 0.1 * m_pClientRect->Height();


		s.second.first = ENDX; //0.8 * m_pClientRect->right;
							   //s.second.second = i *(m_pClientRect->bottom - m_pClientRect->top) / SIZE_LINES;
		s.second.second = ( 0.8 * m_pClientRect->Height() / SIZE_LINES ) * i
			+ 0.1 * m_pClientRect->Height();


		//if( s.first.second < START_COORD )
		//{
		//	s.first.second = START_COORD;
		//	s.second.second = START_COORD;
		//}

		lines.push_back( s );
	}
	//std::cout << lines.size() << std::endl;

	CCoordinates* coord = new CCoordinates( leftTopPoint, rightBottomPoint, lines );

	coord->drawCoordinates( pDC );

	////////////////////////////////////////////

	//for( int i = 0; i < 6; ++i )
	//{
	//	CRect rect( START + i*( RECT_WIDTH + RIGHT_SHIFT ), 0.2 * m_pClientRect->Height(),
	//		START + i*( RECT_WIDTH + RIGHT_SHIFT ) + RECT_WIDTH, 0.9 * m_pClientRect->Height() );
	//	CColorRect* rectan = new CColorRect( &rect, 10, RED, colors[ i ] );

	//	rectan->PaintRect( pDC, rect );
	//}

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

	

	CString str;
	str.Format( L"%d", (int)halfSort->GetSortTime() );
	pDC->TextOutW( 10, 30, str );

	CString str1;
	str1.Format( L"%d", (int) insertSort->GetSortTime() );
	pDC->TextOutW( 10, 60, str1 );

	CString str2;
	str2.Format( L"%d", (int) selectSort->GetSortTime() );
	pDC->TextOutW( 10, 90, str2 );

	CString str3;
	str3.Format( L"%d", (int) quickSort->GetSortTime() );
	pDC->TextOutW( 10, 120, str3 );

	CString str4;
	str4.Format( L"%d", (int) bubbleSort->GetSortTime() );
	pDC->TextOutW( 10, 150, str4 );

	CString str5;
	str5.Format( L"%d", (int) heapSort->GetSortTime() );
	pDC->TextOutW( 10, 180, str5 );


	//simpleSortTime = sort->SimpleSorts();
	//quickSortTime = sort->QuickSorts();
	////CStrint a = simpleSortTime->halfSortTime;
	//CString str;
	//str.Format( L"%d", (int)simpleSortTime->halfSortTime );
	//pDC->TextOutW( 10, 30, str );
	//
	//str.Format( L"%d", (int) simpleSortTime->selectSortTime );
	//pDC->TextOutW( 10, 60, str );

	//str.Format( L"%d", (int) simpleSortTime->insertSortTime );
	//pDC->TextOutW( 10, 90, str );

	//str.Format( L"%d", (int) quickSortTime->bubbleSortTime );
	//pDC->TextOutW( 10, 120, str );

	//str.Format( L"%d", (int) quickSortTime->heapSortTime );
	//pDC->TextOutW( 10, 150, str );

	//str.Format( L"%d", (int) quickSortTime->quickSortTime );
	//pDC->TextOutW( 10, 180, str );

	//pDC->TextOutW(20,20,)

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


void CSortView::OnSimpleSort()
{
	//simpleSortTime = sort->SimpleSorts();
	
}


void CSortView::OnQuickSort()
{
	//quickSortTime = sort->QuickSorts();
}


void CSortView::OnAllSort()
{
	//simpleSortTime = sort->SimpleSorts();
	//quickSortTime = sort->QuickSorts();
}
