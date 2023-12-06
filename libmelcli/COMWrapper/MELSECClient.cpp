#include "stdafx.h"
#include "MELSECClient.h"
#include "DllModule.h"

extern DllData* g_pDllData;

/* MELSECClient **************************************************************/

MELSECClient::MELSECClient(IUnknown* pUnkOuter)
{
    m_cRef = 0;
    m_pUnkOuter = pUnkOuter;

    m_impl = new Impl(this, pUnkOuter);
    m_supportErrorInfoImpl = new SupportErrorInfoImpl(this, pUnkOuter);
}

MELSECClient::~MELSECClient()
{
    delete m_impl;
    delete m_supportErrorInfoImpl;

    InterlockedDecrement((LPLONG)&(g_pDllData->cComponent));
}

HRESULT MELSECClient::Init()
{
    HRESULT hr = m_impl->Init();

    if (SUCCEEDED(hr)) {
        InterlockedIncrement((LPLONG)&(g_pDllData->cComponent));
    }

    return hr;
}

STDMETHODIMP MELSECClient::QueryInterface(REFIID riid, LPVOID* ppv)
{
    if (riid == IID_IUnknown) {
        this->AddRef();
        *ppv = this;
    }
    else if ((riid == IID_IMELSECClientContext) || (riid == IID_IDispatch)) {
        m_impl->AddRef();
        *ppv = m_impl;
    }
    else if (riid == IID_ISupportErrorInfo) {
        m_supportErrorInfoImpl->AddRef();
        *ppv = m_supportErrorInfoImpl;
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    return S_OK;
}

STDMETHODIMP_(ULONG) MELSECClient::AddRef()
{
    return InterlockedIncrement((LPLONG)&m_cRef);
}

STDMETHODIMP_(ULONG) MELSECClient::Release()
{
    ULONG cRef = InterlockedDecrement((LPLONG)&m_cRef);
    if (cRef == 0) {
        delete this;
    }

    return cRef;
}

/* MELSECClient::SupportErrorInfoImpl ****************************************/

MELSECClient::SupportErrorInfoImpl::SupportErrorInfoImpl(
    MELSECClient* pBackObj, IUnknown* pUnkOuter)
    : m_pBackObj(pBackObj)
{
    m_pUnkOuter = (pUnkOuter != NULL) ? pUnkOuter : pBackObj;
}

MELSECClient::SupportErrorInfoImpl::~SupportErrorInfoImpl()
{
}

STDMETHODIMP MELSECClient::SupportErrorInfoImpl::QueryInterface(
    REFIID riid, LPVOID* ppv)
{
    return m_pUnkOuter->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) MELSECClient::SupportErrorInfoImpl::AddRef()
{
    return m_pUnkOuter->AddRef();
}

STDMETHODIMP_(ULONG) MELSECClient::SupportErrorInfoImpl::Release()
{
    return m_pUnkOuter->Release();
}

STDMETHODIMP MELSECClient::SupportErrorInfoImpl::InterfaceSupportsErrorInfo(
    REFIID riid)
{
    return (riid == IID_IMELSECClientContext) ? S_OK : S_FALSE;
}

/* MELSECClient::Impl ********************************************************/

MELSECClient::Impl::Impl(MELSECClient* pBackObj, IUnknown* pUnkOuter)
    : m_pBackObj(pBackObj), m_pTypeInfo(NULL)
{
    m_pUnkOuter = (pUnkOuter != NULL) ? pUnkOuter : pBackObj;

    m_proto = UDPIP;
    
    m_bstrRemoteIPAddress = SysAllocString(L"");
    m_iRemotePort = 8889;
    
    m_bstrLocalIPAddress = SysAllocString(L"0.0.0.0");
    m_iLocalPort = 0;

    /* MELCLI_CONNECTED_STATION */
    m_bNetworkNumber = 0x00;
    m_bNodeNumber = 0xFF;
    m_iProcNumber = 0x03FF;

    /* MELCLI_TIMEOUT_DEFAULT */
    m_iConnTimeout = 1;
    m_iRecvTimeout = 1;
    m_iFrameTimeout = 500;
    m_iFrameTimer = 5;

    m_pCtx = NULL;
}

MELSECClient::Impl::~Impl()
{
}

HRESULT MELSECClient::Impl::Init()
{
    HRESULT hr = S_OK;
    ITypeLib *pTypeLib;
    LPTSTR pszModuleFileName = new TCHAR[255];
    extern DllData* g_pDllData;
    
    do {
        GetModuleFileName((HMODULE)(g_pDllData->hModule), pszModuleFileName, 255);
        
#ifndef _UNICODE
        LPOLESTR pszModuleFileNameW = StrUtil::MultiByteToWideChar(pszModuleFileName);
        hr = LoadTypeLibEx(pszModuleFileNameW, REGKIND_REGISTER, &pTypeLib);
        delete[] pszModuleFileNameW;
#else
        hr = LoadTypeLibEx(pszModuleFileName, REGKIND_REGISTER, &pTypeLib);
#endif

        if (FAILED(hr)) {
            break;
        }

        hr = pTypeLib->GetTypeInfoOfGuid(IID_IMELSECClientContext, &m_pTypeInfo);
        pTypeLib->Release();
    } while (false);

    delete[] pszModuleFileName;
    return hr;
}

STDMETHODIMP MELSECClient::Impl::QueryInterface(REFIID riid, LPVOID* ppv)
{
    return m_pUnkOuter->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) MELSECClient::Impl::AddRef()
{
    return m_pUnkOuter->AddRef();
}

STDMETHODIMP_(ULONG) MELSECClient::Impl::Release()
{
    return m_pUnkOuter->Release();
}

STDMETHODIMP MELSECClient::Impl::GetTypeInfoCount(
    /* [out] */ UINT *pctinfo)
{
    *pctinfo = 1;
    return S_OK;
}

STDMETHODIMP MELSECClient::Impl::GetTypeInfo(
    /* [in] */ UINT iTInfo,
    /* [in] */ LCID lcid,
    /* [out] */ ITypeInfo **ppTInfo)
{
    switch (iTInfo) {
    case 0:
        m_pTypeInfo->AddRef();
        *ppTInfo = m_pTypeInfo;
        return S_OK;
    default:
        *ppTInfo = NULL;
        return DISP_E_BADINDEX;
    }
}

STDMETHODIMP MELSECClient::Impl::GetIDsOfNames(
    /* [in] */ REFIID riid,
    /* [size_is][in] */ LPOLESTR *rgszNames,
    /* [range][in] */ UINT cNames,
    /* [in] */ LCID lcid,
    /* [size_is][out] */ DISPID *rgDispId)
{
    return m_pTypeInfo->GetIDsOfNames(rgszNames, cNames, rgDispId);
}

STDMETHODIMP MELSECClient::Impl::Invoke(
    /* [annotation][in] */ 
    DISPID dispIdMember,
    /* [annotation][in] */ 
    REFIID riid,
    /* [annotation][in] */ 
    LCID lcid,
    /* [annotation][in] */ 
    WORD wFlags,
    /* [annotation][out][in] */ 
    DISPPARAMS *pDispParams,
    /* [annotation][out] */ 
    VARIANT *pVarResult,
    /* [annotation][out] */ 
    EXCEPINFO *pExcepInfo,
    /* [annotation][out] */ 
    UINT *puArgErr)
{
    SetErrorInfo(0, NULL);
    return m_pTypeInfo->Invoke((IDispatch*)(this), dispIdMember, wFlags,
        pDispParams, pVarResult, pExcepInfo, puArgErr);
}

HRESULT MELSECClient::Impl::get_Protocol(ProtocolType *pProto)
{
    if (pProto == NULL) {
        return E_POINTER;
    }

    *pProto = m_proto;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_Protocol(ProtocolType proto)
{
    m_proto = proto;
    return S_OK;
}

HRESULT MELSECClient::Impl::get_RemoteIPAddress(BSTR * pbstrIPAddress)
{
    if (pbstrIPAddress == NULL) {
        return E_POINTER;
    }

    *pbstrIPAddress = SysAllocString(m_bstrRemoteIPAddress);
    return S_OK;
}

HRESULT MELSECClient::Impl::put_RemoteIPAddress(BSTR bstrIPAddress)
{
    SysFreeString(m_bstrRemoteIPAddress);
    m_bstrRemoteIPAddress = SysAllocString(bstrIPAddress);
    return S_OK;
}

HRESULT MELSECClient::Impl::get_RemotePort(SHORT * piPort)
{
    if (piPort == NULL) {
        return E_POINTER;
    }

    *piPort = m_iRemotePort;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_RemotePort(SHORT iPort)
{
    if (iPort == 0) {
        return E_INVALIDARG;
    }

    m_iRemotePort = iPort;

    return S_OK;
}

HRESULT MELSECClient::Impl::get_LocalIPAddress(BSTR * pbstrIPAddress)
{
    if (pbstrIPAddress == NULL) {
        return E_POINTER;
    }

    *pbstrIPAddress = SysAllocString(m_bstrLocalIPAddress);
    return S_OK;
}

HRESULT MELSECClient::Impl::put_LocalIPAddress(BSTR bstrIPAddress)
{
    SysFreeString(m_bstrLocalIPAddress);
    m_bstrLocalIPAddress = SysAllocString(bstrIPAddress);
    return S_OK;
}

HRESULT MELSECClient::Impl::get_LocalPort(SHORT * piPort)
{
    if (piPort == NULL) {
        return E_POINTER;
    }

    *piPort = m_iLocalPort;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_LocalPort(SHORT iPort)
{
    m_iLocalPort = iPort;
    return S_OK;
}

HRESULT MELSECClient::Impl::get_NetworkNumber(BYTE * pbNetworkNumber)
{
    if (pbNetworkNumber == NULL) {
        return E_POINTER;
    }

    *pbNetworkNumber = m_bNetworkNumber;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_NetworkNumber(BYTE bNetworkNumber)
{
    m_bNetworkNumber = bNetworkNumber;
    return S_OK;
}

HRESULT MELSECClient::Impl::get_NodeNumber(BYTE * pbNodeNumber)
{
    if (pbNodeNumber == NULL) {
        return E_POINTER;
    }

    *pbNodeNumber = m_bNodeNumber;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_NodeNumber(BYTE bNodeNumber)
{
    m_bNodeNumber = bNodeNumber;
    return S_OK;
}

HRESULT MELSECClient::Impl::get_ProcNumber(SHORT * piProcNumber)
{
    if (piProcNumber == NULL) {
        return E_POINTER;
    }

    *piProcNumber = m_iProcNumber;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_ProcNumber(SHORT iProcNumber)
{
    m_iProcNumber = iProcNumber;
    return S_OK;
}

HRESULT MELSECClient::Impl::get_ConnectionTimeout(short * piTimeout)
{
    if (piTimeout == NULL) {
        return E_POINTER;
    }

    *piTimeout = m_iConnTimeout;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_ConnectionTimeout(short iTimeout)
{
    m_iConnTimeout = iTimeout;
    return S_OK;
}

HRESULT MELSECClient::Impl::get_ReceiveTimeout(short * piTimeout)
{
    if (piTimeout == NULL) {
        return E_POINTER;
    }

    *piTimeout = m_iRecvTimeout;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_ReceiveTimeout(short iTimeout)
{
    m_iRecvTimeout = iTimeout;
    return S_OK;
}

HRESULT MELSECClient::Impl::get_FrameTimeout(short * piTimeout)
{
    if (piTimeout == NULL) {
        return E_POINTER;
    }

    *piTimeout = m_iFrameTimeout;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_FrameTimeout(short iTimeout)
{
    m_iFrameTimeout = iTimeout;
    return S_OK;
}

HRESULT MELSECClient::Impl::get_FrameWaitTime(short * piWaitTime)
{
    if (piWaitTime == NULL) {
        return E_POINTER;
    }

    *piWaitTime = m_iFrameTimer * 250;
    return S_OK;
}

HRESULT MELSECClient::Impl::put_FrameWaitTime(short iWaitTime)
{
    if (iWaitTime != 0) {
        short iTimer = iWaitTime / 250;
        if (iTimer <= 0) {
            iTimer = 1;
        }

        m_iFrameTimer = iTimer;
    }
    else {
        m_iFrameTimer = 0;
    }

    return S_OK;
}

HRESULT MELSECClient::Impl::Connect(VARIANT_BOOL * pbSuccess)
{
    HRESULT hr = S_OK;

    if (pbSuccess == NULL) {
        return E_POINTER;
    }

    if (m_pCtx != NULL) {
        Disconnect();
    }

    LPSTR lpszRemoteIPAddr = StrUtil::WideCharToMultiByte(m_bstrRemoteIPAddress);
    LPSTR lpszLocalIPAddr = StrUtil::WideCharToMultiByte(m_bstrLocalIPAddress);
    melcli_station_t station = { m_bNetworkNumber, m_bNodeNumber, (uint16_t)m_iProcNumber, 0, 0 };
    melcli_timeout_t timeout 
        = { m_iConnTimeout, m_iRecvTimeout, m_iFrameTimeout, m_iFrameTimer };
    m_pCtx = melcli_new_context(m_proto, lpszRemoteIPAddr, m_iRemotePort,
        lpszLocalIPAddr, m_iLocalPort, &station, &timeout);
    delete lpszRemoteIPAddr;
    delete lpszLocalIPAddr;

    if (m_pCtx == NULL) {
        *pbSuccess = VARIANT_FALSE;
        return S_FALSE;
    }

    int err = melcli_connect(m_pCtx);
    if (err == MELCLI_ERROR_SUCCESS) {
        *pbSuccess = VARIANT_TRUE;
    }
    else {
        Disconnect();
        *pbSuccess = VARIANT_FALSE;

        if (err != MELCLI_ERROR_CONNECT_FAILED) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
        }
    }

    return hr;
}

HRESULT MELSECClient::Impl::Disconnect(void)
{
    if (m_pCtx == NULL) {
        return S_OK;
    }

    melcli_free_context(m_pCtx);
    m_pCtx = NULL;

    return S_OK;
}

HRESULT MELSECClient::Impl::BatchReadBit(BSTR bstrAddress, short cUnitCount, 
    SAFEARRAY ** pparrValues)
{
    HRESULT hr = S_FALSE;
    LPSTR lpszAddr = NULL;
    int err;
    char *data = NULL;
    int cDataLen;
    SAFEARRAY *psa = NULL;

    if (cUnitCount <= 0) {
        return E_INVALIDARG;
    }

    if (pparrValues == NULL) {
        return E_POINTER;
    }

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        lpszAddr = StrUtil::WideCharToMultiByte(bstrAddress);
        err = melcli_batch_read(m_pCtx, NULL, lpszAddr, cUnitCount, &data, &cDataLen);
        if (err != MELCLI_ERROR_SUCCESS) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
            break;
        }

        SAFEARRAYBOUND rgsaBound[1];
        rgsaBound[0].lLbound = 0;
        rgsaBound[0].cElements = cUnitCount;

        psa = SafeArrayCreate(VT_BOOL, 1, rgsaBound);
        if (psa == NULL) {
            hr = E_OUTOFMEMORY;
            break;
        }

        char *pArrData;
        if (FAILED(hr = SafeArrayAccessData(psa, (void**)&pArrData))) {
            break;
        }

        do {
            VARIANT_BOOL *pvbData = new VARIANT_BOOL[cUnitCount];
            if (pvbData == NULL) {
                hr = E_OUTOFMEMORY;
                break;
            }

            for (int i = 0; i != cUnitCount; ++i) {
                pvbData[i] = (data[i] != 0) ? VARIANT_TRUE : VARIANT_FALSE;
            }

            memcpy(pArrData, pvbData, cUnitCount * sizeof(VARIANT_BOOL));
            delete[] pvbData;

            *pparrValues = psa;
        } while (false);

        SafeArrayUnaccessData(psa);

        hr = S_OK;
    } while (false);

    if (psa && FAILED(hr)) {
        SafeArrayDestroy(psa);
    }

    melcli_free(data);
    delete lpszAddr;
    return hr;
}

HRESULT MELSECClient::Impl::BatchReadWord(BSTR bstrAddress, short cUnitCount,
    SAFEARRAY ** pparrValues)
{
    return BatchReadImpl(bstrAddress, cUnitCount, pparrValues, VT_I2);
}

HRESULT MELSECClient::Impl::BatchReadDWord(BSTR bstrAddress, short cUnitCount,
    SAFEARRAY ** pparrValues)
{
    return BatchReadImpl(bstrAddress, cUnitCount, pparrValues, VT_I4);
}

HRESULT MELSECClient::Impl::BatchWriteBit(BSTR bstrAddress, VARIANTARG varValues)
{
    SAFEARRAY *psa = NULL;
    HRESULT hr;
    
    hr = GetSafeArrayFromVariant(varValues, VT_BOOL, &psa);
    if (FAILED(hr)) {
        return hr;
    }

    hr = BatchWriteImpl(bstrAddress, psa, VT_BOOL);

    if (varValues.parray != psa) {
        SafeArrayDestroy(psa);
    }

    return hr;
}

HRESULT MELSECClient::Impl::BatchWriteWord(BSTR bstrAddress, VARIANTARG varValues)
{
    SAFEARRAY *psa = NULL;
    HRESULT hr;
    
    hr = GetSafeArrayFromVariant(varValues, VT_I2, &psa);
    if (FAILED(hr)) {
        return hr;
    }

    hr = BatchWriteImpl(bstrAddress, psa, VT_I2);
    
    if (varValues.parray != psa) {
        SafeArrayDestroy(psa);
    }

    return hr;
}

HRESULT MELSECClient::Impl::BatchWriteDWord(BSTR bstrAddress, VARIANTARG varValues)
{
    SAFEARRAY *psa = NULL;
    HRESULT hr;
    
    hr = GetSafeArrayFromVariant(varValues, VT_I4, &psa);
    if (FAILED(hr)) {
        return hr;
    }

    hr = BatchWriteImpl(bstrAddress, psa, VT_I4);

    if (varValues.parray != psa) {
        SafeArrayDestroy(psa);
    }

    return hr;
}

HRESULT STDMETHODCALLTYPE MELSECClient::Impl::RandomReadWord(VARIANTARG varAddressArray,
    SAFEARRAY **pparrValues)
{
    SAFEARRAY *psaAddrs = NULL;
    HRESULT hr;
    
    hr = GetSafeArrayFromVariant(varAddressArray, VT_BSTR, &psaAddrs);
    if (FAILED(hr)) {
        return hr;
    }

    hr = RandomReadImpl(psaAddrs, pparrValues, VT_I2);

    if (varAddressArray.parray != psaAddrs) {
        SafeArrayDestroy(psaAddrs);
    }

    return hr;
}

HRESULT MELSECClient::Impl::RandomReadDWord(VARIANTARG varAddressArray, SAFEARRAY ** pparrValues)
{
    SAFEARRAY *psaAddrs = NULL;
    HRESULT hr;
    
    hr = GetSafeArrayFromVariant(varAddressArray, VT_BSTR, &psaAddrs);
    if (FAILED(hr)) {
        return hr;
    }

    hr = RandomReadImpl(psaAddrs, pparrValues, VT_I4);

    if (varAddressArray.parray != psaAddrs) {
        SafeArrayDestroy(psaAddrs);
    }

    return hr;
}

HRESULT MELSECClient::Impl::RandomWriteWord(VARIANTARG varAddressArray, VARIANTARG varValueArray)
{
    SAFEARRAY *psaAddrs = NULL, *psaValues = NULL;
    HRESULT hr;

    hr = GetSafeArrayFromVariant(varAddressArray, VT_BSTR, &psaAddrs);
    if (FAILED(hr)) {
        return hr;
    }

    hr = GetSafeArrayFromVariant(varValueArray, VT_I2, &psaValues);
    if (FAILED(hr)) {
        return hr;
    }

    hr = RandomWriteImpl(psaAddrs, psaValues, VT_I2);

    if (varAddressArray.parray != psaAddrs) {
        SafeArrayDestroy(psaAddrs);
    }

    if (varValueArray.parray != psaValues) {
        SafeArrayDestroy(psaValues);
    }

    return hr;
}

HRESULT MELSECClient::Impl::RandomWriteDWord(VARIANTARG varAddressArray, VARIANTARG varValueArray)
{
    SAFEARRAY *psaAddrs = NULL, *psaValues = NULL;
    HRESULT hr;

    hr = GetSafeArrayFromVariant(varAddressArray, VT_BSTR, &psaAddrs);
    if (FAILED(hr)) {
        return hr;
    }

    hr = GetSafeArrayFromVariant(varValueArray, VT_I4, &psaValues);
    if (FAILED(hr)) {
        return hr;
    }

    hr = RandomWriteImpl(psaAddrs, psaValues, VT_I4);

    if (varAddressArray.parray != psaAddrs) {
        SafeArrayDestroy(psaAddrs);
    }

    if (varValueArray.parray != psaValues) {
        SafeArrayDestroy(psaValues);
    }

    return hr;
}

HRESULT STDMETHODCALLTYPE MELSECClient::Impl::RemoteRun( void)
{
    return RemoteControlImpl(MELCLI_REMOTE_RUN);
}
        
HRESULT STDMETHODCALLTYPE MELSECClient::Impl::RemoteStop( void)
{
    return RemoteControlImpl(MELCLI_REMOTE_STOP);
}

HRESULT STDMETHODCALLTYPE MELSECClient::Impl::RemotePause( void)
{
    return RemoteControlImpl(MELCLI_REMOTE_PAUSE);
}

HRESULT STDMETHODCALLTYPE MELSECClient::Impl::RemoteReset( void)
{
    return RemoteControlImpl(MELCLI_REMOTE_RESET);
}

HRESULT STDMETHODCALLTYPE MELSECClient::Impl::RemoteReadTypeName( 
    BSTR *pbstrTypeName)
{
    HRESULT hr = E_FAIL;

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        LPSTR lpszTypeName;
        int iTypeCode;
        int err = melcli_remote_control(m_pCtx, NULL, MELCLI_REMOTE_READ_TYPE_NAME, 
            0, &lpszTypeName, &iTypeCode);

        if (err != MELCLI_ERROR_SUCCESS) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
            break;
        }

        char szType[256];
        sprintf(szType, "%s (0x%04X)", lpszTypeName, iTypeCode);

        LPOLESTR lpwszType = StrUtil::MultiByteToWideChar(szType);
        *pbstrTypeName = SysAllocString(lpwszType);
        delete lpwszType;

        hr = S_OK;
    } while (false);

    return hr;
}

HRESULT STDMETHODCALLTYPE MELSECClient::Impl::ClearError( void)
{
    HRESULT hr = E_FAIL;

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        int err = melcli_clear_error_code(m_pCtx, NULL);

        if (err != MELCLI_ERROR_SUCCESS) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
            break;
        }

        hr = S_OK;
    } while (false);

    return hr;
}

HRESULT MELSECClient::Impl::LoopbackTest(VARIANT_BOOL * pbSuccess)
{
    HRESULT hr = E_FAIL;

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        int err = melcli_self_test(m_pCtx, NULL);

        if (err != MELCLI_ERROR_SUCCESS) {
            if (err != MELCLI_ERROR_SELF_TEST_FAILED) {
                ReturnErrorInfo(err);
                hr = E_FAIL;
                break;
            }
            else {
                *pbSuccess = VARIANT_FALSE;
            }
        }

        *pbSuccess = VARIANT_TRUE;
        hr = S_OK;
    } while (false);

    return hr;
}

/* **************************************************************************/

HRESULT MELSECClient::Impl::BatchReadImpl(BSTR bstrAddress, short cUnitCount, 
    SAFEARRAY **pparrValues, VARTYPE vt)
{
    HRESULT hr = E_FAIL;
    LPSTR lpszAddr = NULL;
    char *data = NULL;
    SAFEARRAY *psa = NULL;

    if (cUnitCount <= 0) {
        return E_INVALIDARG;
    }

    if (pparrValues == NULL) {
        return E_POINTER;
    }

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        lpszAddr = StrUtil::WideCharToMultiByte(bstrAddress);
        int cDataLen;
        int err = melcli_batch_read(m_pCtx, NULL, lpszAddr, cUnitCount, &data, &cDataLen);
        if (err != MELCLI_ERROR_SUCCESS) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
            break;
        }

        SAFEARRAYBOUND rgsaBound[1];
        rgsaBound[0].lLbound = 0;
        rgsaBound[0].cElements = cUnitCount;

        psa = SafeArrayCreate(vt, 1, rgsaBound);
        if (psa == NULL) {
            hr = E_OUTOFMEMORY;
            break;
        }

        do {
            char *pArrData;
            if (FAILED(hr = SafeArrayAccessData(psa, (void**)&pArrData))) {
                break;
            }

            memcpy(pArrData, data, cDataLen);
            *pparrValues = psa;

            SafeArrayUnaccessData(psa);
        } while (false);

        hr = S_OK;
    } while (false);

    if (psa && FAILED(hr)) {
        SafeArrayDestroy(psa);
    }

    melcli_free(data);
    delete lpszAddr;
    return hr;
}

