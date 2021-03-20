#include "eCustomAnimManager.h"
#include "..\core\eSettingsManager.h"
#include "..\manhunt\Anim.h"
#include "..\manhunt\String.h"
#include "..\manhunt\Filenames.h"
#include "..\manhunt\App.h"
#include "eLog.h"
#include <memory>

std::unique_ptr<int[]> CCustomAnimManager::ptrNewAnimationsArray;

void CCustomAnimManager::InitHooks()
{
	ptrNewAnimationsArray = std::make_unique<int[]>(eSettingsManager::iCustomAnimManagerSize);

	InjectHook(0x496410, Initialise, PATCH_JUMP);
	Patch<int>(0x4965B1 + 3, (int)&ptrNewAnimationsArray[0]);
	Patch<int>(0x496768 + 3, (int)&ptrNewAnimationsArray[0]);
	Patch<int>(0x496B17 + 3, (int)&ptrNewAnimationsArray[0]);
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
		sprintf(tmpPath, "%s%s/", CFileNames::ms_CurrentLevelPath.str, (char*)(0x756034 + 20 * CApp::ms_currLevelNum)); 

	strcat(tmpPath, CFileNames::ms_filenameAllAnims.str);
	strcat(tmpPath, CFileNames::ms_filenameAnimFileType.str);



	if (CAnimManager::LoadAnimations(tmpPath))
		result = true;
	else
		result = false;

	eLog::Message(__FUNCTION__, "Loaded file %s Animations - %d/%d", tmpPath, CAnimManager::ms_nAvailableAnims, eSettingsManager::iCustomAnimManagerSize);


	return result;

}
