// GenCodeView.cpp : implementation file
//

#include "stdafx.h"
#include "ccgen.h"
#include "GenCodeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenCodeView

IMPLEMENT_DYNCREATE(CGenCodeView, CEditView)

CGenCodeView::CGenCodeView()
{
    m_textFont.CreatePointFont(12, _T("Fixedsys"));
}

CGenCodeView::~CGenCodeView()
{
}


BEGIN_MESSAGE_MAP(CGenCodeView, CEditView)
	//{{AFX_MSG_MAP(CGenCodeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenCodeView drawing

void CGenCodeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CGenCodeView diagnostics

#ifdef _DEBUG
void CGenCodeView::AssertValid() const
{
	CEditView::AssertValid();
}

void CGenCodeView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGenCodeView message handlers

void CGenCodeView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
}

BOOL CGenCodeView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{	
	BOOL bRet;
    
    if (bRet = CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect,
        pParentWnd, nID, pContext))
    {
        CEdit &edit = GetEditCtrl();
        edit.SetFont(&m_textFont);
        edit.SetTabStops(16);   // 4 chars
        edit.SetReadOnly(TRUE);
        edit.SetLimitText((UINT)(-1));
    }

    return bRet;
}

void CGenCodeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
}
