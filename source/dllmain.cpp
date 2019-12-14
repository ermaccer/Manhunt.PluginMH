// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "code\CSettingsManager.h"
#include "code\CDebugMenuLimit.h"
#include "code\CWeaponAdjuster.h"
#include "code\CPlayerModelLoader.h"
#include "code\CStuff.h"
#include "code\ManhuntSDK.h"
#include "MemoryMgr.h"

using namespace Memory::VP;


void NullFunc(){}

void Init()
{
	SettingsMgr->Init();

	if (SettingsMgr->bEnableConsoleOutput)
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}


//	CDebugMenuLimit::Init();
//	InjectHook(0x5F1EC3, CDebugMenuLimit::HookOne, PATCH_JUMP);


	if (SettingsMgr->bEnableCheatsOnBonusLevels)
		InjectHook(0x5D4A50, CStuff::EnableCheatsOnBonusLevels, PATCH_JUMP);

	if (SettingsMgr->iRestrictedHeliumCheatWeaponType)
		Patch<char>(0x49D6DE + 2, SettingsMgr->iRestrictedHeliumCheatWeaponType);

	InjectHook(0x591E60, CStuff::HookDebugEntires, PATCH_JUMP);


	if (SettingsMgr->bEnableFirearmsExecutions)
		Patch<int>(0x46C7F2 + 1, (int)CWeaponAdjuster::CheckExecutionWeaponType - ((int)0x46C7F2 + 5));

	if (SettingsMgr->bEnableConfirmationIcon)
    	Patch<int>(0x5F085E + 1, (int)CStuff::HookManTriIcon - ((int)0x5F085E + 5));


	if (SettingsMgr->bEnableFXMode) Nop(0x5E9180, 10);

	if (SettingsMgr->bHookPlayerModelLoader)
	{
		if (CPlayerModelLoader::ReadFile("data\\skinLoader.dat"))
		{
			InjectHook(0x437FB0, CPlayerModelLoader::Hook, PATCH_JUMP);
			InjectHook(0x45FD86, CPlayerModelLoader::HookWeapon, PATCH_JUMP);
		}
	}


	if (SettingsMgr->bHookWeaponAdjuster)
	{
		if (CWeaponAdjuster::ReadFile("data\\weaponConfig.dat"))
		{
			InjectHook(0x4C67F0, CWeaponAdjuster::GetRecordName, PATCH_JUMP);
			InjectHook(0x4C5A90, CWeaponAdjuster::GetWeaponID, PATCH_JUMP);
			InjectHook(0x4C5870, CWeaponAdjuster::GetWeaponText, PATCH_JUMP);
			InjectHook(0x5DF9A0, CWeaponAdjuster::GetWeaponIcon, PATCH_JUMP);
			InjectHook(0x4C93B0, CWeaponAdjuster::Executions, PATCH_JUMP);
			InjectHook(0x4C6FC0, CWeaponAdjuster::HookShotgun, PATCH_JUMP);
			InjectHook(0x4C6F90, CWeaponAdjuster::HookSniperRifle, PATCH_JUMP);
			InjectHook(0x4C7020, CWeaponAdjuster::HookHealthItem, PATCH_JUMP);
			Patch<char>(0x49D78C, 0xE9);
			Patch<int>(0x49D78C + 1, (int)CWeaponAdjuster::HookExplodeHeadF - ((int)0x49D78C + 5));
			Patch<char>(0x49D782 + 7, 0);
			Patch<char>(0x49D778 + 7, 0);
			Patch<char>(0x49D94D, 0xE9);
			Patch<int>(0x49D94D + 1, (int)CWeaponAdjuster::HookAutoHeadshot - ((int)0x49D94D + 5));
		}
	}
	while (true)
	{
		Sleep(1);

		if (CStuff::KeyHit(SettingsMgr->iDebugMenuKey))
		{
			*(int*)0x7CF088 ^= 1;
			Sleep(130);
		}

		if (SettingsMgr->bEnableFPSMode)
		{
			Patch<int>(0x4622DC + 1, (int)NullFunc- ((int)0x4622DC + 5));
			Patch<int>(0x46053D, 0x00000000);
			Patch<int>(0x460545, 0x00000000);
			Patch<int>(0x46033F, 0x00000000);
		}

		if (CStuff::KeyHit(SettingsMgr->iQuickScreenshotKeyMain) && CStuff::KeyHit(SettingsMgr->iQuickScreenshotKeySub))
		{
			*(int*)0x715BA0 ^= 1; // freeze
			*(int*)0x715BB0 ^= 1; // free cam
			*(int*)0x7CF0A0 ^= 1; // hud
			Sleep(180);
		}

		if (SettingsMgr->iForcePlayerSkin)
			Patch<int>(0x6A94C0, SettingsMgr->iForcePlayerSkin);
	}
}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		if (*(int*)0x63BC93 != 0x24448B66)
		{
			MessageBoxA(0, "Invalid executable!", "PluginMH", 0);
		}
		else CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);
	}
}