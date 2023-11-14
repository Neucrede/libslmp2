// CcgenDoc.cpp : implementation of the CCcgenDoc class
//

#include "stdafx.h"
#include "Ccgen.h"

#include "CcgenDoc.h"
#include "NewCmdDlg.h"
#include "MainFrm.h"
#include "GenCodeView.h"

#include "CodeGenerator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCcgenApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCcgenDoc

IMPLEMENT_DYNCREATE(CCcgenDoc, CDocument)

BEGIN_MESSAGE_MAP(CCcgenDoc, CDocument)
	//{{AFX_MSG_MAP(CCcgenDoc)
	ON_COMMAND(ID_NEW_COMMAND, OnNewCommand)
	ON_COMMAND(ID_GENERATE_TYPEDEF, OnGenerateTypedef)
	ON_COMMAND(ID_GENERATE_HEADER, OnGenerateHeader)
	ON_COMMAND(ID_GENERATE_SOURCE, OnGenerateSource)
	ON_COMMAND(ID_GENERATE_EXPDEF, OnGenerateExpdef)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCcgenDoc construction/destruction

CCcgenDoc::CCcgenDoc()
{
	// TODO: add one-time construction code here

}

CCcgenDoc::~CCcgenDoc()
{
}

BOOL CCcgenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCcgenDoc serialization

void CCcgenDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
        POSITION pos = GetFirstViewPosition();
        while (pos != NULL) {
            CView *view = GetNextView(pos);
            view->UpdateData(TRUE);
        }

		ar << m_strDesc;
        m_listCmd.Serialize(ar);
        ar  << m_strCommandHeaderFilename
            << m_strCodecHeaderFilename
            << m_strCodecSourceFilename
            << m_bIncludingOrdinal
            << m_ordinalBegin;
	}
	else
	{
		ar >> m_strDesc;
        m_listCmd.Serialize(ar);
        ar  >> m_strCommandHeaderFilename
            >> m_strCodecHeaderFilename
            >> m_strCodecSourceFilename
            >> m_bIncludingOrdinal
            >> m_ordinalBegin;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCcgenDoc diagnostics

#ifdef _DEBUG
void CCcgenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCcgenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCcgenDoc commands

void CCcgenDoc::DeleteContents() 
{
    UpdateAllViews(NULL, 1);

    m_strDesc.Empty();
    m_strCommandHeaderFilename = _T("commands.h");
    m_strCodecHeaderFilename = _T("codec.h");
    m_strCodecSourceFilename = _T("codec.c");
    m_bIncludingOrdinal = TRUE;
    m_ordinalBegin = 1000;

    while (!m_listCmd.IsEmpty()) {
        delete m_listCmd.RemoveHead();
    }

	CDocument::DeleteContents();
}


void CCcgenDoc::OnNewCommand() 
{
    CNewCmdDlg dlg;
    if (dlg.DoModal() != IDOK) {
        return;
    }

    CString &cmdName = dlg.m_strCmdName;

    POSITION pos = m_listCmd.GetHeadPosition();
    while (pos != NULL)
    {
        CCommandObject *cmd = m_listCmd.GetNext(pos);
        if (cmdName == cmd->m_strName) {
            CString msg;
            msg.Format(IDS_COMMAND_EXISTS, cmdName);
            AfxMessageBox(msg);
            return;
        }
    }

    CCommandObject *cmd = new CCommandObject();
    cmd->m_strName = cmdName;
    m_listCmd.AddTail(cmd);

    UpdateAllViews(NULL);
    SetModifiedFlag(TRUE);
}

void CCcgenDoc::OnGenerateTypedef() 
{
    UpdateAllViews(NULL, 2);
    CCodeGenerator gen(this);
    CString code;
    gen.GenerateCommandHeader(code);
    theApp.ListCode(code);
    theApp.PromptSaveCode(code, m_strCommandHeaderFilename);
}

void CCcgenDoc::OnGenerateHeader() 
{
	UpdateAllViews(NULL, 2);
    CCodeGenerator gen(this);
    CString code;
    gen.GenerateCodecHeader(code);
    theApp.ListCode(code);
    theApp.PromptSaveCode(code, m_strCodecHeaderFilename);
}

void CCcgenDoc::OnGenerateSource() 
{	
    UpdateAllViews(NULL, 2);
    CCodeGenerator gen(this);
    CString code;
    gen.GenerateCodecSource(code);
    theApp.ListCode(code);
    theApp.PromptSaveCode(code, m_strCodecSourceFilename);
}

void CCcgenDoc::OnGenerateExpdef() 
{
	UpdateAllViews(NULL, 2);
    CCodeGenerator gen(this);
    CString code;
    gen.GenerateExportDefinitions(code);
    theApp.ListCode(code);
}
