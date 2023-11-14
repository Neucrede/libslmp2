// CommandView.cpp : implementation file
//

#include "stdafx.h"
#include "ccgen.h"
#include "CommandView.h"
#include "CcgenDoc.h"

#include "FieldObject.h"
#include "GroupObject.h"
#include "NewCmdElemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandView

IMPLEMENT_DYNCREATE(CCommandView, CFormView)

CCommandView::CCommandView()
	: CFormView(CCommandView::IDD)
{
	//{{AFX_DATA_INIT(CCommandView)
	m_bAddrLenDep = FALSE;
	m_avail = 2;        // Both
	m_strCmdBrief = _T("");
	m_strCmdName = _T("");
	m_strFieldBrief = _T("");
	m_strFieldName = _T("");
	m_sizeAsc16B = 1;
	m_sizeAsc32B = 1;
	m_sizeBin16B = 1;
	m_sizeBin32B = 1;
	m_strStructType = _T("");
	m_bVarSize = FALSE;
	m_bStringAsc16B = FALSE;
	m_bStringAsc32B = FALSE;
	m_bStringBin16B = FALSE;
	m_bStringBin32B = FALSE;
	m_bStringVarSize = FALSE;
	m_supportedStreamType = 2;
	m_bSizeField = FALSE;
	m_strSizeField = _T("");
	//}}AFX_DATA_INIT

    m_imgList.Create(IDR_CMDTREE_IMAGE_LIST, 16, 1, RGB(255, 0, 0));
    m_cmdObj = NULL;
    m_selElem = NULL;
    m_bUpdating = false;
    m_bInitialUpdate = true;
}

CCommandView::~CCommandView()
{
}

