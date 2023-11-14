#if !defined(AFX_NEWCMDELEMDLG_H__7054AF7A_A35B_4EA9_8D51_CCA88E2EC871__INCLUDED_)
#define AFX_NEWCMDELEMDLG_H__7054AF7A_A35B_4EA9_8D51_CCA88E2EC871__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewCmdElemDlg.h : header file
//

#define CMDELEM_TYPE_GROUP      0
#define CMDELEM_TYPE_FIELD      1

/////////////////////////////////////////////////////////////////////////////
// CNewCmdElemDlg dialog

class CNewCmdElemDlg : public CDialog
{
// Construction
public:
	CNewCmdElemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewCmdElemDlg)
	enum { IDD = IDD_NEW_CMDELEM };
	CEdit	m_edtName;
	CString	m_strName;
	int		m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCmdElemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewCmdElemDlg)
	afx_msg void OnChangeName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCMDELEMDLG_H__7054AF7A_A35B_4EA9_8D51_CCA88E2EC871__INCLUDED_)
