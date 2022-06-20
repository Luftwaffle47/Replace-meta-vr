
// SIMHOST2MSFSDlg.cpp : implementation file
//

#include "pch.h"
#include <afxwin.h>
#include <afxcmn.h>
#include <afxdlgs.h>
#include <afxtempl.h>
#include <afxmt.h>
#include "framework.h"
#include "SIMHOST2MSFS.h"
#include "SIMHOST2MSFSDlg.h"
#include "SimConnect.h"
#include "afxdialogex.h"
#include "string"
#include "windows.h"
#include "iostream"




// CAboutDlg dialog used for App About
static CMutex     mutex;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSIMHOST2MSFSDlg dialog



CSIMHOST2MSFSDlg::CSIMHOST2MSFSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIMHOST2MSFS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CSIMHOST2MSFSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSIMHOST2MSFSDlg, CDialogEx)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//N_EN_CHANGE(IDC_VERTICALSPEED, &CSIMHOST2MSFSDlg::OnEnChangeVerticalSpeed)
//N_EN_CHANGE(IDC_HEADING, &CSIMHOST2MSFSDlg::OnEnChangeHeading)
//N_EN_CHANGE(IDC_AIRSPEED, &CSIMHOST2MSFSDlg::OnEnChangeAirspeed)
//N_EN_CHANGE(IDC_LONGITUDE, &CSIMHOST2MSFSDlg::OnEnChangeLongitude)
//N_EN_CHANGE(IDC_LATITUDE, &CSIMHOST2MSFSDlg::OnEnChangeLatitude)
//N_EN_CHANGE(IDC_ALTITUDE, &CSIMHOST2MSFSDlg::OnEnChangeAltitude)
END_MESSAGE_MAP()


// CSIMHOST2MSFSDlg message handlers

BOOL CSIMHOST2MSFSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	


	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSIMHOST2MSFSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSIMHOST2MSFSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSIMHOST2MSFSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