void CCommandView::DoDataExchange(CDataExchange* pDX)
{
    CDocument* pDoc = GetDocument();
    if (!pDoc) {
        return;
    }

	CFormView::DoDataExchange(pDX);

    if (!m_cmdObj) {
        return;
    }

    if (!(pDX->m_bSaveAndValidate)) {
        m_strCmdName = m_cmdObj->m_strName;
        m_strStructType = m_cmdObj->m_strStructType;
        m_strCmdBrief = m_cmdObj->m_strBrief;
        m_bAddrLenDep = m_cmdObj->m_bAddrLenDep;
        m_supportedStreamType = m_cmdObj->m_supportedStreamType;
        
        // Initialize m_treeCmd first.
        DDX_Control(pDX, IDC_CMD_TREE, m_treeCmd);
        UpdateCmdTree();

        if (m_selElem) {
            CRuntimeClass *clazz = m_selElem->GetRuntimeClass();
            if (clazz == RUNTIME_CLASS(CGroupObject)) {
                CGroupObject *grp = (CGroupObject*)(m_selElem);
                m_strFieldName = grp->m_strName;
            }
            else if (clazz == RUNTIME_CLASS(CFieldObject)) {
                CFieldObject *field = (CFieldObject*)(m_selElem);
                m_strFieldName = field->m_strName;
                m_strFieldBrief = field->m_strBrief;
                m_sizeAsc16B = field->m_sizeAsc16B;
                m_sizeBin16B = field->m_sizeBin16B;
                m_sizeAsc32B = field->m_sizeAsc32B;
                m_sizeBin32B = field->m_sizeBin32B;
                m_bVarSize = field->m_bVarSize;
                m_bSizeField = field->m_bSizeField;
                m_strSizeField = field->m_strSizeField;
                m_bStringBin16B = field->m_bStringBin16B;
                m_bStringAsc16B = field->m_bStringAsc16B;
                m_bStringBin32B = field->m_bStringBin32B;
                m_bStringAsc32B = field->m_bStringAsc32B;
                m_bStringVarSize = field->m_bStringVarSize;
                m_avail = field->m_avail;
            }
        }
    }

	//{{AFX_DATA_MAP(CCommandView)
	DDX_Control(pDX, IDC_CMD_TREE, m_treeCmd);
	DDX_Check(pDX, IDC_ADDR_LEN_DEP, m_bAddrLenDep);
	DDX_Radio(pDX, IDC_AVAIL_BIN, m_avail);
	DDX_Text(pDX, IDC_COMMAND_BRIEF, m_strCmdBrief);
	DDX_Text(pDX, IDC_COMMAND_NAME, m_strCmdName);
	DDX_Text(pDX, IDC_FIELD_BRIEF, m_strFieldBrief);
	DDX_Text(pDX, IDC_FIELD_NAME, m_strFieldName);
	DDX_Text(pDX, IDC_SIZE_ASC_16B, m_sizeAsc16B);
	DDV_MinMaxUInt(pDX, m_sizeAsc16B, 1, 32);
	DDX_Text(pDX, IDC_SIZE_ASC_32B, m_sizeAsc32B);
	DDV_MinMaxUInt(pDX, m_sizeAsc32B, 1, 32);
	DDX_Text(pDX, IDC_SIZE_BIN_16B, m_sizeBin16B);
	DDV_MinMaxUInt(pDX, m_sizeBin16B, 1, 32);
	DDX_Text(pDX, IDC_SIZE_BIN_32B, m_sizeBin32B);
	DDV_MinMaxUInt(pDX, m_sizeBin32B, 1, 32);
	DDX_Text(pDX, IDC_STRUCT_TYPE, m_strStructType);
	DDX_Check(pDX, IDC_VARIABLE_SIZE, m_bVarSize);
	DDX_Check(pDX, IDC_STRING_FIELD_ASC_16B, m_bStringAsc16B);
	DDX_Check(pDX, IDC_STRING_FIELD_ASC_32B, m_bStringAsc32B);
	DDX_Check(pDX, IDC_STRING_FIELD_BIN_16B, m_bStringBin16B);
	DDX_Check(pDX, IDC_STRING_FIELD_BIN_32B, m_bStringBin32B);
	DDX_Check(pDX, IDC_STRING_FIELD_VAR_SIZE, m_bStringVarSize);
	DDX_CBIndex(pDX, IDC_STREAM_TYPE_SUPPORTED, m_supportedStreamType);
	DDX_Check(pDX, IDC_ENABLE_SIZE_FIELD, m_bSizeField);
	DDX_Text(pDX, IDC_SIZE_FIELD, m_strSizeField);
	//}}AFX_DATA_MAP

    if (pDX->m_bSaveAndValidate) {
        m_cmdObj->m_strName = m_strCmdName;
        m_cmdObj->m_strStructType = m_strStructType;
        m_cmdObj->m_strBrief = m_strCmdBrief;
        m_cmdObj->m_bAddrLenDep = m_bAddrLenDep;
        m_cmdObj->m_supportedStreamType = m_supportedStreamType;

        if (m_selElem) {
            CRuntimeClass *clazz = m_selElem->GetRuntimeClass();
            if (clazz == RUNTIME_CLASS(CGroupObject)) {
                CGroupObject *grp = (CGroupObject*)(m_selElem);
                grp->m_strName = m_strFieldName;
            }
            else if (clazz == RUNTIME_CLASS(CFieldObject)) {
                CFieldObject *field = (CFieldObject*)(m_selElem);
                field->m_strName = m_strFieldName;
                field->m_strBrief = m_strFieldBrief;
                field->m_sizeAsc16B = m_sizeAsc16B;
                field->m_sizeBin16B = m_sizeBin16B;
                field->m_sizeAsc32B = m_sizeAsc32B;
                field->m_sizeBin32B = m_sizeBin32B;
                field->m_bVarSize = m_bVarSize;
                field->m_bSizeField = m_bSizeField;
                field->m_strSizeField = m_strSizeField;
                field->m_bStringBin16B = m_bStringBin16B;
                field->m_bStringAsc16B = m_bStringAsc16B;
                field->m_bStringBin32B = m_bStringBin32B;
                field->m_bStringAsc32B = m_bStringAsc32B;
                field->m_bStringVarSize = m_bStringVarSize;
                field->m_avail = m_avail;

                if (m_strSizeField.IsEmpty()) {
                    field->m_bSizeField = FALSE;
                }
            }
        }

        pDoc->SetModifiedFlag(TRUE);
        pDoc->UpdateAllViews(this);
    }
}


BEGIN_MESSAGE_MAP(CCommandView, CFormView)
	//{{AFX_MSG_MAP(CCommandView)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_WM_TIMER()
	ON_NOTIFY(TVN_SELCHANGED, IDC_CMD_TREE, OnSelchangedCmdTree)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_CMD_TREE, OnItemexpandedCmdTree)
	ON_NOTIFY(TVN_SELCHANGING, IDC_CMD_TREE, OnSelchangingCmdTree)
	ON_BN_CLICKED(IDC_AUTO_STRUCT_TYPE, OnAutoStructType)
	ON_BN_CLICKED(IDC_MOVE_UP, OnMoveUp)
	ON_BN_CLICKED(IDC_MOVE_DOWN, OnMoveDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandView diagnostics

#ifdef _DEBUG
void CCommandView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCommandView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommandView message handlers

BOOL CCommandView::DestroyWindow() 
{
    KillTimer(0);
    UpdateData(TRUE);

	return CFormView::DestroyWindow();
}

void CCommandView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
    switch (lHint) {
    case 1:
        m_cmdObj = NULL;
        break;
    case 2:
        UpdateData(TRUE);
        break;
    default:
        break;
    }
}

