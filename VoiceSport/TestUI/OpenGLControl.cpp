#include "stdafx.h"
#include "OpenGLControl.h"


COpenGLControl::COpenGLControl()
{
	m_fPosX = 0.f;
	m_fPosY = 0.f;
	m_fZoom = 10.f;
	m_fRotX = 0.f;
	m_fRotY = 0.f;
	m_fLastX = 0.f;
	m_fLastY = 0.f;
}


COpenGLControl::~COpenGLControl()
{
}

void COpenGLControl::oglCreate(CRect rect, CWnd * parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);
	CreateEx(0, className, L"OpenGL", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	m_oldWindow = rect;
	m_originalRect = rect;

	hWnd = parent;
}

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void COpenGLControl::oglInitialize()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16,
		0, 0, 0, 0, 0, 0, 0
	};

	hdc = GetDC()->m_hDC;

	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClearDepth(1.f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	OnDraw(NULL);
}

void COpenGLControl::oglDrawScene()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUADS);
	// Top Side
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	// Bottom Side
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Front Side
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back Side
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Left Side
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// Right Side
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glEnd();

}

void COpenGLControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
}


int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	oglInitialize();
	return 0;
}

void COpenGLControl::OnDraw(CDC * pDC)
{
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.f);
	glRotatef(m_fRotX, 1.f, 0.f, 0.f);
	glRotatef(m_fRotY, 0.f, 1.f, 0.f);
}


void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent) {
	case 1:
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		oglDrawScene();

		SwapBuffers(hdc);

		break;
	}

	default:
		break;
	}

	CWnd::OnTimer(nIDEvent);
}


void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
}


void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX = (float)point.x;
	m_fLastY = (float)point.y;

	if (nFlags & MK_LBUTTON) {
		m_fRotX += (float)0.5f * diffY;
		if ((m_fRotX > 360.f) || (m_fRotX < -360.f)) {
			m_fRotX = 0.f;
		}

		m_fRotY += (float)0.5f * diffX;
		if ((m_fRotY > 360.f) || (m_fRotY < -360.f)) {
			m_fRotY = 0.f;
		}
	}
	else if (nFlags & MK_RBUTTON) {
		m_fZoom -= (float)0.1f * diffY;
	}
	else if (nFlags & MK_MBUTTON) {
		m_fPosX += (float)0.05f * diffX;
		m_fPosY -= (float)0.05f * diffY;
	}

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
}
