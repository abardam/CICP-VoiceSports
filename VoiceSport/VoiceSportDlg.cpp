
// VoiceSportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VoiceSport.h"
#include "VoiceSportDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CVoiceSportDlg dialog



CVoiceSportDlg::CVoiceSportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VOICESPORT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVoiceSportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, btnStartASR);
	DDX_Control(pDX, IDC_BUTTON2, btnStopASR);
	DDX_Control(pDX, IDC_EDIT1, ebAsrResult);

	btnStartASR.SetWindowTextW(L"Start ASR");
	btnStopASR.SetWindowTextW(L"Stop ASR");
	btnStopASR.EnableWindow(false);
	// Demo ASR
	speechkit.setCtx(AfxGetMainWnd());
	speechkit.connectOnFinalResult(makeFunctor((CBFunctor2<std::string, CWnd* > *)0, onFinalResult));
	speechkit.connectOnError(makeFunctor((CBFunctor2<int, CWnd* > *)0, onError));
	// End Demo
}

BEGIN_MESSAGE_MAP(CVoiceSportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CVoiceSportDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CVoiceSportDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CVoiceSportDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CVoiceSportDlg message handlers

BOOL CVoiceSportDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVoiceSportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVoiceSportDlg::OnPaint()
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
HCURSOR CVoiceSportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVoiceSportDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	runASR();
}


void CVoiceSportDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	stopASR();
}


void CVoiceSportDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CVoiceSportDlg::runASR()
{
	if (!speechkit.startASR()) {
		MessageBox(_T("ASR service is not available."), _T("Error"),
			MB_ICONERROR | MB_OK);
	}
	else {
		btnStopASR.EnableWindow(true);
		btnStartASR.EnableWindow(false);
	}
	
}
void CVoiceSportDlg::stopASR()
{
	speechkit.stopASR();
	btnStartASR.EnableWindow(true);
	btnStopASR.EnableWindow(false);
}


std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void onFinalResult(std::string text, CWnd* ctx)
{
	CVoiceSportDlg *dialogctx = (CVoiceSportDlg *)ctx;
	std::wstring stemp = s2ws(text);
	//CMFCApplication2Dlg *pMainDlg = (CMFCApplication2Dlg *)AfxGetMainWnd();
	//EbASR2 = stemp.c_str();
	dialogctx->ebAsrResult.SetWindowTextW(stemp.c_str());
	tts(stemp.c_str());
	//EbASR2(_T(stemp.c_str()));
}

void onError(int, CWnd* ctx)
{
}