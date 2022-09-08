#include "TexDictionary.h"
#include "core.h"

int CTexDictionary::FindNamedTexture(CClumpDict* dict, const char* name)
{
	return CallAndReturn<int, 0x62F660, CClumpDict*, const char*>(dict, name);
}