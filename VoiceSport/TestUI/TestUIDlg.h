
// TestUIDlg.h : header file
//

#pragma once

#include "../../KinectRead/Kinect2Manager.h"


// CTestUIDlg dialog
class CTestUIDlg : public CDialogEx
{
// Construction
public:
	CTestUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTUI_DIALOG };
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
	DECLARE_MESSAGE_MAP()

public:
	void ShowKinect();
	void InitKinect();

private:
	CStatic * m_maindisplay;
	int m_width, m_height;

	Kinect2Manager m_kinectManager;

public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

};
