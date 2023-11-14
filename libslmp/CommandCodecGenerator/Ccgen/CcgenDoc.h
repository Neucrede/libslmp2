// CcgenDoc.h : interface of the CCcgenDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCGENDOC_H__4E586594_B00E_4F64_A0FC_B00EEC1A0B36__INCLUDED_)
#define AFX_CCGENDOC_H__4E586594_B00E_4F64_A0FC_B00EEC1A0B36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdObj.h"

class CCcgenDoc : public CDocument
{
protected: // create from serialization only
	CCcgenDoc();
	DECLARE_DYNCREATE(CCcgenDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCcgenDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCcgenDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Document objects
public:
    CString m_strDesc;
    CTypedPtrList<CObList, CCommandObject*> m_listCmd;
    CString m_strCommandHeaderFilename;
    CString m_strCodecHeaderFilename;
    CString m_strCodecSourceFilename;
    BOOL m_bIncludingOrdinal;
    UINT m_ordinalBegin;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCcgenDoc)
	afx_msg void OnNewCommand();
	afx_msg void OnGenerateTypedef();
	afx_msg void OnGenerateHeader();
	afx_msg void OnGenerateSource();
	afx_msg void OnGenerateExpdef();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCGENDOC_H__4E586594_B00E_4F64_A0FC_B00EEC1A0B36__INCLUDED_)
