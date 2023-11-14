// CodeGenerator.cpp: implementation of the CCodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ccgen.h"
#include "CodeGenerator.h"

#include "CcgenDoc.h"
#include "FieldObject.h"
#include "GroupObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCodeGenerator::CCodeGenerator(CCcgenDoc* pDoc)
: m_pDoc(pDoc)
{
    ASSERT(m_pDoc != NULL);
}

CCodeGenerator::~CCodeGenerator()
{

}

void CCodeGenerator::GenerateCommandHeader(CString& code)
{
    code.Empty();

    CString strFileComment;
    strFileComment.Format(
        _T( "\\file %s"
            "\n\n"
            "\\brief %s\n\n"
            "This file was generated from %s by CCGEN program.\n"), 
        m_pDoc->m_strCommandHeaderFilename,
        m_pDoc->m_strDesc,
        m_pDoc->GetPathName());
    code += CommentBlock(strFileComment, 0, TRUE);
    code += _T("\n");

    CString strGuardMacroName = m_pDoc->m_strCommandHeaderFilename;
    strGuardMacroName.MakeUpper();
    strGuardMacroName.Replace(_T('.'), _T('_'));
    
    CString strGuardBegin;
    strGuardBegin.Format(
        _T( "#ifndef %s\n"
            "#define %s\n\n" ),
        strGuardMacroName,
        strGuardMacroName);
    code += strGuardBegin;

    code += _T(
        "#include \"slmp/command/cmdhdr.h\" \n"
        "#include \"slmp/_pushpack4.h\" \n\n"
    );

    CTypedPtrList<CObList, CCommandObject*> &listCmd = m_pDoc->m_listCmd;
    POSITION pos = listCmd.GetHeadPosition();
    while (pos != NULL) {
        CCommandObject *cmd = listCmd.GetNext(pos);
        AppendCommandTypedef(cmd, code, 0);
    }

    code += _T("\n\n#include \"slmp/_poppack.h\" \n");

    CString strGuardEnd;
    strGuardEnd.Format(_T("\n#endif /* %s */\n"), strGuardMacroName);
    code += strGuardEnd;

    code.Replace(_T("\r\n"), _T("\n"));
}

void CCodeGenerator::GenerateCodecHeader(CString& code)
{
    code.Empty();

    CString strFileComment;
    strFileComment.Format(
        _T( "\\file %s"
            "\n\n"
            "\\brief %s\n\n"
            "This file was generated from %s by CCGEN program.\n"), 
        m_pDoc->m_strCodecHeaderFilename,
        m_pDoc->m_strDesc,
        m_pDoc->GetPathName());
    code += CommentBlock(strFileComment, 0, TRUE);
    code += _T("\n");

    CString strGuardMacroName = m_pDoc->m_strCodecHeaderFilename;
    strGuardMacroName.MakeUpper();
    strGuardMacroName.Replace(_T('.'), _T('_'));
    
    CString strGuardBegin;
    strGuardBegin.Format(
        _T( "#ifndef %s\n"
            "#define %s\n\n" ),
        strGuardMacroName,
        strGuardMacroName);
    code += strGuardBegin;

    code += _T(
        "#include \"slmp/slmpapi.h\" \n"
        "#include \"slmp/command/cmdhdr.h\" \n\n"
        "#ifdef __cplusplus \n"
        "extern \"C\" { \n"
        "#endif \n\n"
    );

    CTypedPtrList<CObList, CCommandObject*> &listCmd = m_pDoc->m_listCmd;
    POSITION pos = listCmd.GetHeadPosition();
    CString strFcnDecl;
    while (pos != NULL) {
        CCommandObject *cmd = listCmd.GetNext(pos);
        
        strFcnDecl.Format(
            _T( "SLMPAPI size_t SLMPCALL slmp_encode_%s(\n"
                "    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type);\n\n" ),
            cmd->m_strStructType);
        code += strFcnDecl;

        strFcnDecl.Format(
            _T( "SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_%s(\n"
                "    uint8_t *stream, size_t len, int type, int addr_width);\n\n" ),
            cmd->m_strStructType);
        code += strFcnDecl;
    }

    code += _T(
        "#ifdef __cplusplus \n"
        "} \n"
        "#endif \n\n"
    );

    CString strGuardEnd;
    strGuardEnd.Format(_T("#endif /* %s */\n"), strGuardMacroName);
    code += strGuardEnd;

    code.Replace(_T("\r\n"), _T("\n"));
}

void CCodeGenerator::GenerateCodecSource(CString& code)
{
    code.Empty();
    
    CString strFileComment;
    strFileComment.Format(
        _T( "This file was generated from %s by CCGEN program.\n"), 
        m_pDoc->GetPathName());
    code += CommentBlock(strFileComment, 0, FALSE);
    code += _T("\n");

    CString strIncludeHeaders;
    strIncludeHeaders.Format(
        _T( "#include \"cmdcodec_priv.h\" \n"
            "#include \"slmp/command/%s\" \n"
            "#include \"slmp/codec/%s\" \n\n" ),
        m_pDoc->m_strCommandHeaderFilename,
        m_pDoc->m_strCodecHeaderFilename);
    code += strIncludeHeaders;

    CTypedPtrList<CObList, CCommandObject*> &listCmd = m_pDoc->m_listCmd;
    POSITION pos = listCmd.GetHeadPosition();
    CString strFcnDecl;
    while (pos != NULL) {
        CCommandObject *cmd = listCmd.GetNext(pos);
        AppendEncodeFcnImpl(cmd, code);
        AppendDecodeFcnImpl(cmd, code);
    }

    code.Replace(_T("\r\n"), _T("\n"));
}

