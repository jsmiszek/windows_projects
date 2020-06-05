
// KulkiView.cpp : implementation of the CKulkiView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kulki.h"
#endif

#include "KulkiDoc.h"
#include "KulkiView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BALLSIZE 60


// CKulkiView

IMPLEMENT_DYNCREATE(CKulkiView, CView)

BEGIN_MESSAGE_MAP(CKulkiView, CView)
	ON_COMMAND( ID_START, &CKulkiView::OnStartStop )
	ON_COMMAND( ID_DODAJ, &CKulkiView::OnAddBall )
	ON_COMMAND( ID_USUN1, &CKulkiView::OnDeleteBall )
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CALLBACK ZfxTimerProc(
	HWND hWnd,		//handle of CWnd that calles SetTimer
	UINT nMsg,		//WM_TIMER
	UINT nIDEvent,	//timer identification
	DWORD dwTime	//system time
)
{
	::SendMessage( hWnd, WM_TIMER, 0, 0 );
}

// CKulkiView construction/destruction

CKulkiView::CKulkiView()
{
	// TODO: add construction code here
	m_bStartStop = FALSE;
	srand( time( NULL ) );

	m_pBall = new CRect( 20, 20, 20 + BALLSIZE, 20 + BALLSIZE );
	m_pBallPen = new CPen( PS_SOLID, 1, RGB( 0, 0, 255 ) );
	m_pBallBrush = new CBrush( RGB( 0, 0, 255 ) );


	m_pClientRect = new CRect( 0, 0, 0, 0 );

	amountBalls = 0;

	OnAddBall();
}

CKulkiView::~CKulkiView()
{
}

BOOL CKulkiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKulkiView drawing

void CKulkiView::OnDraw(CDC* pDC)
{
	CKulkiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here


	CDC memDC;
	BOOL b = memDC.CreateCompatibleDC( pDC );
	ASSERT( b );

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap( pDC, m_pClientRect->Width(), m_pClientRect->Height() );
	ASSERT( b );
	CBitmap* pOldBitmap = memDC.SelectObject( &bmp );
	memDC.FillSolidRect( m_pClientRect, RGB( 230, 230, 200 ) );

	CPen* pOldPen = memDC.SelectObject( m_pBallPen );
	CBrush* pOldBrush = memDC.SelectObject( m_pBallBrush );

	//memDC.Ellipse(m_pBall);

	for( int i = 0; i < amountBalls; i++ )
	{
		pOldPen = memDC.SelectObject( m_pBalls[ i ]->getBallPen() );
		pOldBrush = memDC.SelectObject( m_pBalls[ i ]->getBallBrush() );
		memDC.Ellipse( m_pBalls[ i ] );
	}

	//memDC.SelectObject(m_pBalls[0]);

	//memDC.Ellipse(m_pBalls[0]);
	//bounceBalls(m_pBalls[0]);

	memDC.SelectObject( pOldPen );
	memDC.SelectObject( pOldBrush );

	b = pDC->BitBlt( 0, 0, m_pClientRect->Width(), m_pClientRect->Height(), &memDC, 0, 0, SRCCOPY );
	ASSERT( b );

	memDC.SelectObject( pOldBitmap );
	bmp.DeleteObject();
	memDC.DeleteDC();

}


// CKulkiView diagnostics

#ifdef _DEBUG
void CKulkiView::AssertValid() const
{
	CView::AssertValid();
}

void CKulkiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKulkiDoc* CKulkiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKulkiDoc)));
	return (CKulkiDoc*)m_pDocument;
}
#endif //_DEBUG


// CKulkiView message handlers


void CKulkiView::OnStartStop()
{
	m_bStartStop = !m_bStartStop;
	CMainFrame* pFrame = (CMainFrame*) GetParentFrame();
	pFrame->ResetButton( m_bStartStop );
}


void CKulkiView::OnAddBall()
{
	if( amountBalls >= 0 && amountBalls < 10 )
	{
		int temp = rand() % 100;
		CBall* pBall = new CBall( 20, 20, 20 + temp, 20 + temp, RGB( rand() % 255, rand() % 255, rand() % 255 ), 1 + rand() % 10, 1 + rand() % 10 );
		//CBall pBall(20, 20, 20 + temp, 20 + temp, RGB(rand() % 255, rand() % 255, rand() % 255), 1 + rand() % 10, 1 + rand() % 10);
		m_pBalls.push_back( pBall );
		amountBalls++;

		if( amountBalls > 10 )
			amountBalls = 10;
	}
}


void CKulkiView::OnDeleteBall()
{
	if( amountBalls > 1 && amountBalls <= 10 )
	{
		CBall* pBall = m_pBalls.back();
		delete pBall;
		m_pBalls.pop_back();

		amountBalls--;

		if( amountBalls < 0 )
			amountBalls = 0;


	}
}


void CKulkiView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_nTimerID = SetTimer( WM_USER + 1, 20, ZfxTimerProc);

	// TODO: Add your specialized code here and/or call the base class
}


void CKulkiView::OnDestroy()
{
	KillTimer( m_nTimerID );
	CView::OnDestroy();

	// TODO: Add your message handler code here
}


void CKulkiView::OnTimer( UINT_PTR nIDEvent )
{
	for( int i = 0; i < amountBalls; i++ )
		m_pBalls[ i ]->OffsetRect( 0, 0 );
	Invalidate();

	if( m_bStartStop ){
		for( int i = 0; i < amountBalls; i++ ){
			if( m_pBalls[ i ]->right >= m_pClientRect->right || m_pBalls[ i ]->left < m_pClientRect->left )
				m_pBalls[ i ]->SetOffset( -1, 1 );

			if( m_pBalls[ i ]->bottom >= m_pClientRect->bottom || m_pBalls[ i ]->top < m_pClientRect->top )
				m_pBalls[ i ]->SetOffset( 1, -1 );

			m_pBalls[ i ]->OffsetRect( m_pBalls[ i ]->getOffX(), m_pBalls[ i ]->getOffY() );
		}
		Invalidate();
	}
	CView::OnTimer( nIDEvent );
}

BOOL CKulkiView::OnEraseBkgnd( CDC* pDC )
{
	return 1;
}

void CKulkiView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo )
{
	GetClientRect( m_pClientRect );
	CView::OnPrepareDC( pDC, pInfo );
}

void CKulkiView::OnSize( UINT nType, int cx, int cy )
{
	for( int i = 0; i < amountBalls; i++ ){
		m_pBalls[ i ]->SetBoundRect( m_pClientRect );
		m_pBalls[ i ]->OffsetRect( m_pBalls[ i ]->getOffX(), m_pBalls[ i ]->getOffY() );
	}
	Invalidate();

	CView::OnSize( nType, cx, cy );

	// TODO: Add your message handler code here
}
