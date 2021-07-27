// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MemoryMgr.h"
#include "code/core/eMain.h"
#include "code/core/eSettingsManager.h"
#include "code/plugin/eCustomAnimManager.h"
#include "code/plugin/eCustomTableOfContents.h"
#include "code/plugin/eNewFrontend.h"
#include "code/plugin/eStatsManager.h"
#include "code/plugin/eNewFrontend.h"
#include "code/plugin/eCommonHooks.h"
#include "code/plugin/modloader/eCustomClumpDict.h"
#include "code/plugin/modloader/eModLoader.h"
#include "code/plugin/script/eScriptExtender.h"
#include "code/manhunt/Script.h"
#include "code/plugin/console/eConsole.h"
#include "code/manhunt/Filenames.h"
#include "code/manhunt/core.h"
#include "code/plugin/eQoLChanges.h"
#include "code/manhunt/Renderer.h"
#include "code/manhunt/Frontend.h"
#include "code/plugin/eSkinLoader.h"
#include "code/plugin/eMapLimits.h"
#include "code/core/FileFunctions.h"
#include "code/plugin/eLog.h"





using namespace Memory::VP;

int GenericTrueReturn() { return 1; }
int GenericFalseReturn() { return 0; }
void  GenericDummy() { }
void Init()
{
	//AllocConsole();
	//freopen("CONIN$", "r", stdin);
	//freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);

	eSettingsManager::Init();

	if (eSettingsManager::bEnableLog)
		eLog::Initialise();

	eModLoader::Init();

	if (eSettingsManager::bSkipIntroSequence) eQoLChanges::SkipIntro();
    if (eSettingsManager::bDisableAutoAim)	Nop(0x46A300, 7);
	if (eSettingsManager::bEnableCheatsInBonusLevels) InjectHook(0x5D4A50, GenericDummy, PATCH_JUMP);
	if (eSettingsManager::bAllowAllWeaponsExplodeCheat) Patch<char>(0x49D6DE + 2, -1);
	if (eSettingsManager::bRestoreConfirmationIcon)	InjectHook(0x5F085E, CommonHooks::HookManTriIcon, PATCH_CALL);

	eModLoader::ScanFolderForFiles("modloader");
	eSkinLoader::InitHooks();
	if (eSettingsManager::bIncreaseMapLimits)
	eMapLimits::InitHooks();

	if (eSettingsManager::bForceStaticExecutionCamera)
		InjectHook(0x4D7942, GenericTrueReturn, PATCH_CALL);

	InitCommonHooks();
	InitConsoleHooks();

	DoCommonPatches();
	eStatsManager::Initialize();
	eNewFrontend::Init();
    eCustomTableOfContents::InitHooks();
	if (eSettingsManager::bHookCustomAnimManager)
      CCustomAnimManager::InitHooks();

	if (eSettingsManager::bForceFXMode)
		Nop(0x5E9180, 10);

	if (eSettingsManager::bEnableFirstPersonMode)
	{
		// disable reset
		InjectHook(0x4622DC, GenericDummy, PATCH_CALL);
		Patch<int>(0x46053D, 0x00000000);
		Patch<int>(0x460545, 0x00000000);
	
		// lock arms for player only
		// filtering only player fixes a bug where peds 
		// wouldn't move torso while aiming
		InjectHook(0x4AB54D, CommonHooks::ArmsPosition_PlayerFPS, PATCH_JUMP);

		// disable resetting camera on x press
		Nop(0x4628B2, 5);
		
	}

	eNewFrontend::InitHooks();
	eStatsManager::InitHooks();
	eCustomClumpDictManager::InitHooks();


	InjectHook(0x5E279F, MainHooks::HookWndProc, PATCH_CALL);

	eLog::Message(__FUNCTION__, "PluginMH initialized!");

}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		if (*(int*)0x63BC93 != 0x24448B66)
		{
			MessageBoxA(0, "Invalid executable!", "PluginMH", 0);
		}
		else Init();
	}
}