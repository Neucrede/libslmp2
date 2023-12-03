#ifndef __STRUTIL_H__
#define __STRUTIL_H__

#include <windows.h>

namespace StrUtil
{
	LPWSTR MultiByteToWideChar(LPCSTR sz);
	LPSTR WideCharToMultiByte(LPWSTR wsz);
};

#endif /* __STRUTIL_H__ */
