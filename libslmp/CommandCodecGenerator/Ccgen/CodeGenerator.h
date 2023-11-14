// CodeGenerator.h: interface for the CCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEGENERATOR_H__E2935F71_23CE_4667_AC88_24224C3B94E4__INCLUDED_)
#define AFX_CODEGENERATOR_H__E2935F71_23CE_4667_AC88_24224C3B94E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCcgenDoc;
class CCommandObject;
class CFieldObject;
class CGroupObject;

class CCodeGenerator : public CObject  
{
    enum AddressLength
    {
        AddressLength16B, AddressLength32B, Unaware
    };

    enum StreamType
    {
        Binary, ASCII
    };

public:
	CCodeGenerator(CCcgenDoc* pDoc = NULL);
	virtual ~CCodeGenerator();

    void GenerateCommandHeader(CString& code);
    void GenerateCodecHeader(CString& code);
    void GenerateCodecSource(CString& code);
    void GenerateExportDefinitions(CString& code);

protected:
    CString GetNextLine(const CString& content, int& startPos);
    CString IndentLine(const CString& line, UINT uIndent);
    CString IndentBlock(const CString& block, UINT uIndent);
    CString CommentBlock(const CString& content, UINT uIndent = 0, bool bDoxygen = FALSE);

    void AppendCommandTypedef(const CCommandObject* cmd, CString& code, UINT uIndent = 0);
    void AppendFieldDeclAddrLenIndep(const CFieldObject* field, CString& code, UINT uIndent = 0);
    void AppendFieldDeclAddrLenDep(const CFieldObject* field, CString& code, UINT uIndent = 0);
    void AppendVarDecl(const CString& name, CString& code, int size, BOOL bString = FALSE, UINT uIndent = 0);
    void AppendUnionDecl(const CString& unionName, CString& code, const CString& name1, 
        const CString& name2, UINT size1, UINT size2, BOOL bString1, BOOL bString2,
        UINT uIndent, BOOL bBoth = FALSE);

    void AppendEncodeFcnImpl(const CCommandObject* cmd, CString& code);
    void AppendDecodeFcnImpl(const CCommandObject* cmd, CString& code);
    BOOL GetVariableSizeFields(const CCommandObject* cmd, CArray<CFieldObject*, CFieldObject*>* fields = NULL,
        BOOL *pbAllDeclaredAsPointers = NULL);
    void GetFixedPartSize(const CCommandObject* cmd, UINT& uSizeBin16B, UINT& uSizeAsc16B,
        UINT& uSizeBin32B, UINT& uSizeAsc32B);
    void GetFieldAccessExpr(const CFieldObject* field, CString& strExpr, int& fieldLen, const CString& grpName = CString(),
        StreamType strmType = Binary, AddressLength addrLen = Unaware, BOOL bGlobalAddrLenUnaware = FALSE);
    void AppendCodecStatements(const CCommandObject* cmd, CString &code, UINT uIndent = 0,
        StreamType strmType = Binary, BOOL bAddrLenDep = FALSE, BOOL bDecode = FALSE);
    void AppendCodecStatements(const CCommandObject* cmd, CString& code, UINT uIndent = 0,
        StreamType strmType = Binary, AddressLength addrLen = Unaware, BOOL bDecode = FALSE);
    void AppendFieldCodecStatement(const CFieldObject* field, CString& code, UINT uIndent = 0,
        StreamType strmType = Binary, AddressLength addrLen = Unaware, UINT uSizeCopy = 0,
        BOOL bDecode = FALSE, BOOL bGlobalAddrLenUnaware = FALSE);

protected:
    CCcgenDoc *m_pDoc;

};

#endif // !defined(AFX_CODEGENERATOR_H__E2935F71_23CE_4667_AC88_24224C3B94E4__INCLUDED_)