HRESULT MELSECClient::Impl::BatchWriteImpl(BSTR bstrAddress, SAFEARRAY *parrValues, 
    VARTYPE vt)
{
    HRESULT hr = E_FAIL;
    LPSTR lpszAddr = NULL;
    char *data = NULL;

    if (parrValues == NULL) {
        return E_POINTER;
    }

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        UINT cUnits;
        if (FAILED(hr = CheckSafeArrayValidOneDim(parrValues, &cUnits))) {
            return hr;
        }

        switch (vt) {
        case VT_BOOL:
            data = new char[cUnits];
            break;
        case VT_I2:
            data = new char[cUnits * 2];
            break;
        case VT_I4:
            data = new char[cUnits * 4];
            break;
        default:
            return E_INVALIDARG;
        }

        if (data == NULL) {
            hr = E_OUTOFMEMORY;
            break;
        }

        long idx;
        hr = SafeArrayGetLBound(parrValues, 1, &idx);
        if (FAILED(hr)) {
            break;
        }
        
        bool ok = true;
        if (vt == VT_BOOL) {
            VARIANT_BOOL boolVal;
            for (UINT i = 0; i != cUnits; ++i, ++idx) {
                hr = SafeArrayGetElement(parrValues, &idx, (void*)(&boolVal));
                if (FAILED(hr)) {
                    ok = false;
                    break;
                }

                data[i] = (boolVal == VARIANT_TRUE) ? 1 : 0;
            }
        }
        else if (vt == VT_I2) {
            short iVal;
            for (UINT i = 0; i != cUnits; ++i, ++idx) {
                hr = SafeArrayGetElement(parrValues, &idx, (void*)(&iVal));
                if (FAILED(hr)) {
                    ok = false;
                    break;
                }

                *(uint16_t*)(&data[2 * i]) = (uint16_t)iVal;
            }
        }
        else if (vt == VT_I4) {
            long lVal;
            for (UINT i = 0; i != cUnits; ++i, ++idx) {
                hr = SafeArrayGetElement(parrValues, &idx, (void*)(&lVal));
                if (FAILED(hr)) {
                    ok = false;
                    break;
                }

                *(uint32_t*)(&data[4 * i]) = lVal;
            }
        }

        lpszAddr = StrUtil::WideCharToMultiByte(bstrAddress);
        int err = melcli_batch_write(m_pCtx, NULL, lpszAddr, cUnits, data);
        if (err != MELCLI_ERROR_SUCCESS) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
            break;
        }

        hr = S_OK;
    } while (false);

    delete data;
    delete lpszAddr;
    return hr;
}

