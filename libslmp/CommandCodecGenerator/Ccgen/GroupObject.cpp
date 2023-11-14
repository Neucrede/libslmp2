// GroupObject.cpp: implementation of the CGroupObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ccgen.h"
#include "GroupObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CGroupObject, CCommandElement, 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGroupObject::CGroupObject()
: m_strName(_T(""))
{

}

CGroupObject::~CGroupObject()
{

}

void CGroupObject::Serialize(CArchive &ar)
{
    if (ar.IsStoring()) {
        ar << m_strName;
    }
    else {
        ar >> m_strName;
    }

    m_listField.Serialize(ar);
}
