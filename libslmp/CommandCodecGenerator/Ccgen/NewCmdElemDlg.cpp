// NewCmdElemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ccgen.h"
#include "NewCmdElemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCmdElemDlg dialog


CNewCmdElemDlg::CNewCmdElemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCmdElemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewCmdElemDlg)
	m_strName = _T("NewElement");
	m_type = CMDELEM_TYPE_FIELD;
	//}}AFX_DATA_INIT
}


void CNewCmdElemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewCmdElemDlg)
	DDX_Control(pDX, IDC_NAME, m_edtName);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Radio(pDX, IDC_TYPE, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewCmdElemDlg, CDialog)
	//{{AFX_MSG_MAP(CNewCmdElemDlg)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCmdElemDlg message handlers

void CNewCmdElemDlg::OnChangeName() 
{
    bool bEmpty = (m_edtName.GetWindowTextLength() == 0);
    GetDlgItem(IDOK)->EnableWindow(!bEmpty);
}
