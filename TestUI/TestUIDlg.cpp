
// TestUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestUI.h"
#include "TestUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "rgbquad_util.h"
#include "antonio_skeleton_util.h"

// KINECT: include KinectRead project
#include "..\KinectRead\Kinect2Manager.h"

// KINECT: declaration for thread loop function
UINT KinectRefreshProc(LPVOID pParam);

// CAboutDlg dialog used for App About

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


// CTestUIDlg dialog



CTestUIDlg::CTestUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_ERASEBKGND()
ON_CBN_SELCHANGE(IDC_COMBO1, &CTestUIDlg::OnCbnSelchangeCombo1)
ON_BN_CLICKED(IDC_CHECK1, &CTestUIDlg::OnBnClickedCheck1)
ON_BN_CLICKED(IDC_CHECK2, &CTestUIDlg::OnBnClickedCheck2)
ON_BN_CLICKED(IDC_CHECK3, &CTestUIDlg::OnBnClickedCheck3)
ON_BN_CLICKED(IDC_CHECK4, &CTestUIDlg::OnBnClickedCheck4)
ON_BN_CLICKED(IDC_CHECK5, &CTestUIDlg::OnBnClickedCheck5)
ON_BN_CLICKED(IDC_CHECK6, &CTestUIDlg::OnBnClickedCheck6)
ON_BN_CLICKED(IDC_CHECK7, &CTestUIDlg::OnBnClickedCheck7)
ON_BN_CLICKED(IDC_CHECK8, &CTestUIDlg::OnBnClickedCheck8)
ON_BN_CLICKED(IDC_CHECK9, &CTestUIDlg::OnBnClickedCheck9)
ON_BN_CLICKED(IDC_CHECK10, &CTestUIDlg::OnBnClickedCheck10)
ON_BN_CLICKED(IDC_CHECK11, &CTestUIDlg::OnBnClickedCheck11)
ON_BN_CLICKED(IDC_CHECK12, &CTestUIDlg::OnBnClickedCheck12)
ON_BN_CLICKED(IDC_CHECK13, &CTestUIDlg::OnBnClickedCheck13)
ON_BN_CLICKED(IDC_CHECK14, &CTestUIDlg::OnBnClickedCheck14)
ON_BN_CLICKED(IDC_CHECK15, &CTestUIDlg::OnBnClickedCheck15)
ON_CBN_SELCHANGE(IDC_COMBO2, &CTestUIDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CTestUIDlg message handlers

BOOL CTestUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// KINECT: set picture control variable so we can change the picture
	//m_maindisplay = (CStatic*)GetDlgItem(IDC_MAINDISPLAY); // this is the ID that we set in the dialog view
	m_sport_cb = (CComboBox*)GetDlgItem(IDC_COMBO1);
	m_action_cb = (CComboBox*)GetDlgItem(IDC_COMBO2);

	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK1));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK2));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK3));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK4));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK5));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK6));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK7));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK8));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK9));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK10));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK11));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK12));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK13));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK14));
	m_bodypartCheckBoxes.push_back((CButton *)GetDlgItem(IDC_CHECK15));

	//populate kinect joint map
	//UPDATE: moved to UtilsHAR.cpp
	/*m_kinectJointMap[HEAD] = JointType_Head;
	m_kinectJointMap[NECK] = JointType_Neck;
	m_kinectJointMap[LSHOULDER] = JointType_ShoulderLeft;
	m_kinectJointMap[LELBOW] = JointType_ElbowLeft;
	m_kinectJointMap[LHAND] = JointType_HandLeft;
	m_kinectJointMap[RSHOULDER] = JointType_ShoulderRight;
	m_kinectJointMap[RELBOW] = JointType_ElbowRight;
	m_kinectJointMap[RHAND] = JointType_HandRight;
	m_kinectJointMap[TORSO] = JointType_SpineMid;
	m_kinectJointMap[LHIP] = JointType_HipLeft;
	m_kinectJointMap[LKNEE] = JointType_KneeLeft;
	m_kinectJointMap[LFOOT] = JointType_FootLeft;
	m_kinectJointMap[RHIP] = JointType_HipRight;
	m_kinectJointMap[RKNEE] = JointType_KneeRight;
	m_kinectJointMap[RFOOT] = JointType_FootRight;*/

	//new style with OpenGL
	CRect rect;
	GetDlgItem(IDC_MAINDISPLAY)->GetWindowRect(rect);
	ScreenToClient(rect);
	m_oglWindow.oglCreate(rect, this);
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 33, 0);


	std::vector<RGBQUAD> img(256 * 256);
	for (int i = 0; i < 256 * 256; ++i) {
		img[i].rgbBlue = 0xff;
		img[i].rgbGreen = 0;
		img[i].rgbRed = 0;
		img[i].rgbReserved = 0xff;
	}

	m_oglWindow.oglSetTexture(img.data(), 256, 256);

	// KINECT: begin the thread
	//AfxBeginThread(KinectRefreshProc, this); // note: multithreading does not play well with ogl
	m_oglWindow.oglSetKinect(&m_kinectManager);

	// init sports
	Sport kendo_sp;
	kendo_sp.name = "Kendo";
	kendo_sp.actions.push_back("Jodan");
	kendo_sp.actions.push_back("Kamae");
	kendo_sp.actions.push_back("Sonkyo");
	kendo_sp.actions.push_back("Suburi");
	kendo_sp.actions.push_back("Tsubazeriai");

	Sport tennis_sp;
	tennis_sp.name = "Tennis";
	tennis_sp.actions.push_back("Forehand");

	m_sports.push_back(kendo_sp);
	m_sports.push_back(tennis_sp);

	m_sport_cb->ResetContent();
	for (Sport s : m_sports) {
		std::wstring s2;
		s2.assign(s.name.begin(), s.name.end());
		m_sport_cb->AddString(s2.c_str());
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestUIDlg::OnPaint()
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
HCURSOR CTestUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// KINECT: this function is what is executed by the thread.
UINT KinectRefreshProc(LPVOID pParam) {

	CTestUIDlg * pObject = (CTestUIDlg*)pParam;

	if (pObject == NULL)
		return 1;   // if pObject is not valid

					//thread loop

	pObject->InitKinect();
	while (true) {
		pObject->ShowKinect();
		Sleep(10);
	}

	return 0;
}

void CTestUIDlg::InitKinect() {
	m_kinectManager.InitializeDefaultSensor();
}

// KINECT: this is what is called repeatedly in the thread in order to update the picture box
// UPDATE: do not use this function. all updates will be handled within the opengl control itself.

void CTestUIDlg::ShowKinect()
{
	m_kinectManager.Update(Update::Color | Update::Depth | Update::Body | Update::BodyIndex);

	RGBQUAD * rgbx = m_kinectManager.GetColorRGBX();
/*
	m_width = m_kinectManager.getColorWidth();
	m_height = m_kinectManager.getColorHeight();

	m_oglWindow.oglSetTexture(rgbx, m_width, m_height);*/

	std::vector<RGBQUAD> img(256 * 256);
	for (int i = 0; i < 256 * 256; ++i) {
		img[i].rgbBlue = 0xff;
		img[i].rgbGreen = 0;
		img[i].rgbRed = 0;
		img[i].rgbReserved = 0xff;
	}

	m_oglWindow.oglSetTexture(img.data(), 256, 256);

	////HBITMAP hBmp = rgbquad_to_hbitmap(rgbx, m_width, m_height);

	//int width = 960, height = 540;

	//std::vector<RGBQUAD> rgbx_resized(width * height);

	//resize_rgbquad(rgbx, m_width, m_height, rgbx_resized.data(), width, height);

	////RGBQUAD col;
	////col.rgbRed = 200;
	////col.rgbGreen = 10;
	////col.rgbBlue = 10;
	////draw_circle(rgbx_resized.data(), width, height, 10, 10, 5, col);

	////show skeleton (need coordinate mapper)
	//ICoordinateMapper * cm = m_kinectManager.getCoordinateMapper();
	//if (cm) {
	//	if (m_kinectManager.getSkeletonIsGood()) {
	//		Joint * jptr = m_kinectManager.GetJoints();

	//		std::vector<CameraSpacePoint> jcam(JointType_Count);
	//		for (int j = 0; j < JointType_Count; ++j)
	//		{
	//			jcam[j] = jptr[j].Position;
	//		}
	//		std::vector<ColorSpacePoint> jcol(JointType_Count);

	//		cm->MapCameraPointsToColorSpace(JointType_Count, jcam.data(), JointType_Count, jcol.data());

	//		RGBQUAD col;
	//		col.rgbRed = 200;
	//		col.rgbGreen = 10;
	//		col.rgbBlue = 10;
	//		float x_ratio = (width + 0.0) / m_width;
	//		float y_ratio = (height + 0.0) / m_height;
	//		for (int j = 0; j < JointType_Count; ++j) {
	//			int x = jcol[j].X * x_ratio;
	//			int y = jcol[j].Y * y_ratio;
	//			draw_circle(rgbx_resized.data(), width, height, x, y, 5, col);
	//		}
	//	}
	//}


	//m_width = width;
	//m_height = height;

	//HBITMAP hBmp = rgbquad_to_hbitmap(rgbx_resized.data(), m_width, m_height);


	////HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"Chrysanthemum.bmp", IMAGE_BITMAP, 1024, 768, LR_LOADFROMFILE);

	//if (hBmp) {
	//	//HBITMAP hBmp_old = m_maindisplay->SetBitmap(hBmp);
	//	//m_maindisplay->SetWindowPos(NULL, 0, 0, m_width, m_height, SWP_NOMOVE | SWP_NOZORDER);
	//	//
	//	//if (hBmp_old) {
	//	//	DeleteObject(hBmp_old);
	//	//	//RedrawWindow();
	//	//}
	//	//else {
	//	//	printf("WTF?\n");
	//	//}
	//	//SetWindowPos(NULL, 0, 0, m_width, m_height, SWP_NOMOVE | SWP_NOZORDER);
	//}
	//else {
	//	printf("WTF?\n");
	//}

}

void CTestUIDlg::ClickBodyPartCheckBox() {
	UpdateAdviceSkeleton();
}

void CTestUIDlg::UpdateAdviceSkeleton() {
	posskeleton inskel;
	if (m_kinectManager.getSkeletonIsGood()) {
		Joint * jptr = m_kinectManager.GetJoints();
		int * kinectJointMap = getKinectJointMap();

		for (int j = 0; j < NUM_JOINTS; ++j)
		{
			inskel.positions[j].rightleft = jptr[kinectJointMap[j]].Position.X;
			inskel.positions[j].updown = jptr[kinectJointMap[j]].Position.Y;
			inskel.positions[j].fwdbwd = jptr[kinectJointMap[j]].Position.Z;
			inskel.confidences[j] = jptr[kinectJointMap[j]].TrackingState;
		}

	}
	else {
		//shitty test data
		for (int j = 0; j < NUM_JOINTS; ++j) {
			inskel.positions[j].rightleft = 0;
			inskel.positions[j].updown = 0;
			inskel.positions[j].fwdbwd = 0;
			inskel.confidences[j] = 1;
		}
	}

	fbskeleton fbjoints;
	for (int i = 0; i < NUM_JOINTS; ++i) {
		fbjoints.needsCheck[i] = m_bodypartCheckBoxes[i]->GetCheck();
	}

	int action;
	action = m_action_cb->GetCurSel();

	if (action < 0) {
		return;
	}

	posskeleton feedback;
	posskeleton fitpose;
	m_poseMatcher.weightedPoseMatching(inskel, fbjoints, action, &feedback, &fitpose);

	m_oglWindow.oglSetAdviceSkeleton(fitpose);
}


//BOOL CTestUIDlg::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
//
//	return CDialogEx::OnEraseBkgnd(pDC);
//}


void CTestUIDlg::OnCbnSelchangeCombo1()
{
	m_current_sport = m_sport_cb->GetCurSel();

	m_action_cb->ResetContent();
	for (std::string s : m_sports[m_current_sport].actions) {
		std::wstring s2;
		s2.assign(s.begin(), s.end());
		m_action_cb->AddString(s2.c_str());

	}
}


void CTestUIDlg::OnBnClickedCheck1()
{
	ClickBodyPartCheckBox();
}


void CTestUIDlg::OnBnClickedCheck2()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck3()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck4()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck5()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck6()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck7()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck8()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck9()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck10()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck11()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck12()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck13()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck14()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnBnClickedCheck15()
{
	ClickBodyPartCheckBox();

}


void CTestUIDlg::OnCbnSelchangeCombo2()
{
	UpdateAdviceSkeleton();
}
