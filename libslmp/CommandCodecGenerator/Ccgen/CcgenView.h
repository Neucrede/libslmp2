// CcgenView.h : interface of the CCcgenView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCGENVIEW_H__13E980F2_E1E9_4899_9030_6FB53A373D1B__INCLUDED_)
#define AFX_CCGENVIEW_H__13E980F2_E1E9_4899_9030_6FB53A373D1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCcgenView : public CFormView
{
protected: // create from serialization only
	CCcgenView();
	DECLARE_DYNCREATE(CCcgenView)

public:
	//{{AFX_DATA(CCcgenView)
	enum { IDD = IDD_CCGEN_FORM };
	//}}AFX_DATA

// Attributes
public:
	CCcgenDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCcgenView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCcgenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCcgenView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CcgenView.cpp
inline CCcgenDoc* CCcgenView::GetDocument()
   { return (CCcgenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCGENVIEW_H__13E980F2_E1E9_4899_9030_6FB53A373D1B__INCLUDED_)
