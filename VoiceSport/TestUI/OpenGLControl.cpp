#include "stdafx.h"
#include "OpenGLControl.h"
#include "rgbquad_util.h"
#include <vector>

COpenGLControl::COpenGLControl()
{
	m_fPosX = 0.f;
	m_fPosY = 0.f;
	m_fZoom = 10.f;
	m_fRotX = 0.f;
	m_fRotY = 0.f;
	m_fLastX = 0.f;
	m_fLastY = 0.f;
	m_kinectManager = 0;
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

void COpenGLControl::oglSetTexture(RGBQUAD * img, int width, int height)
{
	if (m_texture) {
		glDeleteTextures(1, &m_texture);
	}
	m_texture = oglInitTexture(img, width, height);
}

void COpenGLControl::oglSetKinect(Kinect2Manager * km)
{
	m_kinectManager = km;
	m_kinectManager->InitializeDefaultSensor();
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, 1, -1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.f, 1.f, 1.f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f); glVertex2d(-1.0f, -1.0f);
	glTexCoord2f(1.f, 0.f); glVertex2d(1.0f, -1.0f);
	glTexCoord2f(1.f, 1.f); glVertex2d(1.0f, 1.0f);
	glTexCoord2f(0.f, 1.f); glVertex2d(-1.0f, 1.0f);
	glEnd();

	RGBQUAD col;
	col.rgbRed = 200;
	col.rgbGreen = 10;
	col.rgbBlue = 10;

	//show skeleton (need coordinate mapper)
	ICoordinateMapper * cm = m_kinectManager->getCoordinateMapper();
	if (cm) {
		if (m_kinectManager->getSkeletonIsGood()) {
			Joint * jptr = m_kinectManager->GetJoints();

			std::vector<CameraSpacePoint> jcam(JointType_Count);
			for (int j = 0; j < JointType_Count; ++j)
			{
				jcam[j] = jptr[j].Position;
			}
			std::vector<ColorSpacePoint> jcol(JointType_Count);

			cm->MapCameraPointsToColorSpace(JointType_Count, jcam.data(), JointType_Count, jcol.data());

			float x_ratio = (2.f) / m_kinectOrigWidth;
			float y_ratio = (2.f) / m_kinectOrigHeight;

			float x_offset = -1.f;
			float y_offset = -1.f;

			glPointSize(5.f);
			glBegin(GL_POINTS);

			for (int j = 0; j < JointType_Count; ++j) {
				int x = jcol[j].X * x_ratio + x_offset;
				int y = jcol[j].Y * y_ratio + y_offset;

				glVertex2f(x, y);
			}

			glEnd();
		}
	}
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
	/*glLoadIdentity();
	glTranslatef(0.f, 0.f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.f);
	glRotatef(m_fRotX, 1.f, 0.f, 0.f);
	glRotatef(m_fRotY, 0.f, 1.f, 0.f);*/
}


void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent) {
	case 1:
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (m_kinectManager) {
			m_kinectManager->Update(Update::Color | Update::Depth | Update::Body | Update::BodyIndex);
			RGBQUAD * rgbx = m_kinectManager->GetColorRGBX();
			int width = m_kinectManager->getColorWidth();
			int height = m_kinectManager->getColorHeight();

			int nWidth = 512;
			int nHeight = 512;

			std::vector<RGBQUAD> rgbx_res(nWidth * nHeight);

			resize_rgbquad(rgbx, width, height, rgbx_res.data(), nWidth, nHeight);

			oglSetTexture(rgbx_res.data(), nWidth, nHeight);

			m_kinectOrigWidth = width;
			m_kinectOrigHeight = height;
			m_kinectNewWidth = nWidth;
			m_kinectNewHeight = nHeight;
		}

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
	/*int diffX = (int)(point.x - m_fLastX);
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

	OnDraw(NULL);*/

	CWnd::OnMouseMove(nFlags, point);
}

GLuint oglInitTexture(RGBQUAD * img, int width, int height)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the original
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// the texture wraps over at the edges (repeat)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, img);

	return texture;
}