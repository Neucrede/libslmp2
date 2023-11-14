// CmdElem.h: interface for the CCommandElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDELEM_H__C5740D43_03E7_4AF8_A182_F2BCD26F8FE6__INCLUDED_)
#define AFX_CMDELEM_H__C5740D43_03E7_4AF8_A182_F2BCD26F8FE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommandElement : public CObject  
{
public:
	CCommandElement();
	virtual ~CCommandElement();

protected:
    DECLARE_SERIAL(CCommandElement)
};

#endif // !defined(AFX_CMDELEM_H__C5740D43_03E7_4AF8_A182_F2BCD26F8FE6__INCLUDED_)