void CCommandView::OnNew() 
{
    CNewCmdElemDlg dlg;
    if (dlg.DoModal() != IDOK) {
        return;
    }

    CString &name = dlg.m_strName;
    int type = dlg.m_type;

    switch (type) {
    case 0: // Group
        {
            CGroupObject *group = new CGroupObject();
            group->m_strName = name;
            m_cmdObj->m_listElem.AddTail(group);
        } break;

    case 1: // Field
    case 2: // Field (root)
        {
            CFieldObject *field = new CFieldObject();
            field->m_strName = name;

            if (!m_selElem || (type == 2 /* standalone field */)) {
                m_cmdObj->m_listElem.AddTail(field);
            }
            else {
                CRuntimeClass *clazz = m_selElem->GetRuntimeClass();
                if (clazz == RUNTIME_CLASS(CGroupObject)) {
                    CGroupObject *group = (CGroupObject*)(m_selElem);
                    group->m_listField.AddTail(field);
                }
                else if (clazz == RUNTIME_CLASS(CFieldObject)) {
                    HTREEITEM htiSel = m_treeCmd.GetSelectedItem();
                    HTREEITEM htiParent = m_treeCmd.GetParentItem(htiSel);
                    if (!htiParent) {
                        m_cmdObj->m_listElem.AddTail(field);
                    }
                    else {
                        CGroupObject *group = (CGroupObject*)(m_treeCmd.GetItemData(htiParent));
                        group->m_listField.AddTail(field);
                    }
                }
                else {
                    CString msg;
                    msg.Format(IDS_UNKNOWN_CLASS, clazz->m_lpszClassName);
                    AfxMessageBox(msg);
                }
            }
        } break;

    default:
        break;
    }

    UpdateCmdTree();
}

void CCommandView::OnTimer(UINT nIDEvent) 
{
    if (nIDEvent == 0) {
        UpdateUI();
    }

	CFormView::OnTimer(nIDEvent);
}

BOOL CCommandView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	BOOL bRet = CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, 
        pParentWnd, nID, pContext);
    if (bRet) {
        CTreeCtrl *tree = (CTreeCtrl*)GetDlgItem(IDC_CMD_TREE);
        tree->SetImageList(&m_imgList, TVSIL_NORMAL);
        SetTimer(0, 200, NULL);
    }

    return bRet;
}

void CCommandView::UpdateCmdTree()
{
    if (!m_cmdObj) {
        return;
    }

    m_bUpdating = true;

    CList<HTREEITEM, HTREEITEM> listTreeItem;
    for (HTREEITEM hti = m_treeCmd.GetChildItem(TVI_ROOT); hti != NULL;
        hti = m_treeCmd.GetNextItem(hti, TVGN_NEXT))
    {
        listTreeItem.AddTail(hti);
    }

    CTypedPtrList<CObList, CCommandElement*> &listElem = m_cmdObj->m_listElem;
    POSITION pos = listElem.GetHeadPosition();
    while (pos != NULL) {
        CCommandElement *elem = listElem.GetAt(pos);
        CRuntimeClass *clazz = elem->GetRuntimeClass();

        POSITION tipos = listTreeItem.GetHeadPosition();
        while (tipos != NULL) {
            HTREEITEM hti = listTreeItem.GetAt(tipos);
            if (m_treeCmd.GetItemData(hti) == (DWORD)(elem)) {
                if (clazz == RUNTIME_CLASS(CFieldObject)) {
                    CFieldObject *field = static_cast<CFieldObject*>(elem);
                    m_treeCmd.SetItemText(hti, field->m_strName);
                }
                else if (clazz == RUNTIME_CLASS(CGroupObject)) {
                    CGroupObject *group = static_cast<CGroupObject*>(elem);
                    UpdateGroup(group, hti);
                }

                listTreeItem.RemoveAt(tipos);
                break;
            }

            listTreeItem.GetNext(tipos);
        }

        if (!tipos) {
            if (clazz == RUNTIME_CLASS(CFieldObject)) {
                CFieldObject *field = static_cast<CFieldObject*>(elem);
                HTREEITEM hti = m_treeCmd.InsertItem(
                    field->m_strName, ID_IMG_FIELD, ID_IMG_FIELD);
                m_treeCmd.SetItemData(hti, (DWORD)(field));
            }
            else if (clazz == RUNTIME_CLASS(CGroupObject)) {
                CGroupObject *grp = static_cast<CGroupObject*>(elem);
                HTREEITEM htiGrp = m_treeCmd.InsertItem(
                    grp->m_strName, ID_IMG_GROUP, ID_IMG_GROUP);
                m_treeCmd.SetItemData(htiGrp, (DWORD)(grp));
                UpdateGroup(grp, htiGrp);
            }
        }

        listElem.GetNext(pos);
    }

    POSITION tipos = listTreeItem.GetHeadPosition();
    while (tipos != NULL) {
        HTREEITEM hti = listTreeItem.GetNext(tipos);
        m_treeCmd.DeleteItem(hti);
    }

    m_bUpdating = false;
}

