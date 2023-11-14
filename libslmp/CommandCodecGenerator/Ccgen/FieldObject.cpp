// FieldObject.cpp: implementation of the CFieldObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ccgen.h"
#include "FieldObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CFieldObject, CCommandElement, 1)


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFieldObject::CFieldObject()
: m_strName(_T("")), m_strBrief(_T("")), m_bVarSize(FALSE), m_bSizeField(FALSE),
    m_sizeBin16B(1), m_sizeAsc16B(1), m_sizeBin32B(1), m_sizeAsc32B(1), 
    m_avail(2 /* both */),
    m_bStringBin16B(FALSE), m_bStringAsc16B(FALSE), m_bStringBin32B(FALSE),
    m_bStringAsc32B(FALSE), m_bStringVarSize(FALSE)
{

}

CFieldObject::~CFieldObject()
{

}

void CFieldObject::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        ar  << m_strName 
            << m_strBrief 
            << m_bVarSize
            << m_bSizeField
            << m_strSizeField
            << m_sizeBin16B
            << m_sizeAsc16B
            << m_sizeBin32B
            << m_sizeAsc32B
            << m_avail
            << m_bStringBin16B
            << m_bStringAsc16B
            << m_bStringBin32B
            << m_bStringAsc32B
            << m_bStringVarSize;
    }
    else {
        ar  >> m_strName 
            >> m_strBrief 
            >> m_bVarSize
            >> m_bSizeField
            >> m_strSizeField
            >> m_sizeBin16B
            >> m_sizeAsc16B
            >> m_sizeBin32B
            >> m_sizeAsc32B
            >> m_avail
            >> m_bStringBin16B
            >> m_bStringAsc16B
            >> m_bStringBin32B
            >> m_bStringAsc32B
            >> m_bStringVarSize;
    }
}