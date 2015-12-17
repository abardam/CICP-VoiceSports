
// TestKinectRead-MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestKinectRead-MFC.h"
#include "TestKinectRead-MFCDlg.h"
#include "afxdialogex.h"

// KINECT: include KinectRead project
#include "..\KinectRead\Kinect2Manager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// KINECT: declaration for thread loop function
UINT KinectRefreshProc(LPVOID pParam);

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestKinectReadMFCDlg dialog



CTestKinectReadMFCDlg::CTestKinectReadMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TESTKINECTREADMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_width = 0;
	m_height = 0;
}

void CTestKinectReadMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestKinectReadMFCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTestKinectReadMFCDlg message handlers

BOOL CTestKinectReadMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// KINECT: set picture control variable so we can change the picture
	m_picture = (CStatic*)GetDlgItem(IDC_PICTURECONTROL); // this is the ID that we set in the dialog view

	// KINECT: begin the thread
	AfxBeginThread(KinectRefreshProc, this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestKinectReadMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestKinectReadMFCDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestKinectReadMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// KINECT: this function is what is executed by the thread.
UINT KinectRefreshProc(LPVOID pParam) {

	CTestKinectReadMFCDlg * pObject = (CTestKinectReadMFCDlg*)pParam;

	if (pObject == NULL)
		return 1;   // if pObject is not valid

	//thread loop
	while (true) {
		pObject->ShowKinect();
	}

	return 0;
}

HBITMAP get_kinect_color(int * w = 0, int * h = 0);

// KINECT: this is what is called repeatedly in the thread in order to update the picture box

void CTestKinectReadMFCDlg::ShowKinect()
{
	HBITMAP hBmp = get_kinect_color(&m_width, &m_height);

	//HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"Chrysanthemum.bmp", IMAGE_BITMAP, 1024, 768, LR_LOADFROMFILE);
	
	if (hBmp) {
		HBITMAP hBmp_old = m_picture->SetBitmap(hBmp);

		if (hBmp_old) {
			DeleteObject(hBmp_old);
		}
	}

	SetWindowPos(NULL, 0, 0, m_width, m_height, SWP_NOMOVE | SWP_NOZORDER);
}


// KINECT: function to return the Kinect input as HBITMAP.

unsigned char pixels[CAPTURE_SIZE_X_COLOR * CAPTURE_SIZE_Y_COLOR * 3];
HBITMAP get_kinect_color(int * w, int * h) {

	Kinect2Manager k2m;
	k2m.InitializeDefaultSensor();

	Sleep(10);

	k2m.Update(Update::Color | Update::Depth);

	RGBQUAD * rgbx = k2m.GetColorRGBX();

	int width = k2m.getColorWidth();
	int height = k2m.getColorHeight();

	if (w != NULL && width > 0) *w = width;
	if (h != NULL && height > 0) *h = height;

	if (width != 0 && height != 0) {

		for (int x = 0; x < width && x < CAPTURE_SIZE_X_COLOR; ++x) {
			for (int y = 0; y < height && y < CAPTURE_SIZE_Y_COLOR; ++y) {
				pixels[(y * CAPTURE_SIZE_X_COLOR + x) * 3 + 0] = (rgbx + (y * width + x))->rgbBlue;
				pixels[(y * CAPTURE_SIZE_X_COLOR + x) * 3 + 1] = (rgbx + (y * width + x))->rgbGreen;
				pixels[(y * CAPTURE_SIZE_X_COLOR + x) * 3 + 2] = (rgbx + (y * width + x))->rgbRed;
			}
		}

		BITMAPINFOHEADER bmih;
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = CAPTURE_SIZE_X_COLOR;
		bmih.biHeight = -CAPTURE_SIZE_Y_COLOR;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = 0;
		bmih.biXPelsPerMeter = 10;
		bmih.biYPelsPerMeter = 10;
		bmih.biClrUsed = 0;
		bmih.biClrImportant = 0;

		BITMAPINFO dbmi;
		ZeroMemory(&dbmi, sizeof(dbmi));
		dbmi.bmiHeader = bmih;
		dbmi.bmiColors->rgbBlue = 0;
		dbmi.bmiColors->rgbGreen = 0;
		dbmi.bmiColors->rgbRed = 0;
		dbmi.bmiColors->rgbReserved = 0;
		void* bits = (void*)&(pixels[0]);

		// Create DIB
		HBITMAP hBmp = CreateDIBSection(0, &dbmi, DIB_RGB_COLORS, &bits, NULL, 0);
		if (hBmp == NULL) {
			::MessageBox(NULL, __T("Could not load the desired image image"), __T("Error"), MB_OK);
			return 0;
		}
		// copy pixels into DIB.
		memcpy(bits, pixels, sizeof(pixels));

		return hBmp;
	}

	return 0;
}