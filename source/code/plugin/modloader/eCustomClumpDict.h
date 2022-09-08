#pragma once
#include "..\..\manhunt\ClumpDict.h"
#include <vector>


class eCustomClumpDictManager {
public:
	static std::vector<CClumpDict*> m_vecClumps;

	static void InitHooks();
	static char* TranslateClumpPtr(int ptr);
	static void PushClumpDict(CClumpDict* dict);
	static int  LoadTextureDict(const char* name);
	static int  LoadDffBank(const char* name, int arg);

};

class eCustomClumpDict {
public:

	CClump* FindClumpDescription(const char* name);
	CClump* FindClump(const char* name);
	void	Destroy();

	int	CustomUnkFunc(const char* name);
};


class eCustomTexDict {
public:
	static int FindNamedTexture(CClumpDict*dict, const char* name);
};