#pragma once
#include "afxwin.h"
#include <gl\GL.h>
#include <gl\GLU.h>

class COpenGLControl :
	public CWnd
{
public:
	COpenGLControl();
	virtual ~COpenGLControl();

	void oglCreate(CRect rect, CWnd *parent);

	UINT_PTR m_unpTimer;

private:
	CWnd *hWnd;
	HDC hdc;
	HGLRC hrc;
	int m_nPixelFormat;
	CRect m_rect;
	CRect m_oldWindow;
	CRect m_originalRect;

	float m_fPosX;
	float m_fPosY;
	float m_fZoom;
	float m_fRotX;
	float m_fRotY;
	float m_fLastX;
	float m_fLastY;

	void oglInitialize();
	void oglDrawScene();
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDraw(CDC *pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

