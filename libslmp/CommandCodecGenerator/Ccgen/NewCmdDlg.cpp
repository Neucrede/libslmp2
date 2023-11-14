// NewCmdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ccgen.h"
#include "NewCmdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCmdDlg dialog


CNewCmdDlg::CNewCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewCmdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewCmdDlg)
	m_strCmdName = _T("NewCommand");
	//}}AFX_DATA_INIT
}


void CNewCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewCmdDlg)
	DDX_Control(pDX, IDC_COMMAND_NAME, m_edtCmdName);
	DDX_Text(pDX, IDC_COMMAND_NAME, m_strCmdName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CNewCmdDlg)
	ON_EN_CHANGE(IDC_COMMAND_NAME, OnChangeCommandName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCmdDlg message handlers

void CNewCmdDlg::OnChangeCommandName() 
{
    bool bEmptyCmdName = (m_edtCmdName.GetWindowTextLength() == 0);
    GetDlgItem(IDOK)->EnableWindow(!bEmptyCmdName);
}
