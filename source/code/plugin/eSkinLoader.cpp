#include "eSkinLoader.h"
#include "..\manhunt\core.h"
#include "..\core\eSettingsManager.h"
#include <vector>
#include "..\core\FileFunctions.h"
#include "..\manhunt\EntityManager.h"
#include <filesystem>
#include <rwcore.h>
#include <rwplcore.h>

#include "eLog.h"

std::vector<eSkinEntry> eSkinLoader::vSkins;
bool eSkinLoader::ms_bSkinLoaded;
RpClump* eSkinLoader::ms_pPlayerClump;

void eSkinLoader::InitHooks()
{
	ms_bSkinLoaded = false;
	if (eSettingsManager::bHookSkinLoader)
	{
		if (eSkinLoader::ReadFile("data\\skinLoader.dat"))
		{
			InjectHook(0x437FB0, eSkinLoader::Hook, PATCH_JUMP);
			//InjectHook(0x45FD86, eSkinLoader::HookWeapon, PATCH_JUMP);
		}
	}
}

int eSkinLoader::ReadFile(const char * name)
{
	std::filesystem::current_path(getExecutablePath());

	FILE* pFile = fopen(name, "rb");
	if (!pFile)
	{
		eLog::Message(__FUNCTION__, "ERROR: Could not open %s!", name);
		return 0;
	}
	if (pFile)
	{
		eLog::Message(__FUNCTION__, "Reading %s!", name);
		char line[1536];
		while (fgets(line, sizeof(line), pFile))
		{
			// check if comment
			if (line[0] == ';' || line[0] == '#' || line[0] == '\n')
				continue;

			int id = 0;
			if (sscanf(line, "%d", &id) == 1)
			{
				char t_dffname[128];
				char t_txdename[128];
				char t_rootname[128];
				int  bDisplayWeapons;
				int  flag;

				sscanf(line, "%d %s %s %s %d %d", &id, &t_txdename, &t_dffname, &t_rootname, &bDisplayWeapons, &flag);

				// convert to strings
				std::string strDff(t_dffname, strlen(t_dffname));
				std::string strTxd(t_txdename, strlen(t_txdename));
				std::string strRoot(t_rootname, strlen(t_rootname));


				// create skin
				eSkinEntry skin;
				skin.iID = id;
				skin.iShowWeapons = bDisplayWeapons;
				skin.sModelFile = strDff;
				skin.sRootName = strRoot;
				skin.sTxdFile = strTxd;
				skin.iFlag = flag;
				vSkins.push_back(skin);
			}

		}
		eLog::Message(__FUNCTION__, "Read %d entries!", vSkins.size());
		fclose(pFile);
	}
	return 1;
}

int eSkinLoader::Hook(int skinID)
{
	char* result;
	char fullDffPath[260];
	char fullTxdPath[260];
	char txdFile[260];
	char dffFile[260];


	sprintf(txdFile, "%s", vSkins[FindSkin(skinID)].sTxdFile.c_str());
	sprintf(dffFile, "%s", vSkins[FindSkin(skinID)].sModelFile.c_str());
	strcpy((char*)0x6A94A0, vSkins[FindSkin(skinID)].sRootName.c_str());
	*(int*)0x7AE94C = vSkins[FindSkin(skinID)].iFlag;


	sprintf(fullTxdPath, "%s%s", "./levels", txdFile);
	sprintf(fullDffPath, "%s%s", "./levels", dffFile);

	// TODO: update with proper functions?

	printf("Loading %s\n", fullDffPath);

	result = CallMethodAndReturn<char*, 0x4BDDC0, int, char*>(*(int*)0x736DB8, fullTxdPath);
	CallMethod<0x59B3F0, int*, char*, char*>(&(*(int*)0x69BC90), result, fullDffPath);
	return CallMethodAndReturn<int, 0x4BDDE0, int, char*>(*(int*)0x736DB8, result);
}

int eSkinLoader::FindSkin(int skinID)
{
	int iFind = 0;

	for (int i = 0; i < vSkins.size(); i++)
	{
		if (vSkins[i].iID == skinID)
		{
			iFind = i;
			break;
		}
	}
	return iFind;
}

void __declspec(naked) SkinLoader_HookWeapon()
{
	static int jmpTrue  = 0x45FD98;
	static int jmpFalse = 0x45FDA0;


	if (eSkinLoader::vSkins[eSkinLoader::FindSkin(CEntityManager::ms_playerCharacterID)].iShowWeapons == 1)
		_asm jmp jmpTrue
	else
		_asm jmp jmpFalse
}

void eSkinLoader::LoadPlayerDff()
{
	if (!ms_bSkinLoaded)
	{
		RwStream *stream;

		stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, "levels\\GLOBAL\\CHARPAK\\pig_pc.dff");
		printf("stream: %x\n", stream);

		if (RwStreamFindChunk(stream, rwID_CLUMP, NULL, NULL))
			ms_pPlayerClump = RpClumpStreamRead(stream);
		printf("clump %x\n", ms_pPlayerClump);
		if (ms_pPlayerClump)
			ms_bSkinLoaded = true;

		RwStreamClose(stream, NULL);
	}



}
