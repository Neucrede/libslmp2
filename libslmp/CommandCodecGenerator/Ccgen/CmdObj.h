// CmdObj.h: interface for the CCommandObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDOBJ_H__6E351963_D602_4450_BD75_7653FA199DA1__INCLUDED_)
#define AFX_CMDOBJ_H__6E351963_D602_4450_BD75_7653FA199DA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdElem.h"

class CCommandObject : public CObject  
{
public:
	CCommandObject();
 	virtual ~CCommandObject();

public:
    CString m_strName;
    CString m_strStructType;
    CString m_strBrief;
    BOOL m_bAddrLenDep;
    int m_supportedStreamType;
    CTypedPtrList<CObList, CCommandElement*> m_listElem;

public:
	void Serialize(CArchive& ar);
    

protected:
    DECLARE_SERIAL(CCommandObject)
};

#endif // !defined(AFX_CMDOBJ_H__6E351963_D602_4450_BD75_7653FA199DA1__INCLUDED_)
