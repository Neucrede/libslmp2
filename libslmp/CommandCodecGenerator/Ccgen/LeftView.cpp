// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Ccgen.h"

#include "CcgenDoc.h"
#include "LeftView.h"

#include "MainFrm.h"
#include "CcgenView.h"
#include "GenCodeView.h"
#include "GlobalPropsView.h"
#include "CommandView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateUIEdit)
    ON_UPDATE_COMMAND_UI(ID_MOVE_UP, OnUpdateUIEdit)
    ON_UPDATE_COMMAND_UI(ID_MOVE_DOWN, OnUpdateUIEdit)
	ON_COMMAND(ID_MOVE_DOWN, OnMoveDown)
	ON_COMMAND(ID_MOVE_UP, OnMoveUp)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
: m_modifying(false)
{
	// TODO: add construction code here
    m_imgList.Create(IDR_TREE_IMAGE_LIST, 16, 1, RGB(192, 192, 192));
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    
    cs.style |= (TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS);

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CCcgenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLeftView::OnInitialUpdate()
{
    // Empty the contents in right pane.
    CMainFrame *pFrame = (CMainFrame*)(GetParentFrame());
    pFrame->ChangeRightView(RUNTIME_CLASS(CCcgenView), false);

    CTreeView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCcgenDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCcgenDoc)));
	return (CCcgenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
    if (lHint != 0) {
        return;
    }

    m_modifying = true;

    CTreeCtrl &tree = GetTreeCtrl();

    CList<HTREEITEM, HTREEITEM> listCmd;
    HTREEITEM child = tree.GetChildItem(m_htiCommands);
    while (child != NULL) {
        listCmd.AddTail(child);
        child = tree.GetNextItem(child, TVGN_NEXT);
    }

    CCcgenDoc *doc = GetDocument();
    POSITION pos = doc->m_listCmd.GetHeadPosition();
    while (pos != NULL)
    {
        CCommandObject *cmd = doc->m_listCmd.GetNext(pos);
        
        POSITION pos2 = listCmd.GetHeadPosition();
        while (pos2 != NULL) {
            HTREEITEM item = listCmd.GetAt(pos2);
            if (tree.GetItemData(item) == (DWORD)cmd) {
                tree.SetItemText(item, cmd->m_strName);
                listCmd.RemoveAt(pos2);
                break;
            }

            listCmd.GetNext(pos2);
        }

        if (!pos2) {
            HTREEITEM item = tree.InsertItem(cmd->m_strName, ID_IMG_COMMAND, 
                ID_IMG_COMMAND, m_htiCommands);
            tree.SetItemData(item, (DWORD)cmd);
        }
    }

    pos = listCmd.GetHeadPosition();
    while (pos != NULL) {
        HTREEITEM item = listCmd.GetNext(pos);
        tree.DeleteItem(item);
    }

    tree.Expand(m_htiDocument, TVE_EXPAND);
    tree.Expand(m_htiCommands, TVE_EXPAND);

    m_modifying = false;
}

void CLeftView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (m_modifying) {
        *pResult = 0;
        return;
    }

    CMainFrame *pFrame = (CMainFrame*)(GetParentFrame());
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    TVITEM itemNew = pNMTreeView->itemNew;
    CTreeCtrl &tree = GetTreeCtrl();
    
    do {
        if (itemNew.hItem == m_htiDocument) {
            pFrame->ChangeRightView(RUNTIME_CLASS(CGenCodeView));
        }
        else if (itemNew.hItem == m_htiGlobalProps) {
            pFrame->ChangeRightView(RUNTIME_CLASS(CGlobalPropsView));
        }
        else if (tree.GetParentItem(itemNew.hItem) == m_htiCommands) {
            pFrame->ChangeRightView(RUNTIME_CLASS(CCommandView));
            CCommandView *view = (CCommandView*)(pFrame->GetRightView());
            view->m_cmdObj = (CCommandObject*)(itemNew.lParam);
        }
        else {
            break;
        }

        pFrame->GetRightView()->UpdateData(FALSE);
    } while (0);
    
	*pResult = 0;
}

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    CTreeCtrl &tree = GetTreeCtrl();
    tree.SetImageList(&m_imgList, TVSIL_NORMAL);
    
    m_htiDocument = tree.InsertItem(_T("Document"), 
        ID_IMG_DOCUMENT, ID_IMG_DOCUMENT);
    m_htiGlobalProps = tree.InsertItem(_T("Global Properties"), 
        ID_IMG_GLOBAL_PROPS, ID_IMG_GLOBAL_PROPS, m_htiDocument);
    tree.Expand(m_htiDocument, TVE_EXPAND);

    m_htiCommands = tree.InsertItem(_T("Commands"), ID_IMG_COMMANDS, 
        ID_IMG_COMMANDS, m_htiDocument);

	return 0;
}

