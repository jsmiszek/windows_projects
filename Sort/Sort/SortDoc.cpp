
// SortDoc.cpp : implementation of the CSortDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sort.h"
#endif

#include "SortDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSortDoc

IMPLEMENT_DYNCREATE(CSortDoc, CDocument)

BEGIN_MESSAGE_MAP(CSortDoc, CDocument)
	ON_COMMAND( ID_PROSTE, &CSortDoc::OnSimpleSorts )
	ON_COMMAND( ID_SZYBKIE, &CSortDoc::OnQuickSorts )
	ON_COMMAND( ID_WSZYSTKIE, &CSortDoc::OnAllSorts )
END_MESSAGE_MAP()


// CSortDoc construction/destruction

CSortDoc::CSortDoc()
{

	tab = new int[ TAB_SIZE ];

	srand( time( NULL ) );

	for( int i = 0; i < TAB_SIZE; ++i )
		tab[ i ] = rand() % 1000;

	sorts.push_back( new BubbleSort( tab ) );
	sorts.push_back( new HalfSort( tab ) );
	sorts.push_back( new InsertSort( tab ) );
	sorts.push_back( new SelectSort( tab ) );
	sorts.push_back( new HeapSort( tab ) );
	sorts.push_back( new QuickSort( tab ) );

	this->status = 3;
}

CSortDoc::~CSortDoc()
{
	delete tab;

}

BOOL CSortDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	//UpdateAllViews( NULL );

	countMaxSortTime();

	return TRUE;
}



int CSortDoc::getSortStatus()
{
	return this->status;
}


unsigned int CSortDoc::getMaxSortTime()
{
	if( status == 1 || status == 3 )
		return maxSimpleSortTime;
	else
		return maxQuickSortTime;
}

void CSortDoc::OnSimpleSorts()
{
	status = 1;
	UpdateAllViews( NULL );
}


void CSortDoc::OnQuickSorts()
{
	status = 2;
	UpdateAllViews( NULL );
}


void CSortDoc::OnAllSorts()
{
	status = 3;
	UpdateAllViews( NULL );
}

void CSortDoc::countMaxSortTime()
{
	unsigned int sortTime;
	for( Sorter* sort : sorts )
	{
		sortTime = roundMaxSortTime( sort->GetSortTime() );

		if( sort->GetType() == 1 )
		{
			if( maxSimpleSortTime < sortTime )
				maxSimpleSortTime = sortTime;
		}
		else {
			if( maxQuickSortTime < sortTime )
				maxQuickSortTime = sortTime;
		}
	}
}

unsigned int CSortDoc::roundMaxSortTime(unsigned int sortTime)
{
	int r;
	if( sortTime % 20 == 0 )
		return sortTime + 20;
	else{
		r = sortTime - (int)(sortTime / 20) * 20;
		sortTime = sortTime + ( 20 - r );
		return sortTime;
	}

}





// CSortDoc serialization

void CSortDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSortDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSortDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSortDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}




#endif // SHARED_HANDLERS

// CSortDoc diagnostics

#ifdef _DEBUG
void CSortDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSortDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSortDoc commands
