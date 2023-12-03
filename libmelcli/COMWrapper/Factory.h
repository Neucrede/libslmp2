#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <unknwn.h>

class Factory : public IClassFactory
{
public:
    Factory();
    ~Factory();

public: /* IUnknown */
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

public: /* IClassFactory */
    STDMETHODIMP CreateInstance(IUnknown* pUnkOuter, REFIID riid, LPVOID* ppv);
    STDMETHODIMP LockServer(BOOL fLock);

private:
    ULONG m_cRef;
};

#endif /* __FACTORY_H__ */
