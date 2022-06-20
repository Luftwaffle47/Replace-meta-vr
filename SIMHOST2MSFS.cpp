
// SIMHOST2MSFS.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "windows.h"
#include "afxres.h"
#include "minwindef.h"
#include "iostream"
#include "windows.h"
#include "framework.h"
#include "SimConnect.h"
#include "SIMHOST2MSFS.h"
#include "SIMHOST2MSFSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSIMHOST2MSFSApp
int quit = 0; //0= keep running, 1 = Exit App

HANDLE hSimConnect = NULL;




//Event Callback
void CALLBACK MyDispatchProc1(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
	switch (pData->dwID)
	{
		//Case Simulation data recieve event
	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
	{
		SIMCONNECT_RECV_SIMOBJECT_DATA* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

		//Switch to find the right request 
		switch (pObjData->dwRequestID)
		{
		case REQUEST_1:
			//Cast the request data to a SimResponse 
			SimResponse* pS = (SimResponse*)&pObjData->dwData;
			
			//prints data to the console
			std::cout
				<< "\rAltitude:" << pS->altitude
				<< "- heading:" << pS->heading
				<< "- Speed(Knots): " << pS->speed
				<< "- Vertical Speed: " << pS->vertical_speed

				<< std::flush;
				
			break;
		}
		break;
	}
	//Case Simulation quit event
	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = 1;//The application will quit if the simulator is closed
		break;
	}
	// Other events 
	default:
		break;
	}
}
bool initSimEvents() {

	HRESULT hr;


	//If the app successfully connects to SimConnect, the following events will occur
	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "Client Event Demo", NULL, 0, NULL, 0))) {


		//Requesting our data

		//The data request order must follow the declaration order of the response struct
		//SimConnect_AddToDataDefinition takes: HANDLE, enum DEFINITION_ID, const char* DATA_NAME, const char* UNIT, DATATYPE( DEFAULT IS FLOAT64)
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "INDICATED ALTITUDE", "meters");


		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "HEADING INDICATOR", "degrees", SIMCONNECT_DATATYPE_INT32);


		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Airspeed Indicated", "knots", SIMCONNECT_DATATYPE_INT32);


		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "VERTICAL SPEED", "Meters per Second", SIMCONNECT_DATATYPE_INT32);


		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "PLANE LONGITUDE", "meters", SIMCONNECT_DATATYPE_FLOAT32);


		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "PLANE LATITUDE", "meters", SIMCONNECT_DATATYPE_FLOAT32);




		//Every second request data for definition 1 on the current user aircraft(SIMCONNECT_OBJECT_ID_USER)
		hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);

		//Process incoming SimConnect Server messages while this application is running
		while (quit == 0) {
			// Call SimConnect_CallDispatch Every second until quit- MyDispatchProc1 will handle simulation events
			SimConnect_CallDispatch(hSimConnect, MyDispatchProc1, NULL);
			Sleep(1);
		}
		//When we finish running we can close SimConnect handle
		hr = SimConnect_Close(hSimConnect);
		return true;
	}
	else {//if the connection fails, this message will be displayed

		return false;
	}
}







BEGIN_MESSAGE_MAP(CSIMHOST2MSFSApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSIMHOST2MSFSApp construction

CSIMHOST2MSFSApp::CSIMHOST2MSFSApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSIMHOST2MSFSApp object

CSIMHOST2MSFSApp theApp;


// CSIMHOST2MSFSApp initialization

BOOL CSIMHOST2MSFSApp::InitInstance()
{
	

	
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	
	
	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	CSIMHOST2MSFSDlg dlg;
	
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	initSimEvents();
	
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

	
#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
void CSIMHOST2MSFSDlg::OnTimer(UINT nIDEvent)
{
	


}


