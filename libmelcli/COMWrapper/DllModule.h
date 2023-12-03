#ifndef __DLLMODULE_H__
#define __DLLMODULE_H__

struct DllData
{
    HANDLE  hModule;
    HANDLE  hMap;

    ULONG   cLock;
    ULONG   cComponent;
};

struct DllGlobalSharedData
{
    DWORD   dwUseCount;
};

#endif