HRESULT MELSECClient::Impl::RandomReadImpl(SAFEARRAY *psaAddrs, SAFEARRAY **pparrValues,
    VARTYPE vt)
{
    HRESULT hr = E_FAIL;
    UINT cUnits = 0;
    char *data = NULL;
    SAFEARRAY *psa = NULL;
    LPCSTR *ppszAddrs = NULL;

    if ((pparrValues == NULL) || (psaAddrs == NULL)) {
        return E_POINTER;
    }

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        hr = CheckSafeArrayValidOneDim(psaAddrs, &cUnits);
        if (FAILED(hr)) {
            break;
        }

        ppszAddrs = new LPCSTR[cUnits + 1];
        if (ppszAddrs == NULL) {
            hr = E_OUTOFMEMORY;
            break;
        }
        else {
            // Marks the end of array.
            ppszAddrs[cUnits] = NULL;
        }
        
        long idx;
        BSTR bstrAddr;
        SafeArrayGetLBound(psaAddrs, 1, &idx);
        for (UINT i = 0; i != cUnits; ++i, ++idx) {
            hr = SafeArrayGetElement(psaAddrs, &idx, (void*)(&bstrAddr));
            if (FAILED(hr)) {
                break;
            }

            ppszAddrs[i] = StrUtil::WideCharToMultiByte(bstrAddr);
            SysFreeString(bstrAddr);
            if (ppszAddrs[i] == NULL) {
                hr = E_FAIL;
                break;
            }
        }

        if (FAILED(hr)) {
            break;
        }

        int cDataLen;
        int err;
        switch (vt) {
        case VT_I2:
            err = melcli_random_read_word(m_pCtx, NULL, ppszAddrs, (uint16_t**)(&data),
                &cDataLen);
            break;
        case VT_I4:
            err = melcli_random_read_dword(m_pCtx, NULL, ppszAddrs, (uint32_t**)(&data),
                &cDataLen);
            break;
        default:
            break;
        }

        if (err != MELCLI_ERROR_SUCCESS) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
            break;
        }

        SAFEARRAYBOUND rgsaBound[1];
        rgsaBound[0].lLbound = 0;
        rgsaBound[0].cElements = cUnits;

        psa = SafeArrayCreate(vt, 1, rgsaBound);
        if (psa == NULL) {
            hr = E_OUTOFMEMORY;
            break;
        }

        do {
            char *pArrData;
            if (FAILED(hr = SafeArrayAccessData(psa, (void**)&pArrData))) {
                break;
            }

            memcpy(pArrData, data, cDataLen);
            *pparrValues = psa;
            SafeArrayUnaccessData(psa);
        } while (false);

        hr = S_OK;
    } while (false);

    if (psa && FAILED(hr)) {
        SafeArrayDestroy(psa);
    }

    for (UINT i = 0; i != cUnits; ++i) {
        delete const_cast<LPSTR>(ppszAddrs[i]);
    }
    delete ppszAddrs;
    melcli_free(data);
    return hr;
}