void CCodeGenerator::GenerateExportDefinitions(CString& code)
{
    code = _T("EXPORTS\n");

    CTypedPtrList<CObList, CCommandObject*> &listCmd = m_pDoc->m_listCmd;
    POSITION pos = listCmd.GetHeadPosition();
    CString str;
    UINT ordinal = m_pDoc->m_ordinalBegin;
    while (pos != NULL) {
        CCommandObject *cmd = listCmd.GetNext(pos);
        if (m_pDoc->m_bIncludingOrdinal) {
            str.Format(
                _T( "slmp_encode_%s @%u\n"
                    "slmp_decode_%s @%u\n" ),
                cmd->m_strStructType, ordinal,
                cmd->m_strStructType, ordinal + 1);
            ordinal += 2;
        }
        else {
            str.Format(
                _T( "slmp_encode_%s\n"
                    "slmp_decode_%s\n" ),
                cmd->m_strStructType,
                cmd->m_strStructType);
        }

        code += IndentBlock(str, 1);
    }
}

CString CCodeGenerator::GetNextLine(const CString& content, int& startPos)
{
    int len = content.GetLength();
    if (startPos >= len) {
        startPos = -1;
        return CString(_T("\n"));
    }

    int lfPos = content.Find(_T('\n'), startPos);
    
    CString line;
    
    if (lfPos >= 0) {
        line = content.Mid(startPos, lfPos - startPos + 1);
        if (lfPos + 1 < len) {
            startPos = lfPos + 1;
        }
        else {
            startPos = -1;
        }
    }
    else {
        line = content.Mid(startPos);
        startPos = -1;
    }

    if (line.ReverseFind(_T('\n')) < 0) {
        line += _T('\n');
    }

    return line;
}

CString CCodeGenerator::IndentLine(const CString& line, UINT uIndent)
{
    CString str(_T(' '), 4 * uIndent);
    str += line;
    return str;
}

CString CCodeGenerator::IndentBlock(const CString& block, UINT uIndent)
{
    CString str;
    int startPos = 0;
    while (startPos >= 0) {
        str += IndentLine(GetNextLine(block, startPos), uIndent);
    }

    return str;
}

CString CCodeGenerator::CommentBlock(const CString& content, UINT uIndent, bool bDoxygen)
{
    CString comment;
    if (bDoxygen) {
        comment += IndentLine(_T("/**\n"), uIndent);
    }
    else {
        comment += IndentLine(_T("/*\n"), uIndent);
    }

    int startPos = 0;
    while (startPos >= 0) {
        comment += IndentLine(_T(" * "), uIndent);
        comment += GetNextLine(content, startPos);
    }

    comment += IndentLine(_T(" */\n"), uIndent);

    return comment;
}

void CCodeGenerator::AppendCommandTypedef(const CCommandObject* cmd, CString& code, UINT uIndent)
{
    code += _T("\n");
    if (!cmd->m_strBrief.IsEmpty()) {
        CString strComment;
        strComment.Format(_T("\\brief %s\n"), cmd->m_strBrief);
        code += CommentBlock(strComment, uIndent, TRUE);
    }

    CString strDeclBegin;
    strDeclBegin.Format(
        _T( "typedef struct slmp_%s {\n"
            "    /** Header */ \n"
            "    slmp_cmd_hdr_t hdr; \n\n" ),
        cmd->m_strStructType);
    code += strDeclBegin;

    const CTypedPtrList<CObList, CCommandElement*> &listElem = cmd->m_listElem;
    POSITION pos = listElem.GetHeadPosition();
    while (pos != NULL) {
        CCommandElement *elem = listElem.GetNext(pos);
        CRuntimeClass *clazz = elem->GetRuntimeClass();
        if (clazz == RUNTIME_CLASS(CFieldObject)) {
            CFieldObject *field = (CFieldObject*)(elem);
            if (cmd->m_bAddrLenDep) {
                AppendFieldDeclAddrLenDep(field, code, uIndent + 1);
            }
            else {
                AppendFieldDeclAddrLenIndep(field, code, uIndent + 1);
            }
        }
        else if (clazz == RUNTIME_CLASS(CGroupObject)) {
            CGroupObject *group = (CGroupObject*)(elem);
            if (!group->m_strName.IsEmpty()) {
                CString strComment;
                strComment.Format(_T("\\name %s\n@{\n"), group->m_strName);
                code += CommentBlock(strComment, uIndent > 0 ? uIndent - 1 : 0, TRUE);
            }

            const CTypedPtrList<CObList, CFieldObject*> &listField = group->m_listField;
            POSITION lfpos = listField.GetHeadPosition();
            while (lfpos != NULL) {
                CFieldObject *field = listField.GetNext(lfpos);
                if (cmd->m_bAddrLenDep) {
                    AppendFieldDeclAddrLenDep(field, code, uIndent + 1);
                }
                else {
                    AppendFieldDeclAddrLenIndep(field, code, uIndent + 1);
                }
            }

            if (!group->m_strName.IsEmpty()) {
                code += CommentBlock(_T("@}\n"), uIndent > 0 ? uIndent - 1 : 0, TRUE);
            }
        }
    }

    CString strDeclEnd;
    strDeclEnd.Format(_T("} slmp_%s_t;\n"), cmd->m_strStructType);
    code += strDeclEnd;
}

