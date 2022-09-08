#include "eCustomClumpDict.h"
#include "..\..\manhunt\ClumpDict.h"
#include "..\..\manhunt\core.h"
#include "..\..\manhunt\TexDictionary.h"
#include "..\eLog.h"
#include <iostream>

std::vector<CClumpDict*> eCustomClumpDictManager::m_vecClumps;

CClump * eCustomClumpDict::FindClumpDescription(const char * name)
{
	CClump* clump = nullptr;
	CClumpDict* dict = (CClumpDict*)this;

	// custom dffs first
	for (unsigned int i = 0; i < eCustomClumpDictManager::m_vecClumps.size(); i++)
	{
		clump = eCustomClumpDictManager::m_vecClumps[i]->FindClumpDescription(name);
		if (clump)
		{
			eLog::Message(__FUNCTION__, "Loaded model %s!", name);
			break;
		}
	}



	if (!clump)
		clump = dict->FindClumpDescription(name);

	if (!clump)
		eLog::Message(__FUNCTION__, "Could not load model %s!", name);


	
	return clump;
}

CClump * eCustomClumpDict::FindClump(const char * name)
{
	CClump* clump = nullptr;
	CClumpDict* dict = (CClumpDict*)this;

	// custom dffs first
	for (unsigned int i = 0; i < eCustomClumpDictManager::m_vecClumps.size(); i++)
	{
		clump = eCustomClumpDictManager::m_vecClumps[i]->FindClump(name);
		if (clump)
		{
			eLog::Message(__FUNCTION__, "Loaded model %s!", name);
			break;
		}
	}

	if (!clump)
		clump = dict->FindClump(name);

	if (!clump)
		eLog::Message(__FUNCTION__, "Could not load model %s!", name);

	return clump;
}

void eCustomClumpDict::Destroy()
{
	CClumpDict* dict = (CClumpDict*)this;
	dict->Destroy();

	for (unsigned int i = 0; i < eCustomClumpDictManager::m_vecClumps.size(); i++)
		eCustomClumpDictManager::m_vecClumps[i]->Destroy();

}

int eCustomClumpDict::CustomUnkFunc(const char* name)
{
	int clump = 0;
	CClumpDict* dict = (CClumpDict*)this;

	// custom dffs first
	for (unsigned int i = 0; i < eCustomClumpDictManager::m_vecClumps.size(); i++)
	{
		clump = eCustomClumpDictManager::m_vecClumps[i]->sub_59B860(name);
		if (clump)
		{
			eLog::Message(__FUNCTION__, "Loaded model %s!", name);
			break;
		}
	}

	if (!clump)
		clump = dict->sub_59B860(name);

	if (!clump)
		eLog::Message(__FUNCTION__, "Could not load model %s!", name);

	return clump;
}

void eCustomClumpDictManager::InitHooks()
{
	InjectHook(0x433BFF, &eCustomClumpDict::FindClumpDescription, PATCH_CALL);
	InjectHook(0x433C10, &eCustomClumpDict::FindClumpDescription, PATCH_CALL);

	InjectHook(0x4F1239, &eCustomClumpDict::FindClump, PATCH_CALL);

	InjectHook(0x43797B, &eCustomClumpDict::Destroy, PATCH_CALL);

	// skinned peds support
	InjectHook(0x433B66, &eCustomClumpDict::CustomUnkFunc, PATCH_CALL);

	// randomized textures from all dicts
	InjectHook(0x49D162, &eCustomTexDict::FindNamedTexture, PATCH_CALL);
	InjectHook(0x4F134A, &eCustomTexDict::FindNamedTexture, PATCH_CALL);
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
		return "Unknown/Custom";
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

int eCustomTexDict::FindNamedTexture(CClumpDict* dict, const char* name)
{
	int tex = 0;
	// custom dffs first
	for (unsigned int i = 0; i < eCustomClumpDictManager::m_vecClumps.size(); i++)
	{
		CClumpDict d = *eCustomClumpDictManager::m_vecClumps[i];
		tex = CTexDictionary::FindNamedTexture((CClumpDict*)*(int*)eCustomClumpDictManager::m_vecClumps[i], name);
		if (tex)
			break;
	}

	if (!tex)
		tex = CTexDictionary::FindNamedTexture(dict, name);


	return tex;
}
