#if !defined(AFX_GLOBALPROPSVIEW_H__CE335D82_CAC0_45BE_B2E6_DC7A3C6DB957__INCLUDED_)
#define AFX_GLOBALPROPSVIEW_H__CE335D82_CAC0_45BE_B2E6_DC7A3C6DB957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GlobalPropsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGlobalPropsView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CGlobalPropsView : public CFormView
{
protected:
	CGlobalPropsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGlobalPropsView)

// Form Data
public:
	//{{AFX_DATA(CGlobalPropsView)
	enum { IDD = IDD_GLOBALPROPS_FORM };
	CString	m_strDesc;
	CString	m_strCommandHeader;
	CString	m_strCodecSource;
	CString	m_strCodecHeader;
	BOOL	m_bIncludingOrdinal;
	UINT	m_ordinalBegin;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlobalPropsView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGlobalPropsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CGlobalPropsView)
	afx_msg void OnChangeEditDescription();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBALPROPSVIEW_H__CE335D82_CAC0_45BE_B2E6_DC7A3C6DB957__INCLUDED_)
