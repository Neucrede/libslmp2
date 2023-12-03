#include "stdafx.h"
#include "StrUtil.h"

LPWSTR StrUtil::MultiByteToWideChar(LPCSTR sz)
{
	int cchWide = ::MultiByteToWideChar(CP_ACP, 0, sz, -1, NULL, 0);
	LPWSTR wszWide = new WCHAR[cchWide];
	::MultiByteToWideChar(CP_ACP, 0, sz, -1, wszWide,
		cchWide);
	return wszWide;
}

LPSTR StrUtil::WideCharToMultiByte(LPWSTR wsz)
{
	int cchMB = ::WideCharToMultiByte(CP_ACP, 0, wsz, -1, NULL, 0, NULL, NULL);
	LPSTR szMB = new CHAR[cchMB];
	::WideCharToMultiByte(CP_ACP, 0, wsz, -1, szMB, cchMB, NULL, NULL);
	return szMB;
}

