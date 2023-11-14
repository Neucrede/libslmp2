// GlobalPropsView.cpp : implementation file
//

#include "stdafx.h"
#include "Ccgen.h"
#include "GlobalPropsView.h"
#include "CcgenDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGlobalPropsView

IMPLEMENT_DYNCREATE(CGlobalPropsView, CFormView)

CGlobalPropsView::CGlobalPropsView()
	: CFormView(CGlobalPropsView::IDD)
{
	//{{AFX_DATA_INIT(CGlobalPropsView)
	m_strDesc = _T("");
	m_strCommandHeader = _T("");
	m_strCodecSource = _T("");
	m_strCodecHeader = _T("");
	m_bIncludingOrdinal = TRUE;
	m_ordinalBegin = 1000;
	//}}AFX_DATA_INIT
}

CGlobalPropsView::~CGlobalPropsView()
{
}

void CGlobalPropsView::DoDataExchange(CDataExchange* pDX)
{
    CCcgenDoc *doc = (CCcgenDoc*)GetDocument();
    if (!doc) return;

	CFormView::DoDataExchange(pDX);

    if (! pDX->m_bSaveAndValidate) {
        m_strDesc = doc->m_strDesc;
        m_strCommandHeader = doc->m_strCommandHeaderFilename;
        m_strCodecSource = doc->m_strCodecSourceFilename;
        m_strCodecHeader = doc->m_strCodecHeaderFilename;
        m_bIncludingOrdinal = doc->m_bIncludingOrdinal;
        m_ordinalBegin = doc->m_ordinalBegin;
    }

	//{{AFX_DATA_MAP(CGlobalPropsView)
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_strDesc);
	DDX_Text(pDX, IDC_EDIT_COMMAND_HEADER, m_strCommandHeader);
	DDX_Text(pDX, IDC_EDIT_CODEC_SOURCE, m_strCodecSource);
	DDX_Text(pDX, IDC_EDIT_CODEC_HEADER, m_strCodecHeader);
	DDX_Check(pDX, IDC_INCLUDING_ORDINAL, m_bIncludingOrdinal);
	DDX_Text(pDX, IDC_ORDINAL_BEGIN, m_ordinalBegin);
	DDV_MinMaxUInt(pDX, m_ordinalBegin, 1, 65535);
	//}}AFX_DATA_MAP

    if (pDX->m_bSaveAndValidate) {
        doc->m_strDesc = m_strDesc;
        doc->m_strCommandHeaderFilename = m_strCommandHeader;
        doc->m_strCodecHeaderFilename = m_strCodecHeader;
        doc->m_strCodecSourceFilename = m_strCodecSource;
        doc->m_bIncludingOrdinal = m_bIncludingOrdinal;
        doc->m_ordinalBegin = m_ordinalBegin;
    }
}


BEGIN_MESSAGE_MAP(CGlobalPropsView, CFormView)
	//{{AFX_MSG_MAP(CGlobalPropsView)
	ON_EN_CHANGE(IDC_EDIT_DESCRIPTION, OnChangeEditDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalPropsView diagnostics

#ifdef _DEBUG
void CGlobalPropsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGlobalPropsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGlobalPropsView message handlers

BOOL CGlobalPropsView::DestroyWindow() 
{
    UpdateData(TRUE);
	return CFormView::DestroyWindow();
}

void CGlobalPropsView::OnChangeEditDescription() 
{
    CCcgenDoc *doc = (CCcgenDoc*)(m_pDocument);
    doc->SetModifiedFlag(TRUE);
}

void CGlobalPropsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
    if (lHint == 2) {
        UpdateData(TRUE);
    }
}
