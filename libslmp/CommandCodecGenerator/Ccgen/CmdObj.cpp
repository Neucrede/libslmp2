// CmdObj.cpp: implementation of the CCommandObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ccgen.h"
#include "CmdObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CCommandObject, CObject, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommandObject::CCommandObject()
: m_strName(_T("")), m_strStructType(_T("")), m_strBrief(_T("")),
    m_bAddrLenDep(FALSE), m_supportedStreamType(2)
{

}

CCommandObject::~CCommandObject()
{

}

void CCommandObject::Serialize(CArchive &ar)
{
    if (ar.IsStoring()) {
        ar << m_strName << m_strStructType << m_strBrief << m_bAddrLenDep << m_supportedStreamType;
    }
    else {
        ar >> m_strName >> m_strStructType >> m_strBrief >> m_bAddrLenDep >> m_supportedStreamType;
    }

    m_listElem.Serialize(ar);
}
