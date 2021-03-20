#include "eCommonHooks.h"
#include "..\manhunt\core.h"
#include "eStatsManager.h"
#include "..\core\eSettingsManager.h"
#include <filesystem>
#include "..\manhunt\Frontend.h"
#include "..\manhunt\Renderer.h"
#include "menu/eMenu.h"
#include "..\manhunt\Cheats.h"
#include "modloader/eModLoader.h";
#include "console/eConsole.h"
#include "..\manhunt\EntityManager.h"
#include "..\core\FileFunctions.h"
#include "..\manhunt\Scene.h"
#include "..\manhunt\Player.h"

void HookCommonShutdown()
{
	eStatsManager::SaveToFile();

	Call<0x489D50>();
}

void InitCommonHooks()
{

	InjectHook(0x4D7F70, HookCommonShutdown, PATCH_CALL);

	InjectHook(0x489B69, CommonHooks::CreateCamera, PATCH_CALL);
	Patch<int>(0x7113FC, (int)ClassHooks::CPlayer_Kill);
	Patch<int>(0x711538, (int)ClassHooks::CPlayer_Kick);

	InjectHook(0x49D5FD, ClassHooks::CPed_SetTranqed, PATCH_CALL);
	InjectHook(0x49D6A4, ClassHooks::CPed_SetTranqed, PATCH_CALL);
	InjectHook(0x49DE13, ClassHooks::CPed_SetTranqed, PATCH_CALL);
	InjectHook(0x49DE68, ClassHooks::CPed_SetTranqed, PATCH_CALL);

	InjectHook(0x49CDC1, ClassHooks::CPedHead_Explode, PATCH_CALL);
	if (strlen(eSettingsManager::szCustomUserFilesDirectory) > 0)
	InjectHook(0x4BE990, CommonHooks::GetMyDocumentsDirectory, PATCH_JUMP);

	InjectHook(0x4D7A58, CommonHooks::HookLoadSFX, PATCH_CALL);
	InjectHook(0x474A02, CommonHooks::CCheatHandler_SetupForLevel, PATCH_CALL); // open
	InjectHook(0x473F53, CommonHooks::CCheatHandler_SetupForLevel, PATCH_CALL); // reset
	InjectHook(0x5F189F, CommonHooks::HookRenderMenu, PATCH_CALL);

	InjectHook(0x4375D6, CommonHooks::CEntityManager_CreateArchetypes, PATCH_CALL);
	InjectHook(0x47444D, CommonHooks::GameStartInit, PATCH_CALL);

}

void DoCommonPatches()
{
	// CPlayer::ProcessHeartBeat
	if (eSettingsManager::bDisableHeartBeat)
		Nop(0x45F407, 5);
	// CPlayer::ProcessBreathing
	if (eSettingsManager::bDisableBreathing)
		Nop(0x45F40E, 5);

	if (eSettingsManager::bHideBSPWarnings)
	{
		Nop(0x474F24, 5);
		Nop(0x474F43, 5);
	}

	if (eSettingsManager::bDisableAutoAim)
		Nop(0x46A300, 7);

}

void __fastcall ClassHooks::CPlayer_Kill(int ptr)
{
	eStatsManager::IncrementStat(STAT_PLR_DEAD);
	CallMethod<0x45B8A0,int>(ptr);
}

void __fastcall ClassHooks::CPlayer_Kick(int ptr)
{
	eStatsManager::IncrementStat(STAT_PLR_KICKS);
	CallMethod<0x45B8E0, int>(ptr);
}

void ClassHooks::CPedHead_Explode(int ptr, int a2, int a3, int a4)
{
	eStatsManager::IncrementStat(STAT_HEADS_BOOM);
	Call<0x4F1AC0, int,int,int,int>(ptr,a2,a3,a4);
}


void __fastcall ClassHooks::CPed_SetTranqed(int ptr, float time)
{
	if (ptr == *(int*)0x715B9C)
	eStatsManager::IncrementStat(STAT_PLR_TRQ);
	CallMethod<0x4B2DD0, int, float>(ptr, time);
}

void __declspec(naked) CommonHooks::HookSkipIntroSeq()
{
	static int jmpPoint = 0x5E276E;
	_asm jmp jmpPoint
}

void CommonHooks::HookLoadSFX()
{
    TheMenu.PreInitialize();
	Call<0x4D7BB0>();
}

void CommonHooks::CCheatHandler_SetupForLevel()
{
	TheMenu.Initialize();
	CCheatHandler::SetupForLevel();


	if (eSettingsManager::bEnableFirstPersonMode)
	{
		CPlayer* plr = (CPlayer*)CScene::FindPlayer();
		plr->StartLookAround();

	}
}

void CommonHooks::CreateCamera()
{
	Call<0x5E2410>();

//	eStatsManager::Initialize();

}

void CommonHooks::HookRenderMenu()
{
	if (CFrontend::m_gameIsRunning)
	{
		if (TheConsole.m_consoleActive)
			TheConsole.Process();

    }
	TheMenu.ProcessMenu();

	Call<0x5D7070>();
}

char * CommonHooks::GetMyDocumentsDirectory()
{
	std::string folder(eSettingsManager::szCustomUserFilesDirectory, strlen(eSettingsManager::szCustomUserFilesDirectory));
	if (folder.length() > 0)
	{
		std::filesystem::current_path(getExecutablePath_str());

		if (!std::filesystem::exists(folder))
			std::filesystem::create_directory(folder);

	}

	std::string finalPath = getExecutablePath_str();
	finalPath += folder;
	return (char*)finalPath.c_str();
}

void CommonHooks::CEntityManager_CreateArchetypes()
{
	eModLoader::InitClumpDicts();
	CEntityManager::CreateArchetypes();
}

void CommonHooks::GameStartInit()
{
	Call<0x5EF510 >();
	if (eSettingsManager::iForcePlayerSkin > 0)
		CEntityManager::ms_playerCharacterID = eSettingsManager::iForcePlayerSkin;
}



void CommonHooks::HookManTriIcon(float x, float y, float scaleX, float scaleY, int red, int green, int blue, int alpha, int pTexture)
{
	Call<0x5F96F0, float, float, float, float, int, int, int, int, int>(x, y, scaleX, scaleY, red, green, blue, alpha, pTexture);
	// xbox values
	if (*(int*)0x7D343C)
		Call<0x5F96F0, float, float, float, float, int, int, int, int, int>(0.81300002, 0.88100001, 0.04, 0.05, 255, 255, 255, 255, *(int*)0x7D343C);
}

void __declspec(naked) CommonHooks::ArmsPosition_PlayerFPS()
{
	static CEntity* entity_ptr = 0;
	static float rotation_angle = 0.0f;
	static int jmp_continue = 0x4AB555;

	_asm {
		mov		entity_ptr, ebx
		mov		eax, dword ptr[ebx + 880]
		mov		rotation_angle, eax
	}

	//printf("Rotation angle - %f for %s\n", rotation_angle, entity_ptr->m_szName);

	if (!(entity_ptr == CScene::FindPlayer()))
	_asm {
		fsubr   dword ptr[ebx + 880]
		fst		st(4)
		jmp jmp_continue
	}
	else
	_asm {
		jmp jmp_continue
	}
}