void CLeftView::OnEditClear() 
{
    CTreeCtrl &tree = GetTreeCtrl();
    HTREEITEM item = tree.GetSelectedItem();
    if (tree.GetParentItem(item) != m_htiCommands) {
        return;
    }

    CString msg;
    msg.Format(IDS_CONFIRM_DELETE_COMMAND, tree.GetItemText(item));
    if (AfxMessageBox(msg, MB_YESNO | MB_ICONEXCLAMATION) != IDYES) {
        return;
    }

    CMainFrame *pFrame = (CMainFrame*)(GetParentFrame());
    pFrame->ChangeRightView(RUNTIME_CLASS(CCcgenView));

    CCcgenDoc *pDoc = (CCcgenDoc*)GetDocument();
    CCommandObject *pCmdObj = (CCommandObject*)(tree.GetItemData(item));
    POSITION pos = pDoc->m_listCmd.Find(pCmdObj);
    pDoc->m_listCmd.RemoveAt(pos);

    pDoc->UpdateAllViews(NULL);
}

void CLeftView::OnUpdateUIEdit(CCmdUI* pCmdUI) 
{
    CTreeCtrl &tree = GetTreeCtrl();
    HTREEITEM item = tree.GetSelectedItem();

    BOOL bIsCommand = (tree.GetParentItem(item) == m_htiCommands);
    switch (pCmdUI->m_nID) {
    case ID_EDIT_CLEAR:
        pCmdUI->Enable(bIsCommand);
        break;
    case ID_MOVE_UP:
        pCmdUI->Enable(bIsCommand && tree.GetPrevSiblingItem(item));
        break;
    case ID_MOVE_DOWN:
        pCmdUI->Enable(bIsCommand && tree.GetNextSiblingItem(item));
        break;
    default:
        break;
    }
}

void CLeftView::OnMoveDown() 
{
	CTreeCtrl &tree = GetTreeCtrl();
    HTREEITEM item = tree.GetSelectedItem();
    if (tree.GetParentItem(item) != m_htiCommands) {
        return;
    }

    CCcgenDoc *pDoc = (CCcgenDoc*)GetDocument();
    CCommandObject *pCmdObj = (CCommandObject*)(tree.GetItemData(item));
    POSITION pos = pDoc->m_listCmd.Find(pCmdObj);
    if (pos != pDoc->m_listCmd.GetTailPosition()) {
        POSITION posNext = pos;
        pDoc->m_listCmd.GetNext(posNext);

        pDoc->m_listCmd.RemoveAt(pos);
        pDoc->m_listCmd.InsertAfter(posNext, pCmdObj);
        HTREEITEM item2 = tree.InsertItem(pCmdObj->m_strName, ID_IMG_COMMAND, 
                ID_IMG_COMMAND, m_htiCommands, tree.GetNextSiblingItem(item));
        tree.SetItemData(item2, (DWORD)pCmdObj);
        tree.DeleteItem(item);
        tree.SelectItem(item2);
    }
}

void CLeftView::OnMoveUp() 
{
	CTreeCtrl &tree = GetTreeCtrl();
    HTREEITEM item = tree.GetSelectedItem();
    if (tree.GetParentItem(item) != m_htiCommands) {
        return;
    }

    CCcgenDoc *pDoc = (CCcgenDoc*)GetDocument();
    CCommandObject *pCmdObj = (CCommandObject*)(tree.GetItemData(item));
    POSITION pos = pDoc->m_listCmd.Find(pCmdObj);
    if (pos != pDoc->m_listCmd.GetHeadPosition()) {
        POSITION posPrev = pos;
        pDoc->m_listCmd.GetPrev(posPrev);

        pDoc->m_listCmd.RemoveAt(pos);
        pDoc->m_listCmd.InsertBefore(posPrev, pCmdObj);
        HTREEITEM itemPrev = tree.GetPrevSiblingItem(item);
        itemPrev = tree.GetPrevSiblingItem(itemPrev);
        HTREEITEM item2 = tree.InsertItem(pCmdObj->m_strName, ID_IMG_COMMAND, 
                ID_IMG_COMMAND, m_htiCommands, 
                itemPrev != NULL ? itemPrev : TVI_FIRST);
        tree.SetItemData(item2, (DWORD)pCmdObj);
        tree.DeleteItem(item);
        tree.SelectItem(item2);
    }
}