void CCodeGenerator::AppendFieldDeclAddrLenIndep(const CFieldObject* field, CString& code, UINT uIndent)
{
    if (!field->m_strBrief.IsEmpty()) {
        code += CommentBlock(field->m_strBrief, uIndent, TRUE);
    }
    else {
        code += _T("\n");
    }

    if (!field->m_bVarSize) {
        switch (field->m_avail) {
        case 0: // Binary only
            AppendVarDecl(field->m_strName, code, field->m_sizeBin16B, 
                field->m_bStringBin16B, uIndent);
            break;
        case 1: // ASCII only
            AppendVarDecl(field->m_strName, code, field->m_sizeAsc16B, 
                field->m_bStringAsc16B, uIndent);
            break;
        case 2: // Both binary and ASCII
            AppendUnionDecl(field->m_strName, code, _T("bin"), _T("ascii"), field->m_sizeBin16B,
                field->m_sizeAsc16B, field->m_bStringBin16B, field->m_bStringAsc16B, uIndent,
                TRUE);
            break;
        default:
            break;
        }
    }
    else {
        if ((field->m_bSizeField) && !(field->m_strSizeField.IsEmpty())) {
            CString strDecl;
            strDecl.Format(_T("uint8_t *%s; /* (size = '%s') */\n"),
                field->m_strName, field->m_strSizeField);
            code += IndentLine(strDecl, uIndent);
        }
        else {
            AppendVarDecl(field->m_strName, code, -1, field->m_bStringVarSize, uIndent);
        }
    }
}

void CCodeGenerator::AppendFieldDeclAddrLenDep(const CFieldObject* field, CString& code, UINT uIndent)
{
    if (!field->m_strBrief.IsEmpty()) {
        code += CommentBlock(field->m_strBrief, uIndent, TRUE);
    }
    else {
        code += _T("\n");
    }

    int avail = field->m_avail;

    if (!field->m_bVarSize) {
        if ((avail == 0) || (avail == 1)) {
            code += IndentLine(_T("union {\n"), uIndent);
            ++uIndent;
        }

        switch (avail) {
        case 0: // Binary only
            AppendUnionDecl(_T("bin"), code, _T("s"), _T("l"), field->m_sizeBin16B,
                field->m_sizeBin32B, field->m_bStringBin16B, field->m_bStringBin32B, uIndent);
            break;
        case 1: // ASCII only
            AppendUnionDecl(_T("ascii"), code, _T("s"), _T("l"), field->m_sizeAsc16B,
                field->m_sizeAsc32B, field->m_bStringAsc16B, field->m_bStringAsc32B, uIndent);
            break;
        case 2: { // Both binary and ASCII
            bool bIdenticalSize = 
                    (field->m_sizeBin16B == field->m_sizeBin32B)
                &&  (field->m_sizeAsc32B == 2 * field->m_sizeBin32B)
                &&  (field->m_sizeAsc16B == field->m_sizeAsc32B)
                &&  (field->m_sizeAsc16B == 2 * field->m_sizeBin16B);
            bool bIdenticalSizeString = 
                    (field->m_sizeBin16B == field->m_sizeBin32B)
                &&  (field->m_sizeAsc32B == field->m_sizeBin32B)
                &&  (field->m_sizeAsc16B == field->m_sizeAsc32B)
                &&  (field->m_sizeAsc16B == field->m_sizeBin16B);
            bool bAlwaysStringBin = (field->m_bStringBin16B && field->m_bStringBin32B);
            bool bAlwaysStringAsc = (field->m_bStringAsc16B && field->m_bStringAsc32B);
            bool bAlwaysNotStringBin = (!field->m_bStringBin16B && !field->m_bStringBin32B);
            bool bAlwaysNotStringAsc = (!field->m_bStringAsc16B && !field->m_bStringAsc32B);
            if (    (bAlwaysStringBin && bAlwaysStringAsc && bIdenticalSizeString) 
                ||  (bAlwaysNotStringBin && bAlwaysNotStringAsc && bIdenticalSize)  ) 
            {
                AppendVarDecl(field->m_strName, code, field->m_sizeBin16B, field->m_bStringBin16B,
                    uIndent);
            }
            else {
                code += IndentLine(_T("union {\n"), uIndent);
                ++uIndent;

                AppendUnionDecl(_T("bin"), code, _T("s"), _T("l"), field->m_sizeBin16B,
                    field->m_sizeBin32B, field->m_bStringBin16B, field->m_bStringBin32B, uIndent,
                    FALSE);
                AppendUnionDecl(_T("ascii"), code, _T("s"), _T("l"), field->m_sizeAsc16B,
                    field->m_sizeAsc32B, field->m_bStringAsc16B, field->m_bStringAsc32B, uIndent,
                    FALSE);

                CString strDeclEnd;
                strDeclEnd.Format(_T("} %s;\n"), field->m_strName);
                --uIndent;
                code += IndentLine(strDeclEnd, uIndent);
            }
        }   break;
        default:
            break;
        }

        if ((avail == 0) || (avail == 1)) {
            CString strDeclEnd;
            strDeclEnd.Format(_T("} %s;\n"), field->m_strName);
            --uIndent;
            code += IndentLine(strDeclEnd, uIndent);
        }
    }
    else {
        if ((field->m_bSizeField) && !(field->m_strSizeField.IsEmpty())) {
            CString strDecl;
            strDecl.Format(_T("uint8_t *%s; /* (size = '%s') */\n"),
                field->m_strName, field->m_strSizeField);
            code += IndentLine(strDecl, uIndent);
        }
        else {
            AppendVarDecl(field->m_strName, code, -1, field->m_bStringVarSize, uIndent);
        }
    }
}

