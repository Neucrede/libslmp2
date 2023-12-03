#include "stdafx.h"
#include "Factory.h"
#include "MELSECClient.h"
#include "DllModule.h"

extern DllData* g_pDllData;

Factory::Factory() : m_cRef(0)
{
}

Factory::~Factory()
{
}

STDMETHODIMP Factory::QueryInterface(REFIID riid, LPVOID* ppv)
{
    if (riid == IID_IUnknown) {
        AddRef();
        *ppv = this;
    }
    else if (riid == IID_IClassFactory) {
        AddRef();
        *ppv = this;
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    return S_OK;
}

STDMETHODIMP_(ULONG) Factory::AddRef()
{
    return InterlockedIncrement((LPLONG)&m_cRef);
}

STDMETHODIMP_(ULONG) Factory::Release()
{
    ULONG cRef = InterlockedDecrement((LPLONG)&m_cRef);
    if (cRef == 0) {
        delete this;
    }

    return cRef;
}

STDMETHODIMP Factory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, LPVOID * ppv)
{
    MELSECClient *pObj = new MELSECClient(pUnkOuter);
    if (pObj == NULL) {
        return E_OUTOFMEMORY;
    }

    if (FAILED(pObj->Init())) {
        delete pObj;
        return E_UNEXPECTED;
    }

    pObj->AddRef();
    HRESULT hr = pObj->QueryInterface(riid, ppv);
    pObj->Release();

    return hr;
}

STDMETHODIMP Factory::LockServer(BOOL fLock)
{
    if (fLock) {
        InterlockedIncrement((LPLONG)&(g_pDllData->cLock));
    }
    else {
        InterlockedDecrement((LPLONG)&(g_pDllData->cLock));
    }

    return S_OK;
}
