
// VoiceSportsView.cpp : implementation of the CVoiceSportsView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VoiceSports.h"
#endif

#include "VoiceSportsDoc.h"
#include "VoiceSportsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVoiceSportsView

IMPLEMENT_DYNCREATE(CVoiceSportsView, CView)

BEGIN_MESSAGE_MAP(CVoiceSportsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVoiceSportsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CVoiceSportsView construction/destruction

CVoiceSportsView::CVoiceSportsView()
{
	// TODO: add construction code here

}

CVoiceSportsView::~CVoiceSportsView()
{
}

BOOL CVoiceSportsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVoiceSportsView drawing

void CVoiceSportsView::OnDraw(CDC* /*pDC*/)
{
	CVoiceSportsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CVoiceSportsView printing


void CVoiceSportsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CVoiceSportsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVoiceSportsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVoiceSportsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVoiceSportsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVoiceSportsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVoiceSportsView diagnostics

#ifdef _DEBUG
void CVoiceSportsView::AssertValid() const
{
	CView::AssertValid();
}

void CVoiceSportsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVoiceSportsDoc* CVoiceSportsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVoiceSportsDoc)));
	return (CVoiceSportsDoc*)m_pDocument;
}
#endif //_DEBUG


// CVoiceSportsView message handlers