void CCodeGenerator::AppendVarDecl(const CString& name, CString& code, int size, BOOL bString, UINT uIndent)
{
    CString strDecl;

    if (bString) {
        if (size <= 0) {
            strDecl.Format(_T("uint8_t %s[1]; /* string (variable size) */\n"), name);
        }
        else {
            strDecl.Format(_T("uint8_t %s[%d]; /* string */\n"), name, size);
        }
    }
    else if (size <= 0) {
        strDecl.Format(_T("uint8_t %s[1]; /* variable size */\n"), name);
    }
    else {
        switch (size) {
        case 1:
            strDecl.Format(_T("uint8_t %s;\n"), name);
            break;
        case 2:
            strDecl.Format(_T("uint16_t %s;\n"), name);
            break;
        case 3:
            strDecl.Format(_T("uint32_t %s; /* 24b */\n"), name);
            break;
        case 4:
            strDecl.Format(_T("uint32_t %s; /* 32b */\n"), name);
            break;
        default:
            strDecl.Format(_T("uint8_t %s[%d];\n"), name, size);
            break;
        }
    }

    code += IndentLine(strDecl, uIndent);
}

void CCodeGenerator::AppendUnionDecl(const CString& unionName, CString& code, const CString& name1, 
    const CString& name2, UINT size1, UINT size2, BOOL bString1, BOOL bString2, UINT uIndent,
    BOOL bBoth)
{
    bool bIdenticalSize = (2 * size1 == size2);
    bool bIdenticalSizeString = (size1 == size2);
    bool bAlwaysString = (bString1 && bString2);
    bool bAlwaysNotString = (!bString1 && !bString2);
    
    if (    bBoth 
        &&
            (   (bIdenticalSizeString && bAlwaysString)
            ||  (bIdenticalSize && bAlwaysNotString)
            )
        )
    {
        AppendVarDecl(unionName, code, size1, bString1, uIndent);
    }
    else if (size1 == size2) {
        AppendVarDecl(unionName, code, size1, bString1, uIndent);
    }
    else {
        code += IndentLine(_T("union {\n"), uIndent);
        ++uIndent;
        
        AppendVarDecl(name1, code, size1, bString1, uIndent);
        AppendVarDecl(name2, code, size2, bString2, uIndent);
        
        CString strDeclEnd;
        strDeclEnd.Format(_T("} %s;\n"), unionName);
        --uIndent;
        code += IndentLine(strDeclEnd, uIndent);
    }
}

