#include "eCustomClumpDict.h"
#include "..\..\manhunt\ClumpDict.h"
#include "..\..\manhunt\core.h"
#include "..\eLog.h"
#include <iostream>

std::vector<CClumpDict*> eCustomClumpDictManager::m_vecClumps;

CClump * eCustomClumpDict::FindClumpDescription(const char * name)
{
	CClump* clump = nullptr;
	CClumpDict* dict = (CClumpDict*)this;

	// custom dffs first
	for (int i = 0; i < eCustomClumpDictManager::m_vecClumps.size(); i++)
	{
		clump = eCustomClumpDictManager::m_vecClumps[i]->FindClumpDescription(name);
		if (clump)
			break;
	}



	if (!clump)
		clump = dict->FindClumpDescription(name);
	eLog::Message(__FUNCTION__, "Loading model: %s",name);

	
	return clump;
}

void eCustomClumpDict::Destroy()
{
	CClumpDict* dict = (CClumpDict*)this;
	dict->Destroy();

	for (int i = 0; i < eCustomClumpDictManager::m_vecClumps.size(); i++)
		eCustomClumpDictManager::m_vecClumps[i]->Destroy();

}

void eCustomClumpDictManager::InitHooks()
{
	InjectHook(0x433A91, &eCustomClumpDict::FindClumpDescription, PATCH_CALL);
	InjectHook(0x433BFF, &eCustomClumpDict::FindClumpDescription, PATCH_CALL);
	InjectHook(0x433C10, &eCustomClumpDict::FindClumpDescription, PATCH_CALL);
	InjectHook(0x43797B, &eCustomClumpDict::Destroy, PATCH_CALL);
}

char * eCustomClumpDictManager::TranslateClumpPtr(int ptr)
{
	switch (ptr)
	{
	case 0x756250:
		return "Global";
		break;
	case 0x69BC84:
		return "Local";
		break;
	case 0x69BC90:
		return "Character";
		break;
	default:
		return "Unknown";
		break;
	}
	return nullptr;
}

void eCustomClumpDictManager::PushClumpDict(CClumpDict * dict)
{
	m_vecClumps.push_back(dict);
}

int eCustomClumpDictManager::LoadTextureDict(const char * name)
{
	int txd = CallAndReturn<int, 0x4777D0, const char*>(name);
	printf("Loading TXD: %s [%x]\n", name,txd);
	return txd;
}

int eCustomClumpDictManager::LoadDffBank(const char * name, int arg)
{
	int dff = CallAndReturn<int, 0x4776C0, const char*,int>(name, arg);
	printf("Loading DFF: %s [%x]\n", name, dff);
	return dff;
}
