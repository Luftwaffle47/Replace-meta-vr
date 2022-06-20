
// SIMHOST2MSFS.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSIMHOST2MSFSApp:
// See SIMHOST2MSFS.cpp for the implementation of this class
//

static enum DATA_DEFINE_ID {
	DEFINITION_1,
};

static enum DATA_REQUEST_ID {
	REQUEST_1,
	REQUEST_2,
};

class CSIMHOST2MSFSApp : public CWinApp
{
public:
	CSIMHOST2MSFSApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSIMHOST2MSFSApp theApp;
