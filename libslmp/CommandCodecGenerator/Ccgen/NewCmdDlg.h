#if !defined(AFX_NEWCMDDLG_H__A15B0C1F_2613_4EB4_8CF2_6E66D88360C8__INCLUDED_)
#define AFX_NEWCMDDLG_H__A15B0C1F_2613_4EB4_8CF2_6E66D88360C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewCmdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewCmdDlg dialog

class CNewCmdDlg : public CDialog
{
// Construction
public:
	CNewCmdDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewCmdDlg)
	enum { IDD = IDD_NEW_COMMAND };
	CEdit	m_edtCmdName;
	CString	m_strCmdName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewCmdDlg)
	afx_msg void OnChangeCommandName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCMDDLG_H__A15B0C1F_2613_4EB4_8CF2_6E66D88360C8__INCLUDED_)
