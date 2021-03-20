#include "ClumpDict.h"
#include "core.h"

CClump * CClumpDict::FindClump(const char * name)
{
	return CallMethodAndReturn<CClump*, 0x59B7C0,CClumpDict*, const char*>(this, name);
}

void CClumpDict::Initialise(const char * texture, const char * name)
{
	CallMethod<0x59B3F0, CClumpDict*, const char*, const char*>(this, texture, name);
}

int CClumpDict::CheckDict()
{
	return CallMethodAndReturn<int, 0x59B6F0, CClumpDict*>(this);
}

CClump * CClumpDict::FindClumpDescription(const char * name)
{
	return CallMethodAndReturn<CClump*, 0x59B730, CClumpDict*, const char*>(this, name);
}

void CClumpDict::Destroy()
{
	CallMethod<0x59B680, CClumpDict*>(this);
}
