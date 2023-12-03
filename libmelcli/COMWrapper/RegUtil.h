#ifndef __REGUTIL_H__
#define __REGUTIL_H__

#include <windows.h>

namespace RegUtil
{
    BOOL CreateKey(HKEY hRootKey, LPCTSTR lpszSubkey);
    BOOL DeleteKey(HKEY hRootKey, LPCTSTR lpszSubkey);
    BOOL SetValue(HKEY hRootKey, LPCTSTR lpszSubkey, LPCTSTR lpszValueName,
        DWORD dwType, const BYTE *lpData, DWORD cbData);
    BOOL DeleteValue(HKEY hRootKey, LPCTSTR lpszSubkey, LPCTSTR lpszValueName);
};

#endif /* __REGUTIL_H__ */