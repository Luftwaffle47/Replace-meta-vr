
// SIMHOST2MSFSDlg.h : header file
//

#pragma once
struct SimResponse {
	 double altitude;
	 int32_t heading;
	 int32_t speed;
	 int32_t vertical_speed;
	 float_t plane_longitude;
	 float_t plane_latitude;
};

// CSIMHOST2MSFSDlg dialog
class CSIMHOST2MSFSDlg : public CDialogEx
{
// Construction
public:
	CSIMHOST2MSFSDlg(CWnd* pParent = nullptr);
	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIMHOST2MSFS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
//public:
// TODO utilize some of these for sending packets to the MSFS IG
	//afx_msg void OnEnChangeVerticalSpeed();
//afx_msg void OnEnChangeHeading();
//afx_msg void OnEnChangeAirspeed();
//afx_msg void OnEnChangeLongitude();
//afx_msg void OnEnChangeLatitude();
//afx_msg void OnEnChangeAltitude();
//
};
