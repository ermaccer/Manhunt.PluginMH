#include "String.h"
#include "core.h"

CString::CString()
{
	str = 0;
	len = 0;
	cap = 0;
}

CString::CString(const char * text)
{
	CallMethod<0x4F2550, CString*, const char*>(this, text);
}

CString::~CString()
{
	CallMethod<0x4F2520, CString*>(this);
}

void CString::__as(CString * src, CString * dest)
{
	Call<0x4F2A90, CString*, CString*>(src, dest);
}

bool CString::Identical(const char* text)
{
	return CallMethodAndReturn<bool, 0x4F2490, CString*, const char*>(this, text);
}
