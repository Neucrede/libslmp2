// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__0699CCBB_BAC5_4DF4_BBCE_764BD386E89E__INCLUDED_)
#define AFX_LEFTVIEW_H__0699CCBB_BAC5_4DF4_BBCE_764BD386E89E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* Image list indices */
#define ID_IMG_DOCUMENT             0
#define ID_IMG_GLOBAL_PROPS         1
#define ID_IMG_COMMANDS             2
#define ID_IMG_COMMAND              3

#define TREE_ITEM_TYPE_COMMAND      0xAABBCCDD

class CCcgenDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CCcgenDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditClear();
	afx_msg void OnUpdateUIEdit(CCmdUI* pCmdUI);
	afx_msg void OnMoveDown();
	afx_msg void OnMoveUp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CImageList m_imgList;

	HTREEITEM m_htiDocument;
    HTREEITEM m_htiGlobalProps;
    HTREEITEM m_htiCommands;

    bool m_modifying;
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CCcgenDoc* CLeftView::GetDocument()
   { return (CCcgenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__0699CCBB_BAC5_4DF4_BBCE_764BD386E89E__INCLUDED_)
