#ifndef __MELSEC_CLIENT_H__
#define __MELSEC_CLIENT_H__

#include "MelcliCOMWrapper.h"
#include "melcli/melcli.h"
#include "StrUtil.h"

class MELSECClient : public IUnknown
{
public:
    MELSECClient(IUnknown* pUnkOuter);
    ~MELSECClient();

    HRESULT Init();

public: /* IUnknown */
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

private:
    friend class Impl;
    class Impl : public IMELSECClientContext
    {
    public:
        Impl(MELSECClient* pBackObj, IUnknown* pUnkOuter);
        ~Impl();

        HRESULT Init();

    public: /* IUnknown */
        STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv);
        STDMETHODIMP_(ULONG) AddRef();
        STDMETHODIMP_(ULONG) Release();

    public: /* IDispatch */
        STDMETHODIMP GetTypeInfoCount(
            /* [out] */ UINT *pctinfo);
        STDMETHODIMP GetTypeInfo(
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        STDMETHODIMP GetIDsOfNames(
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        STDMETHODIMP Invoke(
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
            UINT *puArgErr);

    public: /* IMELSECClientContext */
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Protocol( 
            /* [retval][out] */ ProtocolType *pProto);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Protocol( 
            /* [in] */ ProtocolType proto);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RemoteIPAddress( 
            /* [retval][out] */ BSTR *pbstrIPAddress);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_RemoteIPAddress( 
            /* [in] */ BSTR bstrIPAddress);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RemotePort( 
            /* [retval][out] */ SHORT *puiPort);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_RemotePort( 
            /* [in] */ SHORT iPort);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LocalIPAddress( 
            /* [retval][out] */ BSTR *pbstrIPAddress);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_LocalIPAddress( 
            /* [in] */ BSTR bstrIPAddress);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LocalPort( 
            /* [retval][out] */ SHORT *puiPort);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_LocalPort( 
            /* [in] */ SHORT iPort);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NetworkNumber( 
            /* [retval][out] */ BYTE *pbNetworkNumber);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_NetworkNumber( 
            /* [in] */ BYTE bNetworkNumber);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NodeNumber( 
            /* [retval][out] */ BYTE *pbNodeNumber);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_NodeNumber( 
            /* [in] */ BYTE bNodeNumber);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ProcNumber( 
            /* [retval][out] */ SHORT *puiProcNumber);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ProcNumber( 
            /* [in] */ SHORT iProcNumber);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionTimeout( 
            /* [retval][out] */ short *piTimeout);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ConnectionTimeout( 
            /* [in] */ short iTimeout);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ReceiveTimeout( 
            /* [retval][out] */ short *piTimeout);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveTimeout( 
            /* [in] */ short iTimeout);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FrameTimeout( 
            /* [retval][out] */ short *piTimeout);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FrameTimeout( 
            /* [in] */ short iTimeout);
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FrameWaitTime( 
            /* [retval][out] */ short *piWaitTime);
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FrameWaitTime( 
            /* [in] */ short iWaitTime);
        
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [retval][out] */ VARIANT_BOOL *pbSuccess);
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( void);
        
        virtual HRESULT STDMETHODCALLTYPE BatchReadBit( 
            /* [in] */ BSTR bstrAddress,
            /* [in] */ short cUnitCount,
            /* [retval][out] */ SAFEARRAY * *pparrValues);

        virtual HRESULT STDMETHODCALLTYPE BatchReadWord(
            /* [in] */ BSTR bstrAddress,
            /* [in] */ short cUnitCount,
            /* [retval][out] */ SAFEARRAY * *pparrValues);

        virtual HRESULT STDMETHODCALLTYPE BatchReadDWord(
            /* [in] */ BSTR bstrAddress,
            /* [in] */ short cUnitCount,
            /* [retval][out] */ SAFEARRAY * *pparrValues);

        virtual HRESULT STDMETHODCALLTYPE BatchWriteBit( 
            /* [in] */ BSTR bstrAddress,
            /* [in] */ VARIANTARG varValues);

        virtual HRESULT STDMETHODCALLTYPE BatchWriteWord(
            /* [in] */ BSTR bstrAddress,
            /* [in] */ VARIANTARG varValues);

        virtual HRESULT STDMETHODCALLTYPE BatchWriteDWord(
            /* [in] */ BSTR bstrAddress,
            /* [in] */ VARIANTARG varValues);

        virtual HRESULT STDMETHODCALLTYPE RandomReadWord( 
            /* [in] */ VARIANTARG varAddressArray,
            /* [retval][out] */ SAFEARRAY **pparrValues);

        virtual HRESULT STDMETHODCALLTYPE RandomReadDWord(
            /* [in] */ VARIANTARG varAddressArray,
            /* [retval][out] */ SAFEARRAY * *pparrValues);

        virtual HRESULT STDMETHODCALLTYPE RandomWriteWord(
            /* [in] */ VARIANTARG varAddressArray,
            /* [in] */ VARIANTARG varValueArray);

        virtual HRESULT STDMETHODCALLTYPE RandomWriteDWord(
            /* [in] */ VARIANTARG varAddressArray,
            /* [in] */ VARIANTARG varValueArray);

        virtual HRESULT STDMETHODCALLTYPE RemoteRun( void);
        
        virtual HRESULT STDMETHODCALLTYPE RemoteStop( void);
        
        virtual HRESULT STDMETHODCALLTYPE RemotePause( void);
        
        virtual HRESULT STDMETHODCALLTYPE RemoteReset( void);
        
        virtual HRESULT STDMETHODCALLTYPE RemoteReadTypeName( 
            /* [retval][out] */ BSTR *pbstrTypeName);

        virtual HRESULT STDMETHODCALLTYPE ClearError( void);

        virtual HRESULT STDMETHODCALLTYPE LoopbackTest(
            /* [retval][out] */ VARIANT_BOOL *pbSuccess);

    private:
        HRESULT BatchReadImpl(BSTR bstrAddress, short cUnitCount, SAFEARRAY **pparrValues, 
            VARTYPE vt);
        HRESULT BatchWriteImpl(BSTR bstrAddress, SAFEARRAY *parrValues, VARTYPE vt);
        HRESULT RandomReadImpl(SAFEARRAY *psaAddrs, SAFEARRAY **pparrValues, VARTYPE vt);
        HRESULT RandomWriteImpl(SAFEARRAY *psaAddrs, SAFEARRAY *parrValues, VARTYPE vt);
        HRESULT RemoteControlImpl(int iCtlCode);
        HRESULT GetSafeArrayFromVariant(VARIANTARG var, VARTYPE vt, SAFEARRAY **ppsa);
        HRESULT CheckSafeArrayValidOneDim(SAFEARRAY *psa, UINT *pcElements = NULL);
        void ReturnErrorInfo(LPCSTR lpszFormat, ...);
        void ReturnErrorInfo(int err);
        
    private:
        MELSECClient *m_pBackObj;
        IUnknown *m_pUnkOuter;
        ITypeInfo *m_pTypeInfo;

    private:
        ProtocolType m_proto;
        
        BSTR m_bstrRemoteIPAddress;
        SHORT m_iRemotePort;
        
        BSTR m_bstrLocalIPAddress;
        SHORT m_iLocalPort;

        BYTE m_bNetworkNumber;
        BYTE m_bNodeNumber;
        SHORT m_iProcNumber;

        SHORT m_iConnTimeout;
        SHORT m_iRecvTimeout;
        SHORT m_iFrameTimeout;
        SHORT m_iFrameTimer;

        melcli_ctx_t *m_pCtx;
    };

    friend class SupportErrorInfoImpl;
    class SupportErrorInfoImpl : public ISupportErrorInfo
    {
    public:
        SupportErrorInfoImpl(MELSECClient* pBackObj, IUnknown* pUnkOuter);
        ~SupportErrorInfoImpl();

    public: /* IUnknown */
        STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv);
        STDMETHODIMP_(ULONG) AddRef();
        STDMETHODIMP_(ULONG) Release();

    public: /* ISupportErrorInfo */
        STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

    private:
        MELSECClient *m_pBackObj;
        IUnknown *m_pUnkOuter;
    };

private:
    Impl *m_impl;
    SupportErrorInfoImpl *m_supportErrorInfoImpl;
    ULONG m_cRef;
    IUnknown *m_pUnkOuter;
};

#endif /* __MELSEC_CLIENT_H__ */
