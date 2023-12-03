#include "stdafx.h"
#include "RegUtil.h"

BOOL RegUtil::CreateKey(HKEY hRootKey, LPCTSTR lpszSubkey)
{
    LONG lResult;
    HKEY hKey;
    DWORD dwDispos;

    lResult = RegCreateKeyEx(hRootKey, lpszSubkey, 0, NULL, 
        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDispos);
    if (lResult != ERROR_SUCCESS) {
        return FALSE;
    }

    RegCloseKey(hKey);
    return TRUE;
}

BOOL RegUtil::DeleteKey(HKEY hRootKey, LPCTSTR lpszSubkey)
{
    BOOL bRet = TRUE;
    LONG lResult;
    HKEY hKey;
    
    lResult = RegDeleteKey(hRootKey, lpszSubkey);
    if (lResult == ERROR_SUCCESS) {
        return TRUE;
    }

    lResult = RegOpenKeyEx(hRootKey, lpszSubkey, 0, KEY_READ, &hKey);
    if (lResult != ERROR_SUCCESS) {
        return FALSE;
    }

    const int cbMaxName = 256;
    TCHAR szSubkeyName[cbMaxName];
    DWORD cbSubkeyName;
    FILETIME ftLastWriteTime;
    
    while (true) {
        cbSubkeyName = cbMaxName;
        lResult = RegEnumKeyEx(hKey, 0, szSubkeyName, &cbSubkeyName, NULL, 
            NULL, NULL, &ftLastWriteTime);
        if (lResult == ERROR_NO_MORE_ITEMS) {
            break;
        }

        if (!DeleteKey(hKey, szSubkeyName)) {
            bRet = FALSE;
            break;
        }
    } 

    if (bRet) {
        RegDeleteKey(hRootKey, lpszSubkey);
    }
    
    return bRet;
}

BOOL RegUtil::SetValue(HKEY hRootKey, LPCTSTR lpszSubkey, LPCTSTR lpszValueName, 
    DWORD dwType, const BYTE* lpData, DWORD cbData)
{
    BOOL bRet = FALSE;
    LONG lResult;
    HKEY hKey;
    DWORD dwDispos;

    do {
        lResult = RegCreateKeyEx(hRootKey, lpszSubkey, 0, NULL, 
            REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDispos);
        if (lResult != ERROR_SUCCESS) {
            break;
        }

        lResult = RegSetValueEx(hKey, lpszValueName, 0, dwType, lpData, cbData);
        if (lResult != ERROR_SUCCESS) {
            break;
        }

        bRet = TRUE;
    } while (false);

    RegCloseKey(hKey);

    return bRet;
}

BOOL RegUtil::DeleteValue(HKEY hRootKey, LPCTSTR lpszSubkey, LPCTSTR lpszValueName)
{
    BOOL bRet = FALSE;
    LONG lResult;
    HKEY hKey;
    DWORD dwDispos;

    do {
        lResult = RegCreateKeyEx(hRootKey, lpszSubkey, 0, NULL, 
            REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDispos);
        if (lResult != ERROR_SUCCESS) {
            break;
        }

        lResult = RegDeleteValue(hKey, lpszValueName);
        if (lResult != ERROR_SUCCESS) {
            break;
        }

        bRet = TRUE;
    } while (false);

    RegCloseKey(hKey);

    return bRet;
}
