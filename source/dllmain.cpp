// dllmain.cpp : Defines the entry point for the DLL application.
// rewritten
// no color changing core for now, no inst dumping from game (as manhunt-toolkit is way easier)
// will be added soon (tm)
#include "..\shared\stdafx.h"

#include "common.h"


void GetFuncs()
{
	WriteSDebug = (void(__cdecl *)(int, char*, char *))0x5E5480;
	WriteDebug = (void(__cdecl *)(int, char*))0x5E5480;
	// debug menu
	AddToggleEntry = (int(__cdecl *)(char*, unsigned int))0x5E9840;
	AddFunctionEntry = (int(__cdecl *)(char*, void*))0x5E9920;
	AddSliderEntry = (int(__cdecl *)(char*, void*, void*, void*, void*, void*, void*, void*))0x5E98F0;
	EnableItemIfTrue = (void(__cdecl *)(unsigned int))0x5E9960;
	FlashScreen = (void(__cdecl *)(int,int,int))0x5EF890;
}
void GetIniValues()
{
	CIniReader reader("PluginMH.ini");
	KeyShowCoordinates = reader.ReadInteger("Settings", "KeyShowCoordinates", 0x74);
	KeyBaseScreenshotMode = reader.ReadInteger("Settings", "KeyBaseScreenshotMode", 0x11);
	KeyEnableScreenshotMode = reader.ReadInteger("Settings", "KeyEnableScreenshotMode", 0x56);
	KeyDisableScreenshotMode = reader.ReadInteger("Settings", "KeyDisableScreenshotMode", 0x42);
	KeyDebugMenuEnable = reader.ReadInteger("Settings", "KeyDebugMenuEnable", 0x70);
	KeyDebugMenuDisable = reader.ReadInteger("Settings", "KeyDebugMenuDisable", 0x71);
	EnableScreenshotMode = reader.ReadBoolean("Settings", "EnableScreenshotMode", 0);
	EnableCheatsOnBonusLevels = reader.ReadBoolean("Settings", "EnableCheatsOnBonusLevels", 0);
	AddMoreDebugMenuOptions = reader.ReadBoolean("Settings", "AddMoreDebugMenuOptions", 0);
	EnableFXMode = reader.ReadBoolean("Settings", "EnableFXMode", 0);
	EnableFPS = reader.ReadBoolean("Settings", "EnableFirstPerson", 0);
	EnableInfiniteAmmo = reader.ReadBoolean("Settings", "EnableInfiniteAmmo", 0);
	RemoveCameraEffects = reader.ReadBoolean("Settings", "RemoveCameraEffects", 0);
	char* tempLine = reader.ReadString("Settings", "DisplayWeaponsOn", "0 2");
	ReadSkinIDs(tempLine);
}

void WINAPI Init()
{
	GetFuncs();
	GetIniValues();
	Sleep(10);

	while (true) {

		InjectHook(0x45FD86, DisplayWeaponsHook, PATCH_JUMP);
		InjectHook(0x5EE9E0, SwitchCameraHook, PATCH_JUMP);
		if (AddMoreDebugMenuOptions) InjectHook(0x591E60, AddDebugMenuOptions, PATCH_JUMP);
		if (RemoveCameraEffects) CameraEffects();
	
		if (KeyHit(KeyDebugMenuEnable)) DebugMode = 1;
		if (KeyHit(KeyDebugMenuDisable)) DebugMode = 0;

		if (EnableInfiniteAmmo) Nop(0x4F9073, 7);
		if (EnableFXMode) Nop(0x5E9180, 10);

		if (ReplaceSniperRifleIcon) Patch(0x5DFB16, 0x7D39F4);

		if (EnableFPS)
		{
			ReplaceCall(0x4622DC, EmptyFunctionHook);
			// disable camera reset if any key is pressed
			Patch<unsigned int>(0x46053D, 0x00000000); 
			Patch<unsigned int>(0x460545, 0x00000000);
			Patch<unsigned int>(0x46033F, 0x00000000);
		}

		if (KeyHit(KeyShowCoordinates))DisplayPlayerCoords();

		if (EnableCheatsOnBonusLevels) ReplaceCall(0x474334, EmptyFunctionHook);

		if (EnableScreenshotMode && InGame)
		{
			FreeCameraMouseSpeed = 0.035f; FreeCameraMovementSpeed = 0.95f;
			if (KeyHit(KeyBaseScreenshotMode) && KeyHit(KeyEnableScreenshotMode))
			{

				FreeCamera = 1; FreezeWorld = 1; DisplayHud = 0;
				ScreenshotModeHelp();
			}
			if (KeyHit(KeyBaseScreenshotMode) && KeyHit(KeyDisableScreenshotMode))
			{

				FreeCamera = 0; FreezeWorld = 0; DisplayHud = 1;
			}
		}

		Sleep(1);
	}
}


BOOL WINAPI DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		if (*(int*)0x63BC93 != 0x24448B66)
		{
			MessageBoxA(0, "Invalid executable!", 0, 0);
			return -1;
		}
		else CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Init), nullptr, 0, nullptr);
	}
	return TRUE;
}

