// CcgenView.cpp : implementation of the CCcgenView class
//

#include "stdafx.h"
#include "Ccgen.h"

#include "CcgenDoc.h"
#include "CcgenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCcgenView

IMPLEMENT_DYNCREATE(CCcgenView, CFormView)

BEGIN_MESSAGE_MAP(CCcgenView, CFormView)
	//{{AFX_MSG_MAP(CCcgenView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCcgenView construction/destruction

CCcgenView::CCcgenView()
	: CFormView(CCcgenView::IDD)
{
	//{{AFX_DATA_INIT(CCcgenView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CCcgenView::~CCcgenView()
{
}

void CCcgenView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCcgenView)
	//}}AFX_DATA_MAP
}

BOOL CCcgenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CCcgenView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	
    // ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CCcgenView printing

BOOL CCcgenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCcgenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCcgenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCcgenView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CCcgenView diagnostics

#ifdef _DEBUG
void CCcgenView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCcgenView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCcgenDoc* CCcgenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCcgenDoc)));
	return (CCcgenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCcgenView message handlers
