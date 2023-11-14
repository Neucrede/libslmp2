// Ccgen.h : main header file for the CCGEN application
//

#if !defined(AFX_CCGEN_H__FEAD5684_3077_48DF_8734_61FC0C6A2F38__INCLUDED_)
#define AFX_CCGEN_H__FEAD5684_3077_48DF_8734_61FC0C6A2F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCcgenApp:
// See Ccgen.cpp for the implementation of this class
//

class CCcgenApp : public CWinApp
{
public:
	CCcgenApp();

    void ListCode(const CString& code);
    void PromptSaveCode(CString& code, const CString& filename);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCcgenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCcgenApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCGEN_H__FEAD5684_3077_48DF_8734_61FC0C6A2F38__INCLUDED_)
