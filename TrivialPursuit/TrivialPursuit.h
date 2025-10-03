
// TrivialPursuit.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTrivialPursuitApp:
// See TrivialPursuit.cpp for the implementation of this class
//

class CTrivialPursuitApp : public CWinApp
{
public:
	CTrivialPursuitApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTrivialPursuitApp theApp;