void CCommandView::OnSelchangedCmdTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (m_bUpdating) {
        *pResult = 0;
        return;
    }

    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    TVITEM itemNew = pNMTreeView->itemNew;
    m_selElem = (CCommandElement*)(m_treeCmd.GetItemData(itemNew.hItem));
    UpdateData(FALSE);

	*pResult = 0;
}

void CCommandView::UpdateGroup(CGroupObject *group, HTREEITEM htiGroup)
{
    m_treeCmd.SetItemText(htiGroup, group->m_strName);

    CList<HTREEITEM, HTREEITEM> listFieldTI;
    for (HTREEITEM h = m_treeCmd.GetChildItem(htiGroup); h != NULL;
        h = m_treeCmd.GetNextItem(h, TVGN_NEXT))
    {
        listFieldTI.AddTail(h);
    }

    CTypedPtrList<CObList, CFieldObject*> &listField = group->m_listField;
    POSITION lfpos = listField.GetHeadPosition();
    while (lfpos != NULL) {
        CFieldObject *field = listField.GetAt(lfpos);

        POSITION ftipos = listFieldTI.GetHeadPosition();
        while (ftipos  != NULL) {
            HTREEITEM h = listFieldTI.GetAt(ftipos);
            if (m_treeCmd.GetItemData(h) == (DWORD)(field)) {
                m_treeCmd.SetItemText(h, field->m_strName);
                listFieldTI.RemoveAt(ftipos);
                break;
            }
            listFieldTI.GetNext(ftipos);
        }

        if (!ftipos) {
            HTREEITEM htiField = m_treeCmd.InsertItem(
                field->m_strName, ID_IMG_FIELD, ID_IMG_FIELD, htiGroup);
            m_treeCmd.SetItemData(htiField, (DWORD)(field));
        }
        listField.GetNext(lfpos);
    }

    POSITION ftipos = listFieldTI.GetHeadPosition();
    while (ftipos  != NULL) {
        HTREEITEM h = listFieldTI.GetAt(ftipos);
        m_treeCmd.DeleteItem(h);
        listFieldTI.GetNext(ftipos);
    }

    m_treeCmd.Expand(htiGroup, TVE_EXPAND);
}

void CCommandView::OnDelete() 
{	
    if (!m_selElem) {
        return;
    }

    if (AfxMessageBox(IDS_CONFIRM_DELETE_ELEMENT, MB_YESNO | MB_ICONEXCLAMATION)
        != IDYES)
    {
        return;
    }

    CRuntimeClass *clazz = m_selElem->GetRuntimeClass();
    if (clazz == RUNTIME_CLASS(CGroupObject)) {
        POSITION pos = m_cmdObj->m_listElem.Find(m_selElem);
        if (pos) {
            m_cmdObj->m_listElem.RemoveAt(pos);
        }
    }
    else if (clazz == RUNTIME_CLASS(CFieldObject)) {
        HTREEITEM htiSel = m_treeCmd.GetSelectedItem();
        HTREEITEM htiParent = m_treeCmd.GetParentItem(htiSel);
        if (htiParent) {
            CGroupObject *group = (CGroupObject*)(m_treeCmd.GetItemData(htiParent));
            POSITION pos = group->m_listField.Find(m_selElem);
            if (pos) {
                group->m_listField.RemoveAt(pos);
            }
        }
        else {
            POSITION pos = m_cmdObj->m_listElem.Find(m_selElem);
            if (pos) {
                m_cmdObj->m_listElem.RemoveAt(pos);
            }
        }
    }

    m_selElem = NULL;
    UpdateCmdTree();
    UpdateUI();
}

