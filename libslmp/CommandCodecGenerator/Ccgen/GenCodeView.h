#if !defined(AFX_GENCODEVIEW_H__4FD756DE_36E6_441F_811C_D6706CD1D0CE__INCLUDED_)
#define AFX_GENCODEVIEW_H__4FD756DE_36E6_441F_811C_D6706CD1D0CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenCodeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenCodeView view

class CGenCodeView : public CEditView
{
protected:
	CGenCodeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGenCodeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenCodeView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGenCodeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGenCodeView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_textFont;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENCODEVIEW_H__4FD756DE_36E6_441F_811C_D6706CD1D0CE__INCLUDED_)
