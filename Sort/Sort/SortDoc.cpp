
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
	sorts.push_back( new SelectSort( tab ) );
	sorts.push_back( new InsertSort( tab ) );
	sorts.push_back( new HalfSort( tab ) );
	
	sorts.push_back( new HeapSort( tab ) );
	sorts.push_back( new QuickSort( tab ) );

	this->status = 3;

	maxSimpleSortTime = 0;
	maxQuickSortTime = 0;

	countMaxSortTime();
	fillTimeVector();

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

	
	//fillTimeVector( maxQuickSortTime, quickSortsTimes );

	return TRUE;
}



int CSortDoc::getSortStatus()
{
	return this->status;
}

std::vector<unsigned int> CSortDoc::getTimeVector()
{
	if( status == 3 || status == 1 )
		return simpleSortsTimes;
	else if( status == 2 )
		return quickSortsTimes;
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
	unsigned int sortTime = 0;
	for( Sorter* sort : sorts )
	{
		sortTime = roundMaxSortTime( sort->GetSortTime() );

		if( sort->GetType() == 1 )
		{
			if( this->maxSimpleSortTime < sortTime )
				this->maxSimpleSortTime = sortTime;
		}
		else {
			if( this->maxQuickSortTime < sortTime )
				this->maxQuickSortTime = sortTime;
		}
	}
}

unsigned int CSortDoc::roundMaxSortTime(unsigned int sortTime)
{
	int r;
	int plus = 60;
	if( sortTime % 20 == 0 )
		return sortTime + plus;
	else{
		r = sortTime - (int)(sortTime / 20) * 20;
		sortTime = sortTime + ( plus - r );
		return sortTime;
	}

}

void CSortDoc::fillTimeVector()
{
	unsigned int temp, temp1;
	for( int i = 0; i < SIZE_LINES; ++i )
	{
		temp = this->maxSimpleSortTime - ( this->maxSimpleSortTime / 20 ) * i;
		this->simpleSortsTimes.push_back( temp );

		temp1 = this->maxQuickSortTime - ( this->maxQuickSortTime / 20 ) *i;
		this->quickSortsTimes.push_back( temp1 );
	}
	simpleSortsTimes.push_back( 0 );
	quickSortsTimes.push_back( 0 );
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
