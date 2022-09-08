#pragma once
#include "ClumpDict.h"

class CTexDictionary {
public:
	static int FindNamedTexture(CClumpDict* dict, const char* name);
};