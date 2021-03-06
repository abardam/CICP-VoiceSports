
// TestUIDlg.h : header file
//

#pragma once

#include "../KinectRead/Kinect2Manager.h"
#include <vector>
#include "OpenGLControl.h"

#include "../CICP-ActionTemplates/UtilsHAR.h"
#include "../CICP-ActionTemplates/PoseMatcher.h"

#include "../SpeechAPI/tts.h"
#include "../SpeechAPI/asr.h"

#include "../wit_nlu/wit_lib.h"
#include "../wit_nlu/dict.h"

struct Sport {
	std::string name;
	std::vector<std::string> actions;
};

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

	// Variables for the speech API
	voicesport::SpeechKit speechkit;
	void onFinalResult(std::string text);


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
	void ClickBodyPartCheckBox();
	void UpdateAdviceSkeleton();
	void InitKinect();

private:
	//CStatic * m_maindisplay;
	COpenGLControl m_oglWindow;
	std::vector<CButton *> m_bodypartCheckBoxes;

	CComboBox * m_sport_cb;
	CComboBox * m_action_cb;
	CButton * m_start_recording;
	int m_width, m_height;
	bool m_bSpeechIsActive;

	std::vector<Sport> m_sports;
	int m_current_sport;
	bool m_bAdviceFront;

	Kinect2Manager m_kinectManager;
	PoseMatcher m_poseMatcher;

	// Variables for the NLU module
	dict *m_dict;
	WitLib *m_witlib;


	// corresponding kinect joint for each "Antonio joint"
	//UPDATE: moved to UtilsHAR.cpp
	//int m_kinectJointMap[NUM_JOINTS];

public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnBnClickedCheck11();
	afx_msg void OnBnClickedCheck12();
	afx_msg void OnBnClickedCheck13();
	afx_msg void OnBnClickedCheck14();
	afx_msg void OnBnClickedCheck15();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonSpeech();
	afx_msg void OnBnClickedButton3();
};
