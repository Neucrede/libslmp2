#if !defined(AFX_COMMANDVIEW_H__32F05FDB_4918_4422_92DC_92663216205E__INCLUDED_)
#define AFX_COMMANDVIEW_H__32F05FDB_4918_4422_92DC_92663216205E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommandView.h : header file
//

#define ID_IMG_GROUP            0
#define ID_IMG_GROUP_COLLAPSED  1
#define ID_IMG_FIELD            2

/////////////////////////////////////////////////////////////////////////////
// CCommandView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CCommandObject;
class CCommandElement;
class CGroupObject;

class CCommandView : public CFormView
{
protected:
	CCommandView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCommandView)

// Form Data
public:
	//{{AFX_DATA(CCommandView)
	enum { IDD = IDD_COMMAND_FORM };
	CTreeCtrl	m_treeCmd;
	BOOL	m_bAddrLenDep;
	int		m_avail;
	CString	m_strCmdBrief;
	CString	m_strCmdName;
	CString	m_strFieldBrief;
	CString	m_strFieldName;
	UINT	m_sizeAsc16B;
	UINT	m_sizeAsc32B;
	UINT	m_sizeBin16B;
	UINT	m_sizeBin32B;
	CString	m_strStructType;
	BOOL	m_bVarSize;
	BOOL	m_bStringAsc16B;
	BOOL	m_bStringAsc32B;
	BOOL	m_bStringBin16B;
	BOOL	m_bStringBin32B;
	BOOL	m_bStringVarSize;
	int		m_supportedStreamType;
	BOOL	m_bSizeField;
	CString	m_strSizeField;
	//}}AFX_DATA

// Attributes
public:
    CCommandObject *m_cmdObj;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandView)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCommandView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void UpdateUI();
	void UpdateCmdTree();
	void UpdateGroup(CGroupObject *group, HTREEITEM htiGroup);
    
    CImageList m_imgList;
    CCommandElement *m_selElem;
    bool m_bUpdating;
    bool m_bInitialUpdate;

	// Generated message map functions
	//{{AFX_MSG(CCommandView)
	afx_msg void OnNew();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangedCmdTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnItemexpandedCmdTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingCmdTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAutoStructType();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDVIEW_H__32F05FDB_4918_4422_92DC_92663216205E__INCLUDED_)
