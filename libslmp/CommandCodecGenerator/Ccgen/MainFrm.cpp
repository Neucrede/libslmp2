// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Ccgen.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "CcgenView.h"
#include "GenCodeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCcgenApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

    m_wndToolBar.SetWindowText(_T("Standard"));

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
    int colWidth0 = (int)(theApp.GetProfileInt(_T("MainWnd"), _T("ColWidth0"), 200));

	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(colWidth0, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCcgenView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

    // remove the ugly useless horizontal scrollbar
    m_wndSplitter.RecalcLayout();

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

BOOL CMainFrame::ChangeRightView(CRuntimeClass *pViewClass, bool bUpdateData)
{
    ASSERT(pViewClass);

    CView *pViewOld = GetRightView();
    if (!pViewOld) {
        return FALSE;
    }

    CCreateContext ctx;
    CDocument *pActiveDoc = GetActiveDocument();
    ctx.m_pCurrentDoc = pActiveDoc;

    if (bUpdateData) {
        pViewOld->UpdateData(TRUE);
    }

    // Fool CSplitterWnd that the right pane doesn't exist ;-p
    pViewOld->SetDlgCtrlID(-1);

    if (pActiveDoc) {
        pActiveDoc->RemoveView(pViewOld);
        ctx.m_pNewDocTemplate = pActiveDoc->GetDocTemplate();
    }

    if (!m_wndSplitter.CreateView(0, 1, pViewClass, CSize(100, 100), &ctx)) {
        return FALSE;
    }

    m_wndSplitter.RecalcLayout();

    if (pViewOld) {
        pViewOld->DestroyWindow();
    }

    CView *pView = GetRightView();
    SetActiveView((CView*)m_wndSplitter.GetPane(0, 0)); //left pane
    CDocument *pDoc = pView->GetDocument();
    if (pDoc) {
        pDoc->OnChangedViewList();
    }
    
    return TRUE;
}

CView* CMainFrame::GetRightView()
{
    return (CView*)(m_wndSplitter.GetPane(0, 1));
}

void CMainFrame::ListCode(const CString& code)
{
    ChangeRightView(RUNTIME_CLASS(CGenCodeView));
    CGenCodeView *pView = (CGenCodeView*)GetRightView();

    CString code2 = code;
    code2.Replace(_T("\n"), _T("\r\n"));
    pView->GetEditCtrl().SetWindowText(code2);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose() 
{
    WINDOWPLACEMENT wp;
    GetWindowPlacement(&wp);
    if (wp.showCmd != SW_MAXIMIZE) {
        RECT rect;
        GetWindowRect(&rect);
        theApp.WriteProfileBinary(_T("MainWnd"), _T("Rect"), (LPBYTE)(&rect), sizeof(RECT));
    }
    
    int colWidth0, cxMin;
    m_wndSplitter.GetColumnInfo(0, colWidth0, cxMin);
    theApp.WriteProfileInt(_T("MainWnd"), _T("ColWidth0"), colWidth0);

	CFrameWnd::OnClose();
}
