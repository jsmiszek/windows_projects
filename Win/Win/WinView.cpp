
// WinView.cpp : implementation of the CWinView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Win.h"
#endif

#include "WinDoc.h"
#include "WinView.h"
#include "ColorRect.h"
#include "Coordinates.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#define RIGHT_SHIFT 30
#define RECT_WIDTH 50 
#define START 100
#define START_COORD 50
#define ENDY 500

#define SIZE_LINES 20

// CWinView

IMPLEMENT_DYNCREATE(CWinView, CView)

BEGIN_MESSAGE_MAP(CWinView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWinView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CWinView construction/destruction

CWinView::CWinView()
{
	// TODO: add construction code here

	this->m_pClientRect = new CRect;
}

CWinView::~CWinView()
{
	delete m_pClientRect;
}

BOOL CWinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CWinView drawing

void CWinView::OnDraw(CDC* pDC)
{
	CWinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	GetClientRect( m_pClientRect );

	//CRect* rect;

	std::pair<int, int> leftTopPoint( START_COORD, START_COORD );
	////std::pair<int, int> leftTopPoint( START_COORD, m_pClientRect->bottom );

	std::pair<int, int> rightBottomPoint( ENDX, 0.9 * m_pClientRect->Height() );
	////std::pair<int, int> rightBottomPoint( ENDX, 0.9 * m_pClientRect->bottom );
	//CCoordinates coord( leftTopPoint, rightBottomPoint );

	///////////////////////////////////////////

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines;

	for( int i = 0; i < SIZE_LINES - 1; i++ )
	{

		std::pair<std::pair<int, int>, std::pair<int, int>> s;
		s.first.first = START_COORD;
		s.first.second = m_pClientRect->bottom * i / SIZE_LINES;
		
		s.second.first = ENDX; //0.8 * m_pClientRect->right;
		s.second.second = i * m_pClientRect->bottom / SIZE_LINES;

		if( s.second.first < 200 )
		{
			s.second.first = 200;
		}

		if( s.first.second < START_COORD )
		{
			s.first.second = START_COORD;
			s.second.second = START_COORD;;
		}

		lines.push_back( s );
	}

	CCoordinates* coord = new CCoordinates( leftTopPoint, rightBottomPoint, lines );

	coord->drawCoordinates( pDC );

	////////////////////////////////////////////

	for( int i = 0; i < 6; ++i )
	{
		CRect rect( START + i*( RECT_WIDTH + RIGHT_SHIFT ), START,
			START + i*( RECT_WIDTH + RIGHT_SHIFT ) + RECT_WIDTH, 0.9 * m_pClientRect->Height() );
		CColorRect* rectan = new CColorRect( &rect, 10, RED, colors[i] );

		rectan->PaintRect( pDC, rect );
	}


	//rect.PaintRect( pDC );

	//rect.setAttr( 10, RGB(255,0,0), RGB(0, 255,0) );
	//rectan->PaintRect( pDC, rect1 );

}


// CWinView printing


void CWinView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWinView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWinView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWinView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CWinView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWinView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWinView diagnostics

#ifdef _DEBUG
void CWinView::AssertValid() const
{
	CView::AssertValid();
}

void CWinView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinDoc* CWinView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinDoc)));
	return (CWinDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinView message handlers
