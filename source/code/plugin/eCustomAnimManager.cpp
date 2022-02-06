#include "eCustomAnimManager.h"
#include "..\core\eSettingsManager.h"
#include "..\manhunt\Anim.h"
#include "..\manhunt\String.h"
#include "..\manhunt\Filenames.h"
#include "..\manhunt\App.h"
#include "eLevelsLoader.h"
#include "eLog.h"
#include "..\core\FileFunctions.h"
#include <filesystem>
#include <memory>
#include <fstream>

std::unique_ptr<int[]> CCustomAnimManager::ptrNewAnimationsArray;
std::unique_ptr<eAnimationEntry[]> CCustomAnimManager::ptrNewAnimationsNamesArray;
void CCustomAnimManager::InitHooks()
{
	ptrNewAnimationsArray = std::make_unique<int[]>(eSettingsManager::iCustomAnimManagerSize);
	ptrNewAnimationsNamesArray = std::make_unique<eAnimationEntry[]>(eSettingsManager::iCustomAnimManagerSize);

	InjectHook(0x496410, Initialise, PATCH_JUMP);
	Patch<int>(0x4965B1 + 3, (int)&ptrNewAnimationsArray[0]);
	Patch<int>(0x496768 + 3, (int)&ptrNewAnimationsArray[0]);
	Patch<int>(0x496B17 + 3, (int)&ptrNewAnimationsArray[0]);

	LoadAnimations();
}

void CCustomAnimManager::LoadAnimations()
{
	std::filesystem::current_path(getExecutablePath());

	FILE* pFile = fopen("data\\animationNames.dat", "rb");

	if (pFile)
	{
		int i = 0;
		char line[1024];
		while (fgets(line, sizeof(line), pFile))
		{
			// check if comment
			if (line[0] == ';' || line[0] == '#' || line[0] == '\n')
				continue;

			char animName[128] = {};
			if (sscanf(line, "%s", &animName) == 1)
			{
				sprintf(ptrNewAnimationsNamesArray[i].name, animName);
				i++;

			}
		}
		eLog::Message(__FUNCTION__, "Read %d names", i);

		Patch<int>(0x41D92D, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x41E92B, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x41EBC9, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x41EBD4, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x421139, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x421145, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x4211B7, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x4211C3, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x421BF7, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x421C03, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x422616, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x422622, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x422927, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x422933, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x422D56, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x422D62, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x422FC6, (int)&ptrNewAnimationsNamesArray[0]);
		Patch<int>(0x422FD2, (int)&ptrNewAnimationsNamesArray[0]);

		fclose(pFile);
	}


}

bool CCustomAnimManager::Initialise()
{
	char tmpPath[_MAX_PATH];
	int  nAnims  = eSettingsManager::iCustomAnimManagerSize;
	bool result = false;

	do
	{
		ptrNewAnimationsArray[nAnims] = 0;
		nAnims -= 8;
	} while (nAnims >= 0);

	CAnimManager::ms_nAvailableAnims = 0;

	// load global animation file if set
	if (eSettingsManager::bCustomAnimManagerUseGlobalFile)
    	sprintf(tmpPath, "%s%s/", CFileNames::ms_CurrentLevelPath.str, "GLOBAL");
	else
	{
		if (eSettingsManager::bCustomLevelsLoader)
			sprintf(tmpPath, "%s%s/", CFileNames::ms_CurrentLevelPath.str, eLevelsLoader::m_levelNames[CApp::ms_currLevelNum]);
		else
			sprintf(tmpPath, "%s%s/", CFileNames::ms_CurrentLevelPath.str, (char*)(0x756034 + 20 * CApp::ms_currLevelNum));
	}


	strcat(tmpPath, CFileNames::ms_filenameAllAnims.str);
	strcat(tmpPath, CFileNames::ms_filenameAnimFileType.str);



	if (CAnimManager::LoadAnimations(tmpPath))
		result = true;
	else
		result = false;

	eLog::Message(__FUNCTION__, "Loaded file %s Animations - %d/%d", tmpPath, CAnimManager::ms_nAvailableAnims, eSettingsManager::iCustomAnimManagerSize);


	return result;

}

bool CCustomAnimManager::IsAnimAvailable(int id)
{
	return false;
}