void CCodeGenerator::AppendEncodeFcnImpl(const CCommandObject* cmd, CString& code)
{
    BOOL bAddrLenDep = cmd->m_bAddrLenDep;
    CString strStructType;
    strStructType.Format(_T("slmp_%s_t"), cmd->m_strStructType);

    CString strFuncImplBegin;
    strFuncImplBegin.Format(
        _T( "SLMPAPI size_t SLMPCALL slmp_encode_%s(\n"
            "    slmp_cmd_hdr_t *hdr, uint8_t *stream, int type)\n"
            "{ \n" ),
        cmd->m_strStructType);
    code += strFuncImplBegin;

    CString strStmt;
    UINT uIndent = 1;
    
    UINT uSizeBin16B, uSizeAsc16B, uSizeBin32B, uSizeAsc32B;
    GetFixedPartSize(cmd, uSizeBin16B, uSizeAsc16B, uSizeBin32B, uSizeAsc32B);

    CArray<CFieldObject*, CFieldObject*> varSizeFields;
    varSizeFields.SetSize(8);   /* A reasonable value :-P */
    BOOL bAllVarSizeFieldsDeclaredAsPointers = FALSE;
    BOOL bVarSize = GetVariableSizeFields(cmd, &varSizeFields, &bAllVarSizeFieldsDeclaredAsPointers);

    strStmt.Format(_T("ENCODE_COMMAND_DECLARE_LOCAL_VARIABLES(%s); \n"), strStructType);
    code += IndentLine(strStmt, uIndent);

    strStmt.Format(_T("ENCODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(%s, %d); \n\n"), 
        strStructType, (bVarSize && !bAllVarSizeFieldsDeclaredAsPointers) ? 1 : 0);
    code += IndentLine(strStmt, uIndent);

    if (bVarSize) {
        for (int i = 0; i <= varSizeFields.GetUpperBound(); ++i) {
            CFieldObject *field = varSizeFields.ElementAt(i);
            if (field->m_bSizeField && !field->m_strSizeField.IsEmpty()) {
                strStmt.Format(_T("var_part_size += (size_t)(cmd->%s); \n"), 
                    field->m_strSizeField);
                code += IndentLine(strStmt, uIndent);
            }
        }

        strStmt.Format(
            _T( "ENCODE_COMMAND_SET_MIN_BUF_SIZE( \n"
                "    %u + var_part_size, \n"
                "    %u + var_part_size, \n"
                "    %u + var_part_size, \n"
                "    %u + var_part_size \n"
                "); \n\n" ),
            uSizeBin16B, uSizeBin32B, uSizeAsc16B, uSizeAsc32B);
        code += IndentBlock(strStmt, uIndent);
    }
    else {
        strStmt.Format(
            _T( "ENCODE_COMMAND_SET_MIN_BUF_SIZE(%u, %u, %u, %u); \n\n" ),
            uSizeBin16B, uSizeBin32B, uSizeAsc16B, uSizeAsc32B);
        code += IndentBlock(strStmt, uIndent);
    }

    code += IndentBlock(
        _T( "if (stream == NULL) { \n"
            "    return min_buf_size; \n"
            "} \n\n" ), 
        uIndent);


    if ((cmd->m_supportedStreamType == 0) || (cmd->m_supportedStreamType == 2)) {
        code += IndentLine(_T("if (type == SLMP_BINARY_STREAM) { \n"), uIndent);
        AppendCodecStatements(cmd, code, uIndent + 1, Binary, bAddrLenDep, FALSE);
        code += IndentLine(_T("} \n"), uIndent);
    }

    if (cmd->m_supportedStreamType == 2) {
        code += IndentLine(_T("else "), uIndent);
    }
    else if (cmd->m_supportedStreamType == 1) {
        code += _T("    ");
    }

    if ((cmd->m_supportedStreamType == 1) || (cmd->m_supportedStreamType == 2)) {
        code += _T("if (type == SLMP_ASCII_STREAM) { \n");
        AppendCodecStatements(cmd, code, uIndent + 1, ASCII, bAddrLenDep, FALSE);
        code += IndentLine(_T("} \n"), uIndent);
    }

    code += _T("\n");
    code += IndentLine(_T("return min_buf_size; \n"), uIndent);

    code += _T("}\n\n");
}

void CCodeGenerator::AppendDecodeFcnImpl(const CCommandObject* cmd, CString& code)
{
    BOOL bAddrLenDep = cmd->m_bAddrLenDep;
    CString strStructType;
    strStructType.Format(_T("slmp_%s_t"), cmd->m_strStructType);

    CString strFuncImplBegin;
    strFuncImplBegin.Format(
        _T( "SLMPAPI slmp_cmd_hdr_t* SLMPCALL slmp_decode_%s( \n"
            "    uint8_t *stream, size_t len, int type, int addr_width) \n"
            "{ \n" ),
        cmd->m_strStructType);
    code += strFuncImplBegin;

    CString strStmt;
    UINT uIndent = 1;
    
    UINT uSizeBin16B, uSizeAsc16B, uSizeBin32B, uSizeAsc32B;
    GetFixedPartSize(cmd, uSizeBin16B, uSizeAsc16B, uSizeBin32B, uSizeAsc32B);

    strStmt.Format(
        _T( "DECODE_COMMAND_DECLARE_LOCAL_VARIABLES(%s); \n"
            "DECODE_COMMAND_INITIALIZE_LOCAL_VARIABLES(); \n" 
            "DECODE_COMMAND_CHECK_STREAM_LENGTH(%u, %u, %u, %u); \n"
            "DECODE_COMMAND_ALLOC_MEMORY(%s); \n"
            "DECODE_COMMAND_FILL_COMMAND_HEADER(%s); \n\n"),
        strStructType,
        uSizeBin16B, uSizeBin32B, uSizeAsc16B, uSizeAsc32B,
        strStructType,
        strStructType);
    code += IndentBlock(strStmt, uIndent);

    if ((cmd->m_supportedStreamType == 0) || (cmd->m_supportedStreamType == 2)) {
        code += IndentLine(_T("if (type == SLMP_BINARY_STREAM) { \n"), uIndent);
        AppendCodecStatements(cmd, code, uIndent + 1, Binary, bAddrLenDep, TRUE);
        code += IndentLine(_T("} \n"), uIndent);
    }

    if (cmd->m_supportedStreamType == 2) {
        code += IndentLine(_T("else "), uIndent);
    }
    else if (cmd->m_supportedStreamType == 1) {
        code += _T("    ");
    }

    if ((cmd->m_supportedStreamType == 1) || (cmd->m_supportedStreamType == 2)) {
        code += _T("if (type == SLMP_ASCII_STREAM) { \n");
        AppendCodecStatements(cmd, code, uIndent + 1, ASCII, bAddrLenDep, TRUE);
        code += IndentLine(_T("} \n"), uIndent);
    }

    code += _T("\n");
    code += IndentLine(_T("return &(cmd->hdr); \n"), uIndent);

    code += _T("}\n\n");
}

