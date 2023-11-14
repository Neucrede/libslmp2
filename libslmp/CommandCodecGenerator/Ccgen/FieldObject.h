// FieldObject.h: interface for the CFieldObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELDOBJECT_H__DBC88C25_D3A0_46FB_9AD3_02112084D100__INCLUDED_)
#define AFX_FIELDOBJECT_H__DBC88C25_D3A0_46FB_9AD3_02112084D100__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdElem.h"

class CFieldObject : public CCommandElement  
{
public:
	CFieldObject();
	virtual ~CFieldObject();

  	void Serialize(CArchive& ar);

public:
    CString m_strName;
    CString m_strBrief;
    BOOL m_bVarSize;
    BOOL m_bSizeField;
    CString m_strSizeField;
    UINT m_sizeBin16B;
    UINT m_sizeAsc16B;
    UINT m_sizeBin32B;
    UINT m_sizeAsc32B;
    int m_avail;
    BOOL m_bStringBin16B;
    BOOL m_bStringAsc16B;
    BOOL m_bStringBin32B;
    BOOL m_bStringAsc32B;
    BOOL m_bStringVarSize;  // not used in code generation.

protected:
    DECLARE_SERIAL(CFieldObject)
};

#endif // !defined(AFX_FIELDOBJECT_H__DBC88C25_D3A0_46FB_9AD3_02112084D100__INCLUDED_)
