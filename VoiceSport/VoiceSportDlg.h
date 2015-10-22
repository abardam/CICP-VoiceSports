
// VoiceSportDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "asr.h"
#include "callback.h"
#include "tts.h"

void onFinalResult(std::string text, CWnd* ctx);
void onError(int, CWnd* ctx);
// CVoiceSportDlg dialog
class CVoiceSportDlg : public CDialogEx
{
// Construction
public:
	CVoiceSportDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VOICESPORT_DIALOG };
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
	// Start ASR
	CButton btnStartASR;
	// Stop ASR
	CButton btnStopASR;
	// Edit box that store ASR result
	CEdit ebAsrResult;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	void runASR();
	void stopASR();
private:
	// Demo ASR
	voicesport::SpeechKit speechkit;
	// End Demo
};
