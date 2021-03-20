#include "String.h"
#include "core.h"

CString::CString()
{
	str = 0;
	len = 0;
	cap = 0;
}

void CString::__as(CString * src, CString * dest)
{
	Call<0x4F2A90, CString*, CString*>(src, dest);
}
