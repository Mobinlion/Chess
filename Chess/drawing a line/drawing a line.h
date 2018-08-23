
// drawing a line.h : main header file for the drawing a line application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CdrawingalineApp:
// See drawing a line.cpp for the implementation of this class
//

class CdrawingalineApp : public CWinApp
{
public:
	CdrawingalineApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CdrawingalineApp theApp;
