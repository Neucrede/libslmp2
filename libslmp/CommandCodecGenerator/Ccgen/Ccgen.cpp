// Ccgen.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Ccgen.h"

#include "MainFrm.h"
#include "CcgenDoc.h"
#include "LeftView.h"
#include "GlobalPropsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCcgenApp

BEGIN_MESSAGE_MAP(CCcgenApp, CWinApp)
	//{{AFX_MSG_MAP(CCcgenApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCcgenApp construction

CCcgenApp::CCcgenApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCcgenApp object

CCcgenApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCcgenApp initialization

BOOL CCcgenApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("libslmp2"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCcgenDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

    RECT *rect = NULL;
    UINT n;
    if (GetProfileBinary(_T("MainWnd"), _T("Rect"), (LPBYTE*)(&rect), &n)) {
        m_pMainWnd->MoveWindow(rect);
        delete rect;
    }

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

void CCcgenApp::ListCode(const CString& code)
{
    ((CMainFrame*)(m_pMainWnd))->ListCode(code);
}

void CCcgenApp::PromptSaveCode(CString& code, const CString& filename)
{
    CFileDialog dlg(FALSE, NULL, filename, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("C Source Files (*.c)|*.c|C/C++ Header Files (*.h)|*.h|All Files (*.*)|*.*||"));
    if (dlg.DoModal() != IDOK) {
        return;
    }

    CString strFilePath = dlg.GetPathName();
    try {
        CStdioFile file(strFilePath, CFile::modeCreate | CFile::modeWrite);
        file.Write((PVOID)(code.GetBuffer(0)), code.GetLength());
    }
    catch (CFileException &e) {
        TCHAR szErr[1024];
        if (e.GetErrorMessage(szErr, 1023)) {
            AfxMessageBox(szErr, MB_ICONEXCLAMATION);
        }
    }
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCcgenApp::OnAppAbout()
{
    PlaySound(_T("SystemStart"), AfxGetInstanceHandle(), SND_ALIAS | SND_ASYNC);

	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCcgenApp message handlers

#include "CommandView.h"
