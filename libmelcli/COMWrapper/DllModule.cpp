// DllModule.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "DllModule.h"
#include "Factory.h"
#include "MelcliCOMWrapper.h"
#include "RegUtil.h"
#include "StrUtil.h"

static const TCHAR gs_pszMapObjectName[] 
    = TEXT("MelcliCOMWrapperDllGlobalSharedData");
static LPCTSTR gs_lpszThreadingModel = "Apartment";
static LPCTSTR gs_lpszDesc = "Neucrede's MELSEC Client Component";
static LPCTSTR gs_lpszProgId = "Neucrede.MELSECClient";
static LPCTSTR gs_lpszProgIdWithVer = "Neucrede.MELSECClient.1.0";
static LPCTSTR gs_lpszAppId = "{BB9C2540-7AE5-4C1B-A8F1-B9BF87EEFF01}";

DllData* g_pDllData = NULL;
DllGlobalSharedData* g_pDllGlobalSharedData = NULL;


BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
    BOOL bRet = TRUE;

    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        bRet = FALSE;
        g_pDllData = new DllData;
        do {
            if (!g_pDllData) break;

            memset(g_pDllData, 0, sizeof(DllData));
            g_pDllData->hModule = hModule;

            DWORD dwSizeSharedData = sizeof(DllGlobalSharedData);
            
            HANDLE hMap;
            /* Backed by paging file. */
            g_pDllData->hMap = hMap = CreateFileMapping((HANDLE)(-1), 
                NULL, PAGE_READWRITE, 0, dwSizeSharedData, 
                gs_pszMapObjectName);
            if (!hMap) break;

            bool bInit = (GetLastError() != ERROR_ALREADY_EXISTS);
            g_pDllGlobalSharedData = (DllGlobalSharedData*)MapViewOfFile(
                hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
            if (!g_pDllGlobalSharedData) break;

            if (bInit) {
                memset(g_pDllGlobalSharedData, 0, dwSizeSharedData);
                g_pDllGlobalSharedData->dwUseCount = 1;
            }
            else {
                InterlockedIncrement((LPLONG)(&g_pDllGlobalSharedData->dwUseCount));
            }

            bRet = TRUE;
        } while (FALSE);
        break;
    case DLL_PROCESS_DETACH:
        UnmapViewOfFile(g_pDllGlobalSharedData);
        CloseHandle(g_pDllData->hMap);
        delete g_pDllData;
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    default:
        break;
    }

    UNREFERENCED_PARAMETER(lpReserved);
    return bRet;
}

STDAPI DllRegisterServer()
{
	HRESULT hr = SELFREG_E_CLASS;
	LPOLESTR pstr;
	char sBuf[256], sBuf2[256];

	StringFromCLSID(CLSID_MELSECClient, &pstr);
	LPSTR lpszCLSID = StrUtil::WideCharToMultiByte(pstr);
	CoTaskMemFree(pstr);
	
	do {
		sprintf(sBuf, "CLSID\\%s", lpszCLSID);
		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, NULL, REG_SZ,
			(const BYTE*)gs_lpszDesc, strlen(gs_lpszDesc) + 1))
		{
			break;
		}

        if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, "AppID", REG_SZ,
			(const BYTE*)gs_lpszAppId, strlen(gs_lpszAppId) + 1))
		{
			break;
		}

		sprintf(sBuf, "CLSID\\%s\\InprocServer32", lpszCLSID);
		GetModuleFileName((HMODULE)(g_pDllData->hModule), sBuf2, sizeof(sBuf2));
		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, NULL, REG_SZ,
			(const BYTE*)sBuf2, strlen(sBuf2) + 1))
		{
			break;
		}

        if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, "ThreadingModel", REG_SZ,
			(const BYTE*)gs_lpszThreadingModel, strlen(gs_lpszThreadingModel) + 1))
		{
			break;
		}

		sprintf(sBuf, "CLSID\\%s\\ProgID", lpszCLSID);
		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, NULL, REG_SZ,
			(const BYTE*)gs_lpszProgIdWithVer, strlen(gs_lpszProgIdWithVer) + 1))
		{
			break;
		}

		sprintf(sBuf, "CLSID\\%s\\VersionIndependentProgID", lpszCLSID);
		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, NULL, REG_SZ,
			(const BYTE*)gs_lpszProgId, strlen(gs_lpszProgId) + 1))
		{
			break;
		}

		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, gs_lpszProgId, NULL, REG_SZ,
			(const BYTE*)gs_lpszDesc, strlen(gs_lpszDesc) + 1))
		{
			break;
		}

		sprintf(sBuf, "%s\\CLSID", gs_lpszProgId);
		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, NULL, REG_SZ,
			(const BYTE*)lpszCLSID, strlen(lpszCLSID) + 1))
		{
			break;
		}

		sprintf(sBuf, "%s\\CurVer", gs_lpszProgId);
		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, NULL, REG_SZ,
			(const BYTE*)gs_lpszProgIdWithVer, strlen(gs_lpszProgIdWithVer) + 1))
		{
			break;
		}

		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, gs_lpszProgIdWithVer, NULL, REG_SZ,
			(const BYTE*)gs_lpszDesc, strlen(gs_lpszDesc) + 1))
		{
			break;
		}

		sprintf(sBuf, "%s\\CLSID", gs_lpszProgIdWithVer);
		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, NULL, REG_SZ,
			(const BYTE*)lpszCLSID, strlen(lpszCLSID) + 1))
		{
			break;
		}

		sprintf(sBuf, "AppID\\%s", gs_lpszAppId);
		if (!RegUtil::SetValue(HKEY_CLASSES_ROOT, sBuf, "DllSurrogate", REG_SZ,
            (const BYTE*)"\x0", 1))
		{
			break;
		}

		hr = S_OK;
	} while (false);

	delete lpszCLSID;
	if (FAILED(hr)) {
		return hr;
	}
    
	OleInitialize(NULL);
	IMELSECClientContext *pCtx;
	hr = CoCreateInstance(CLSID_MELSECClient, NULL, CLSCTX_INPROC_SERVER,
		IID_IMELSECClientContext, (LPVOID*)&pCtx);
	if (SUCCEEDED(hr)) {
		pCtx->Release();
	}
	OleUninitialize();
    
    return hr;
}

STDAPI DllUnregisterServer()
{
    LPOLESTR pstr;
    char sBuf[256];

    StringFromCLSID(CLSID_MELSECClient, &pstr);
    LPSTR lpszCLSID = StrUtil::WideCharToMultiByte(pstr);
    CoTaskMemFree(pstr);

    sprintf(sBuf, "CLSID\\%s", lpszCLSID);
    RegUtil::DeleteKey(HKEY_CLASSES_ROOT, sBuf);

    sprintf(sBuf, "AppID\\%s", gs_lpszAppId);
    RegUtil::DeleteKey(HKEY_CLASSES_ROOT, sBuf);

    RegUtil::DeleteKey(HKEY_CLASSES_ROOT, gs_lpszProgId);

    RegUtil::DeleteKey(HKEY_CLASSES_ROOT, gs_lpszProgIdWithVer);

    return S_OK;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{    
    if (rclsid != CLSID_MELSECClient) {
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    Factory *pFactory = new Factory();
    if (pFactory == NULL) {
        return E_OUTOFMEMORY;
    }

    return pFactory->QueryInterface(riid, ppv);
}

STDAPI DllCanUnloadNow()
{
    return 
        ((g_pDllData->cLock == 0) && (g_pDllData->cComponent == 0))
        ? S_OK : S_FALSE;
}