HRESULT MELSECClient::Impl::RandomWriteImpl(SAFEARRAY * psaAddrs, SAFEARRAY * parrValues, 
    VARTYPE vt)
{
    HRESULT hr = E_FAIL;
    UINT cUnits = 0;
    LPCSTR *ppszAddrs = NULL;
    void *pArrData = NULL;

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        hr = CheckSafeArrayValidOneDim(psaAddrs, &cUnits);
        if (FAILED(hr)) {
            break;
        }

        UINT cValues;
        hr = CheckSafeArrayValidOneDim(parrValues, &cValues);
        if (FAILED(hr)) {
            break;
        }

        if (cValues != cUnits) {
            hr = E_INVALIDARG;
            break;
        }

        ppszAddrs = new LPCSTR[cUnits + 1];
        if (ppszAddrs == NULL) {
            hr = E_OUTOFMEMORY;
            break;
        }
        else {
            // Marks the end of array.
            ppszAddrs[cUnits] = NULL;
        }

        long idx;
        BSTR bstrAddr;
        SafeArrayGetLBound(psaAddrs, 1, &idx);
        for (UINT i = 0; i != cUnits; ++i, ++idx) {
            hr = SafeArrayGetElement(psaAddrs, &idx, (void*)(&bstrAddr));
            if (FAILED(hr)) {
                break;
            }

            ppszAddrs[i] = StrUtil::WideCharToMultiByte(bstrAddr);
            SysFreeString(bstrAddr);
            if (ppszAddrs[i] == NULL) {
                hr = E_FAIL;
                break;
            }
        }

        if (FAILED(hr)) {
            break;
        }

        if (FAILED(hr = SafeArrayAccessData(parrValues, &pArrData))) {
            break;
        }

        int err;
        switch (vt) {
        case VT_I2:
            err = melcli_random_write_word(m_pCtx, NULL, ppszAddrs, (const uint16_t*)(pArrData));
            break;
        case VT_I4:
            err = melcli_random_write_dword(m_pCtx, NULL, ppszAddrs, (const uint32_t*)(pArrData));
            break;
        default:
            break;
        }

        if (err != MELCLI_ERROR_SUCCESS) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
            break;
        }

        hr = S_OK;
    } while (false);

    if (pArrData) {
        SafeArrayUnaccessData(parrValues);
    }

    for (UINT i = 0; i != cUnits; ++i) {
        delete const_cast<LPSTR>(ppszAddrs[i]);
    }
    delete ppszAddrs;

    return hr;
}