BOOL CCodeGenerator::GetVariableSizeFields(const CCommandObject* cmd, CArray<CFieldObject*, CFieldObject*>* fields,
    BOOL *pbAllDeclaredAsPointers)
{
    BOOL bContain = FALSE, bHasNonPointer = FALSE;
    const CTypedPtrList<CObList, CCommandElement*> &listElem = cmd->m_listElem;
    
    if (fields) {
        fields->RemoveAll();
    }

    POSITION pos = listElem.GetHeadPosition();
    while (pos != NULL) {
        CCommandElement *elem = listElem.GetNext(pos);
        CRuntimeClass *clazz = elem->GetRuntimeClass();

        if (clazz == RUNTIME_CLASS(CFieldObject)) {
            CFieldObject *field = (CFieldObject*)(elem);
            if (field->m_bVarSize) {
                bContain = TRUE;

                if (fields) {
                    fields->Add(field);
                }

                if ((!field->m_bSizeField) || (field->m_strSizeField.GetLength() == 0)) {
                    bHasNonPointer = TRUE;
                }
            }
        }
        else if (clazz == RUNTIME_CLASS(CGroupObject)) {
            CGroupObject *group = (CGroupObject*)(elem);
            CTypedPtrList<CObList, CFieldObject*> &listField = group->m_listField;
            POSITION lfpos = listField.GetHeadPosition();
            while (lfpos != NULL) {
                CFieldObject *field = listField.GetNext(lfpos);
                if (field->m_bVarSize) {
                    bContain = TRUE;

                    if ((!field->m_bSizeField) || (field->m_strSizeField.GetLength() == 0)) {
                        bHasNonPointer = TRUE;
                    }
                }
            }
        }
    }

    if (pbAllDeclaredAsPointers) {
        *pbAllDeclaredAsPointers = !bHasNonPointer;
    }

    return bContain;
}

void CCodeGenerator::GetFixedPartSize(const CCommandObject* cmd, UINT& uSizeBin16B, UINT& uSizeAsc16B,
    UINT& uSizeBin32B, UINT& uSizeAsc32B)
{
    uSizeBin16B = uSizeAsc16B = uSizeBin32B = uSizeAsc32B = 0;

    const CTypedPtrList<CObList, CCommandElement*> &listElem = cmd->m_listElem;
    POSITION pos = listElem.GetHeadPosition();
    while (pos != NULL) {
        CCommandElement *elem = listElem.GetNext(pos);
        CRuntimeClass *clazz = elem->GetRuntimeClass();
        if (clazz == RUNTIME_CLASS(CFieldObject)) {
            CFieldObject *field = (CFieldObject*)(elem);
            if (!field->m_bVarSize) {
                int avail =  field->m_avail;
                
                if (avail != 1 /* ASCII only */) {
                    uSizeBin16B += field->m_sizeBin16B;
                    uSizeBin32B += field->m_sizeBin32B;
                }

                if (avail != 0 /* Binary only */) {
                    uSizeAsc16B += field->m_sizeAsc16B;
                    uSizeAsc32B += field->m_sizeAsc32B;
                }
            }
        }
        else if (clazz == RUNTIME_CLASS(CGroupObject)) {
            CGroupObject *group = (CGroupObject*)(elem);
            CTypedPtrList<CObList, CFieldObject*> &listField = group->m_listField;
            POSITION lfpos = listField.GetHeadPosition();
            while (lfpos != NULL) {
                CFieldObject *field = listField.GetNext(lfpos);
                if (!field->m_bVarSize) {
                    int avail =  field->m_avail;
                
                    if (avail != 1 /* ASCII only */) {
                        uSizeBin16B += field->m_sizeBin16B;
                        uSizeBin32B += field->m_sizeBin32B;
                    }

                    if (avail != 0 /* Binary only */) {
                        uSizeAsc16B += field->m_sizeAsc16B;
                        uSizeAsc32B += field->m_sizeAsc32B;
                    }
                }
            }
        }
    }

    if (!cmd->m_bAddrLenDep) {
        uSizeAsc32B = uSizeAsc16B;
        uSizeBin32B = uSizeBin16B;
    }
}

