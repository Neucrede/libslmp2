// GroupObject.h: interface for the CGroupObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUPOBJECT_H__54218271_0D69_42FB_8449_3F078A57D875__INCLUDED_)
#define AFX_GROUPOBJECT_H__54218271_0D69_42FB_8449_3F078A57D875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdElem.h"
#include "FieldObject.h"

class CGroupObject : public CCommandElement  
{
public:
	CGroupObject();
	virtual ~CGroupObject();

    void Serialize(CArchive &ar);

public:
    CString m_strName;
    CTypedPtrList<CObList, CFieldObject*> m_listField;

protected:
    DECLARE_SERIAL(CGroupObject)
};

#endif // !defined(AFX_GROUPOBJECT_H__54218271_0D69_42FB_8449_3F078A57D875__INCLUDED_)