HRESULT MELSECClient::Impl::RemoteControlImpl(int iCtlCode)
{
    HRESULT hr = E_FAIL;

    do {
        if (m_pCtx == NULL) {
            ReturnErrorInfo("The connection has not been established");
            hr = E_FAIL;
            break;
        }

        int err = melcli_remote_control(m_pCtx, NULL, iCtlCode, 0, NULL, NULL);

        if (err != MELCLI_ERROR_SUCCESS) {
            ReturnErrorInfo(err);
            hr = E_FAIL;
            break;
        }

        hr = S_OK;
    } while (false);

    return hr;
}

HRESULT MELSECClient::Impl::GetSafeArrayFromVariant(VARIANTARG var, VARTYPE vt, 
    SAFEARRAY ** ppsa)
{
    HRESULT hr = E_FAIL;
    SAFEARRAY *psa = NULL;
    LPCSTR *ppszAddrs = NULL;

    do {
        if (var.vt == (VT_ARRAY | vt)) {
            psa = var.parray;
            if (FAILED(hr = CheckSafeArrayValidOneDim(psa))) {
                break;
            }
        }
        else if (!(var.vt & VT_ARRAY)) {
            hr = VariantChangeType(&var, &var, 0, vt);
            if (FAILED(hr)) {
                break;
            }

            psa = SafeArrayCreateVector(vt, 0, 1);
            if (psa == NULL) {
                hr = E_OUTOFMEMORY;
                break;
            }

            long rgIndices[1] = { 0 };
            if (vt == VT_BSTR) {
                hr = SafeArrayPutElement(psa, rgIndices, (void*)(var.bstrVal));
            }
            else {
                hr = SafeArrayPutElement(psa, rgIndices, (void*)(&var.byref));
            }

            VariantClear(&var);
            
            if (FAILED(hr)) {
                break;
            }
        }
        else {
            hr = E_INVALIDARG;
            break;
        }

        hr = S_OK;
        *ppsa = psa;
    } while (false);

    return hr;
}

