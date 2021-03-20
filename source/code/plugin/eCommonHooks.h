#pragma once

void HookCommonShutdown();
void InitCommonHooks();
namespace ClassHooks {
	void __fastcall CPlayer_Kill(int ptr);
	void __fastcall CPlayer_Kick(int ptr);
	void CPedHead_Explode(int ptr, int a2, int a3, int a4);
	void __fastcall CPed_SetTranqed(int ptr, float time);
}
namespace CommonHooks {
	void  HookSkipIntroSeq();
	void  HookLoadSFX();
	void  CCheatHandler_SetupForLevel();
	void  CreateCamera();
	void  HookRenderMenu();
	char* GetMyDocumentsDirectory();
	void  CEntityManager_CreateArchetypes();
	void  GameStartInit();
	void HookManTriIcon(float x, float y, float scaleX, float scaleY, int red, int green, int blue, int alpha, int pTexture);

	void ArmsPosition_PlayerFPS();
}

void DoCommonPatches();