void CCommandView::UpdateUI()
{
    do {
        bool bSel = (m_selElem != NULL);
        bool bField = 
                m_selElem 
            ?   (m_selElem->GetRuntimeClass() == RUNTIME_CLASS(CFieldObject))
            :   false;
        BOOL bVarSize = IsDlgButtonChecked(IDC_VARIABLE_SIZE);
        BOOL bAddrLenDep = IsDlgButtonChecked(IDC_ADDR_LEN_DEP);

        GetDlgItem(IDC_FIELD_NAME)->EnableWindow(bSel);
        GetDlgItem(IDC_FIELD_BRIEF)->EnableWindow(bSel && bField);
        GetDlgItem(IDC_VARIABLE_SIZE)->EnableWindow(bSel && bField);
        GetDlgItem(IDC_STRING_FIELD_VAR_SIZE)->EnableWindow(bSel && bField && bVarSize);
        GetDlgItem(IDC_ENABLE_SIZE_FIELD)->EnableWindow(bSel && bField && bVarSize);

        BOOL bSizeFieldChecked = IsDlgButtonChecked(IDC_ENABLE_SIZE_FIELD);
        GetDlgItem(IDC_SIZE_FIELD)->EnableWindow(bSel && bField && bVarSize && bSizeFieldChecked);

        GetDlgItem(IDC_AVAIL_BIN)->EnableWindow(bSel && bField);
        GetDlgItem(IDC_AVAIL_ASC)->EnableWindow(bSel && bField);
        GetDlgItem(IDC_AVAIL_BOTH)->EnableWindow(bSel && bField);
        GetDlgItem(IDC_DELETE)->EnableWindow(bSel);
        GetDlgItem(IDC_MOVE_UP)->EnableWindow(bSel);
        GetDlgItem(IDC_MOVE_DOWN)->EnableWindow(bSel);

        bool b1 = (bSel && bField && !bVarSize);
        GetDlgItem(IDC_SIZE_BIN_16B)->EnableWindow(b1);
        GetDlgItem(IDC_STRING_FIELD_BIN_16B)->EnableWindow(b1);
        GetDlgItem(IDC_SIZE_ASC_16B)->EnableWindow(b1);
        GetDlgItem(IDC_STRING_FIELD_ASC_16B)->EnableWindow(b1);

        bool b2 = (bSel && bField && !bVarSize && bAddrLenDep);
        GetDlgItem(IDC_SIZE_BIN_32B)->EnableWindow(b2);
        GetDlgItem(IDC_STRING_FIELD_BIN_32B)->EnableWindow(b2);
        GetDlgItem(IDC_SIZE_ASC_32B)->EnableWindow(b2);
        GetDlgItem(IDC_STRING_FIELD_ASC_32B)->EnableWindow(b2);
    } while (0);
}

void CCommandView::OnItemexpandedCmdTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	TVITEM item = pNMTreeView->itemNew;
    
    // Since only group items can contain visible child items there is no
    // extra validations to do.
    //
    if (pNMTreeView->action == TVE_EXPAND) {
        m_treeCmd.SetItemImage(item.hItem, ID_IMG_GROUP, ID_IMG_GROUP);
    }
    else if (pNMTreeView->action == TVE_COLLAPSE) {
        m_treeCmd.SetItemImage(item.hItem, ID_IMG_GROUP_COLLAPSED, ID_IMG_GROUP_COLLAPSED);
    }
	
	*pResult = 0;
}

void CCommandView::OnSelchangingCmdTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (m_bUpdating) {
        *pResult = 0;
        return;
    }

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    if (!UpdateData(TRUE)) {
        *pResult = TRUE;    // Prevents the selection from changing.
    }
    else {
	    *pResult = 0;
    }
}

void CCommandView::OnAutoStructType() 
{
    CString strCmdName;
    GetDlgItem(IDC_COMMAND_NAME)->GetWindowText(strCmdName);

    int len = strCmdName.GetLength();
    CString str, strStructType;

    for (int i = 0; i < len; ++i) {
        TCHAR ch = strCmdName[i];
        if (isupper(ch)) {
            if (i > 0) {
                str.Format(_T("_%c"), tolower(ch));
                strStructType += str;
            }
            else {
                strStructType += (TCHAR)tolower(ch);
            }
        }
        else {
            strStructType += ch;
        }
    }

    GetDlgItem(IDC_STRUCT_TYPE)->SetWindowText(strStructType);
}

void CCommandView::OnMoveUp() 
{
	AfxMessageBox(IDS_NOT_IMPL);
}

void CCommandView::OnMoveDown() 
{
    AfxMessageBox(IDS_NOT_IMPL);
}