HRESULT MELSECClient::Impl::CheckSafeArrayValidOneDim(SAFEARRAY * psa, UINT *pcElements)
{
    HRESULT hr = S_OK;

    do {
        if (SafeArrayGetDim(psa) != 1) {
            hr = E_INVALIDARG;
            break;
        }

        long lBound, uBound;
        if (FAILED(hr = SafeArrayGetLBound(psa, 1, &lBound))
            || FAILED(hr = SafeArrayGetUBound(psa, 1, &uBound)))
        {
            hr = E_INVALIDARG;
            break;
        }

        long count = uBound - lBound + 1;
        if (count <= 0) {
            hr = E_INVALIDARG;
        }

        if (pcElements) {
            *pcElements = count;
        }
    } while (false);

    return hr;
}

void MELSECClient::Impl::ReturnErrorInfo(LPCSTR lpszFormat, ...)
{
    HRESULT hr;
    ICreateErrorInfo *pCEInfo;

    hr = CreateErrorInfo(&pCEInfo);
    if (FAILED(hr)) return;

    char szBuf[1024];
    va_list ap;
    va_start(ap, lpszFormat);
    vsprintf(szBuf, lpszFormat, ap);
    LPOLESTR lpszDesc = StrUtil::MultiByteToWideChar(szBuf);

    pCEInfo->SetDescription(lpszDesc);
    pCEInfo->SetGUID(IID_IMELSECClientContext);
    
    IErrorInfo *pErrInfo;
    hr = pCEInfo->QueryInterface(IID_IErrorInfo, (LPVOID*)&pErrInfo);
    if (SUCCEEDED(hr)) {
        SetErrorInfo(0, pErrInfo);
        pErrInfo->Release();
    }

    pCEInfo->Release();
    delete lpszDesc;
}

void MELSECClient::Impl::ReturnErrorInfo(int err)
{
    ReturnErrorInfo("(%d) %s", err, melcli_get_err_msg(err));
}