void CCodeGenerator::GetFieldAccessExpr(const CFieldObject* field, CString& strExpr, 
    int& fieldLen, const CString& grpName, StreamType strmType, AddressLength addrLen,
    BOOL bGlobalAddrLenUnaware)
{
    strExpr = _T("cmd->");
    if (!grpName.IsEmpty()) {
        strExpr += (grpName + _T('.'));
    }
    strExpr += field->m_strName;

    if (!field->m_bVarSize) {
        switch (field->m_avail) {
        case 0: // Binary only
            ASSERT(strmType == Binary);
            if ((strmType == Binary) && !bGlobalAddrLenUnaware) {
                strExpr += _T(".bin");
            }
            break;
        case 1: // ASCII only
            ASSERT(strmType == ASCII);
            if ((strmType == ASCII) && !bGlobalAddrLenUnaware) {
                strExpr += _T(".ascii");
            }
            break;
        case 2: { // Both
            if (addrLen != Unaware) {
                bool bIdenticalSize = 
                        (field->m_sizeBin16B == field->m_sizeBin32B)
                    &&  (field->m_sizeAsc32B == 2 * field->m_sizeBin32B)
                    &&  (field->m_sizeAsc16B == field->m_sizeAsc32B)
                    &&  (field->m_sizeAsc16B == 2 * field->m_sizeBin16B);
                bool bIdenticalSizeString = 
                        (field->m_sizeBin16B == field->m_sizeBin32B)
                    &&  (field->m_sizeAsc32B == field->m_sizeBin32B)
                    &&  (field->m_sizeAsc16B == field->m_sizeAsc32B)
                    &&  (field->m_sizeAsc16B == field->m_sizeBin16B);
                bool bAlwaysStringBin = (field->m_bStringBin16B && field->m_bStringBin32B);
                bool bAlwaysStringAsc = (field->m_bStringAsc16B && field->m_bStringAsc32B);
                bool bAlwaysNotStringBin = (!field->m_bStringBin16B && !field->m_bStringBin32B);
                bool bAlwaysNotStringAsc = (!field->m_bStringAsc16B && !field->m_bStringAsc32B);
                if (    (bAlwaysStringBin && bAlwaysStringAsc && bIdenticalSizeString) 
                    ||  (bAlwaysNotStringBin && bAlwaysNotStringAsc && bIdenticalSize)    ) 
                {
                    fieldLen = field->m_sizeBin16B;
                    return;
                }
            }
            else {
                bool bIdenticalSize = (field->m_sizeAsc16B == 2 * field->m_sizeBin16B);
                bool bIdenticalSizeString = (field->m_sizeAsc16B == field->m_sizeBin16B);
                bool bAlwaysString = (field->m_bStringAsc16B && field->m_bStringBin16B);
                bool bAlwaysNotString = (!field->m_bStringAsc16B && !field->m_bStringBin16B);
                if (    (bIdenticalSize && bAlwaysNotString) 
                    ||  (bIdenticalSizeString && bAlwaysString) ) 
                {
                    fieldLen = field->m_sizeBin16B;
                    return;
                }
            }
        }    break;
        default:
            break;
        }

        switch (strmType) {
        case Binary:
            switch (addrLen) {
            case AddressLength16B:
            case Unaware:
                fieldLen = field->m_sizeBin16B;
                break;
            case AddressLength32B:
                fieldLen = field->m_sizeBin32B;
                break;
            default:
                break;
            }
            break;
        case ASCII:
            switch (addrLen) {
            case AddressLength16B:
            case Unaware:
                fieldLen = field->m_sizeAsc16B;
                break;
            case AddressLength32B:
                fieldLen = field->m_sizeAsc32B;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }

        switch (field->m_avail) {
        case 0: /* Binary only */
            if (addrLen == Unaware) {
                fieldLen = field->m_sizeBin16B;
                return;
            }
            else if (field->m_sizeBin16B == field->m_sizeBin32B) {
                return;
            }
            break;
        case 1: /* ASCII only */
            if (addrLen == Unaware) {
                fieldLen = field->m_sizeAsc16B;
                return;
            }
            else if (field->m_sizeAsc16B == field->m_sizeAsc32B) {
                return;
            }
            break;
        case 2: /* Both */
            if (addrLen == Unaware) {
                if (field->m_sizeAsc16B == field->m_sizeBin16B) {
                    return;
                }
            }
            
            switch (strmType) {
            case Binary:
                strExpr += _T(".bin");
                if ((addrLen != Unaware) && (field->m_sizeBin16B == field->m_sizeBin32B)) {
                    return;
                }
                break;
            case ASCII:
                strExpr += _T(".ascii");
                if ((addrLen != Unaware) && (field->m_sizeAsc16B == field->m_sizeAsc32B)) {
                    return;
                }
                break;
            default:
                break;
            }

            if (addrLen == Unaware) {
                return;
            }
            break;
        default:
            break;
        }

        switch (addrLen) {
        case AddressLength16B:
            strExpr += _T(".s");
            break;
        case AddressLength32B:
            strExpr += _T(".l");
            break;
        default:
            break;
        }
    }
    else {
        fieldLen = -1;
    }
}

void CCodeGenerator::AppendCodecStatements(const CCommandObject* cmd, CString &code, UINT uIndent,
    StreamType strmType, BOOL bAddrLenDep, BOOL bDecode)
{
    UINT uPrevIndent = uIndent;
    if (bAddrLenDep) {
        if (!bDecode) {
            code += IndentBlock(
                _T( "switch (cmd->hdr.addr_width) { \n"
                    "case SLMP_ADDRESS_16BIT: \n" ),
                uIndent);
        }
        else {
            code += IndentBlock(
                _T( "switch (addr_width) { \n"
                    "case SLMP_ADDRESS_16BIT: \n" ),
                uIndent);
        }

        ++uIndent;
    }

    AppendCodecStatements(cmd, code, uIndent, strmType, 
        bAddrLenDep ? AddressLength16B : Unaware, bDecode);

    if (bAddrLenDep) {
        code += IndentLine(_T("break;\n"), uIndent);

        uIndent = uPrevIndent;

        code += IndentBlock(
            _T( "case SLMP_ADDRESS_32BIT: \n"), 
            uIndent);
        ++uIndent;

        AppendCodecStatements(cmd, code, uIndent, strmType, 
            bAddrLenDep ? AddressLength32B : Unaware, bDecode);
        code += IndentLine(_T("break;\n"), uIndent);

        uIndent = uPrevIndent;
        code += IndentBlock(
            _T( "default: \n"
                "    break; \n"
                "} \n" ),
            uIndent);
    }
}

void CCodeGenerator::AppendCodecStatements(const CCommandObject* cmd, CString& code, UINT uIndent,
    StreamType strmType, AddressLength addrLen, BOOL bDecode)
{
    const CTypedPtrList<CObList, CCommandElement*> &listElem = cmd->m_listElem;
    POSITION pos = listElem.GetHeadPosition();
    while (pos != NULL) {
        CCommandElement *elem = listElem.GetNext(pos);
        CRuntimeClass *clazz = elem->GetRuntimeClass();

        if (clazz == RUNTIME_CLASS(CFieldObject)) {
            CFieldObject *field = (CFieldObject*)(elem);
            // code += CommentBlock(field->m_strName, uIndent);
            code += IndentLine(_T("/* ") + field->m_strName + _T(" */ \n"), uIndent);
            AppendFieldCodecStatement(field, code, uIndent, strmType, addrLen, 0, bDecode,
                !cmd->m_bAddrLenDep);
        }
        else if (clazz == RUNTIME_CLASS(CGroupObject)) {
            CGroupObject *group = (CGroupObject*)(elem);
            // code += CommentBlock(group->m_strName, uIndent);
            code += IndentLine(_T("/* ") + group->m_strName + _T(" */ \n"), uIndent);

            const CTypedPtrList<CObList, CFieldObject*> &listField = group->m_listField;
            POSITION lfpos = 
                (strmType == Binary) 
                ? listField.GetTailPosition() 
                : listField.GetHeadPosition();
            while (lfpos != NULL) {
                CFieldObject *field = 
                    (strmType == Binary)
                    ? listField.GetPrev(lfpos)
                    : listField.GetNext(lfpos);
                AppendFieldCodecStatement(field, code, uIndent, strmType, addrLen, 0, bDecode,
                    !cmd->m_bAddrLenDep);
            }
        }
    }
}

void CCodeGenerator::AppendFieldCodecStatement(const CFieldObject* field, CString& code, UINT uIndent,
    StreamType strmType, AddressLength addrLen, UINT uSizeCopy, BOOL bDecode, BOOL bGlobalAddrLenUnaware)
{
    if (    ((field->m_avail == 0) && (strmType == ASCII))
        ||  ((field->m_avail == 1) && (strmType == Binary)) )
    {
        return;
    }

    CString strPrefix;
    if (!bDecode) {
        strPrefix = _T("ENCODE_AND_ADVANCE_STREAM_");
    } else {
        strPrefix = _T("DECODE_AND_ADVANCE_STREAM_");
    }

    CString strFieldExpr;
    int fieldLen;
    GetFieldAccessExpr(field, strFieldExpr, fieldLen, _T(""), strmType, addrLen, bGlobalAddrLenUnaware);

    BOOL bCopyMemory = FALSE;
    if (fieldLen <= 4 && !field->m_bVarSize) {
        if (strmType == Binary) {
            if (addrLen == AddressLength16B || addrLen == Unaware) {
                bCopyMemory = field->m_bStringBin16B;
            }
            else {
                bCopyMemory = field->m_bStringBin32B;
            }
        }
        else if (strmType == ASCII) {
            if (addrLen == AddressLength16B || addrLen == Unaware) {
                bCopyMemory = field->m_bStringAsc16B;
            }
            else {
                bCopyMemory = field->m_bStringAsc32B;
            }
        }
    }
    else {
        bCopyMemory = TRUE;
    }

    CString strStmt;
    CString str;
    if (!bCopyMemory) {
        switch (fieldLen) {
        case 1:
        case 2:
        case 3:
        case 4:
            str.Format(
                ( bDecode ? _T("%dB(&(%s)); \n") : _T("%dB(%s); \n") ),
                8 * fieldLen, strFieldExpr);
            break;
        default:
            break;
        }

        strStmt += (strPrefix + str);
    }
    else if (fieldLen >= 0) {
        str.Format(_T("COPY_MEMORY(&(%s), %d); \n"), strFieldExpr, fieldLen);
        strStmt += (strPrefix + str);
    }
    else {
        if (!field->m_bSizeField || field->m_strSizeField.IsEmpty()) {
            str.Format(_T("COPY_MEMORY(&(%s), var_part_size); \n"), strFieldExpr);
            strStmt += (strPrefix + str);
        }
        else if (!bDecode) {    /* Encode */
            strStmt.Format(_T("ENCODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(%s, cmd->%s); \n"),
                strFieldExpr, field->m_strSizeField);
        }
        else {  /* Decode */
            strStmt.Format(_T("DECODE_AND_ADVANCE_STREAM_COPY_MEMORY_N(%s, cmd->%s); \n"),
                strFieldExpr, field->m_strSizeField);
        }
    }

    code += IndentBlock(strStmt, uIndent);
}
