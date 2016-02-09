
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

// KINECT: include KinectRead project
#include "..\..\KinectRead\Kinect2Manager.h"

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
	m_maindisplay = (CStatic*)GetDlgItem(IDC_MAINDISPLAY); // this is the ID that we set in the dialog view
	m_sport_cb = (CComboBox*)GetDlgItem(IDC_COMBO1);
	m_action_cb = (CComboBox*)GetDlgItem(IDC_COMBO2);
														  // KINECT: begin the thread
	AfxBeginThread(KinectRefreshProc, this);

	// init sports
	Sport kendo_sp;
	kendo_sp.name = "Kendo";
	kendo_sp.actions.push_back("Kamae");

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

void CTestUIDlg::ShowKinect()
{
	m_kinectManager.Update(Update::Color | Update::Depth);

	RGBQUAD * rgbx = m_kinectManager.GetColorRGBX();

	m_width = m_kinectManager.getColorWidth();
	m_height = m_kinectManager.getColorHeight();

	//HBITMAP hBmp = rgbquad_to_hbitmap(rgbx, m_width, m_height);

	int width = 400, height = 300;

	std::vector<RGBQUAD> rgbx_resized(width * height);

	resize_rgbquad(rgbx, m_width, m_height, rgbx_resized.data(), width, height);

	m_width = width;
	m_height = height;

	HBITMAP hBmp = rgbquad_to_hbitmap(rgbx_resized.data(), m_width, m_height);


	//HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"Chrysanthemum.bmp", IMAGE_BITMAP, 1024, 768, LR_LOADFROMFILE);

	if (hBmp) {
		HBITMAP hBmp_old = m_maindisplay->SetBitmap(hBmp);

		if (hBmp_old) {
			DeleteObject(hBmp_old);
			//RedrawWindow();
		}
		else {
			printf("WTF?\n");
		}
		//SetWindowPos(NULL, 0, 0, m_width, m_height, SWP_NOMOVE | SWP_NOZORDER);
	}
	else {
		printf("WTF?\n");
	}

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
