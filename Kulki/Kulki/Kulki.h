
// Kulki.h : main header file for the Kulki application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKulkiApp:
// See Kulki.cpp for the implementation of this class
//

class CKulkiApp : public CWinApp
{
public:
	CKulkiApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKulkiApp theApp;
