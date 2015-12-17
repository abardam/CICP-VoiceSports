
// TestKinectRead-MFCDlg.h : header file
//

#pragma once


// CTestKinectReadMFCDlg dialog
class CTestKinectReadMFCDlg : public CDialog
{
// Construction
public:
	CTestKinectReadMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTKINECTREADMFC_DIALOG };
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
	//KINECT: function to update/show kinect
	void ShowKinect();

private:
	CStatic * m_picture;
	int m_width, m_height;
};
