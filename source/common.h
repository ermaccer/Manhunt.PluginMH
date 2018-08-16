#pragma once
#include <iostream>
#include "..\shared\MemoryMgr.h"
#include "..\shared\IniReader.h"
using namespace Memory::VP;

// plugin variables

int KeyBaseScreenshotMode;
int KeyEnableScreenshotMode;
int KeyDisableScreenshotMode;
int KeyShowCoordinates;
int KeyDebugMenuEnable;
int KeyDebugMenuDisable;

bool EnableInfiniteAmmo;
bool EnableScreenshotMode;
// changes psg icon to unused correct one
bool ReplaceSniperRifleIcon;
bool RemoveCameraEffects;
bool EnableCheatsOnBonusLevels;
bool AddMoreDebugMenuOptions;
bool EnableFXMode;
bool EnableFPS;


//int& DisableHudAndFreezeWorld = *(int*)0x78949C;
int& DebugMode = *(int*)0x7CF088;
int& FreezeWorld = *(int*)0x715BA0;
int& FreeCamera = *(int*)0x715BB0;
int& DisplayHud = *(int*)0x7CF0A0;
int& DisableCameraMovement = *(int*)0x715BB4;
int& CurrentLeftWeapon = *(int*)0x8204A8;
int& CurrentBackWeapon = *(int*)0x8204A4;
int& InGame = *(int*)0x7D2E28;
float& FreeCameraMouseSpeed = *(float*)0x715AB8;
float& FreeCameraMovementSpeed = *(float*)0x715ABC;

// for weapon display hook
int buffer1, buffer2, buffer3, buffer4 = -1;


float& PlayerX = *(float *)0x821430;
float& PlayerY = *(float *)0x821438;
float& PlayerZ = *(float *)0x821434;
float& PlayerRot = *(float*)0x7A1608;

// Functions
void GetIniValues();
void ReloadIni();
void(__cdecl *WriteDebug)(int, char*);
void(__cdecl *WriteSDebug)(int, char*,char*);
void(__cdecl *FlashScreen)(int,int,int);
void(__cdecl *ReloadFrontend)();
// debug menu
void(__cdecl *AddToggleEntry)(char*, unsigned int);
void(__cdecl *AddFunctionEntry)(char*, void*);
void(__cdecl *EnableItemIfTrue)(unsigned int);



unsigned int PrintInfo(char* string)
{
	reinterpret_cast<void(__cdecl *)(char*, int)>(0x5E5410)(string, 0);
	return 0;
}


unsigned int SetHelpMessage(wchar_t* string)
{
	reinterpret_cast<void(__cdecl *)(wchar_t*)>(0x489F40)(string);
	return 0;
}


void ReloadIni()
{
	GetIniValues();
	FlashScreen(0, 255, 0);
}


void AddDebugMenuOptions()
{
	(int(__cdecl *)())0x591E60;
	// no need to check if InGame is true
	// this function inits when game is started anyway
	AddToggleEntry("Freeze World", 0x715BA0);
	AddToggleEntry("Display HUD", 0x7CF0A0);
	AddToggleEntry("Display Health", 0x7CF09B);
	AddToggleEntry("Display Text Box", 0x7CF0B9);
	AddFunctionEntry("Reload PluginMH.ini", ReloadIni);
}


bool KeyHit(unsigned int keyCode)
{
	return (GetKeyState(keyCode) & 0x8000) != 0;
}

bool KeyDown(unsigned int keyCode)
{
	return (GetAsyncKeyState(keyCode) & 0x8000) != 0;
}

void DisplayPlayerCoords()
{
	char buffer[256];
	sprintf_s(buffer, "~red~X~colour~ = %f ~green~Y~colour~ = %f ~blue~Z~colour~ = %f ~grey4~ROT~colour~ = %f", PlayerX,PlayerY,PlayerZ,PlayerRot);
	WriteDebug(10, buffer);
}





void MemPatch(void* address, void* data, int size)
{
	unsigned long flOld[2];
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &flOld[0]);
	memcpy(address, data, size);
	VirtualProtect(address, size, flOld[0], &flOld[1]);
}


void ReplaceCall(int address, void *func)
{
	int temp = 0xE8;
	MemPatch((void *)address, &temp, 1);
	temp = (int)func - ((int)address + 5);
	MemPatch((void *)((int)address + 1), &temp, 4);
}


void DisplayWeaponsHook()
{
	_asm {
		    mov ecx, ds:0x6A94C0
			cmp   ecx, buffer1
			je	jump
			cmp   ecx, buffer2
			je	jump
			cmp   ecx, buffer3
			je	jump
			cmp   ecx, buffer4
			je	jump
			push	0x45FDA0
			retn

			jump :
		    push	0x45FD98
			retn
	}
}





void ReadSkinIDs(char* line)
{
	sscanf_s(line, "%d %d %d %d", &buffer1, &buffer2, &buffer3, &buffer4);
}


unsigned int SwitchCameraHook()
{
	bool bCheck;
	unsigned int uiOutput;

	if (FreeCamera)
	{
		bCheck = DisableCameraMovement != 0;
		DisableCameraMovement = DisableCameraMovement == 0;
		if (bCheck)
			FreeCamera = 0;
	}
	else
	{
		SetHelpMessage(L"Press the Action button to teleport.");
		FreeCamera = 1;
	}
	if (!FreeCamera || DisableCameraMovement)
	{
		if (FreeCamera && DisableCameraMovement)
			uiOutput = PrintInfo("Stop Camera");
		else
			uiOutput = PrintInfo("Normal Camera");
	}
	else
	{
		uiOutput = PrintInfo("Free Camera");
	}
	return uiOutput;
}



void ScreenshotModeHelp()
{

	WriteSDebug(0, "Controls:", "");
	WriteSDebug(1, "%s  - Move", "~cyan2~ ~up~ ~down~ ~right~ ~left~ ~colour~");
	WriteSDebug(2, "%s  - Look Around", "~cyan2~Mouse~colour~");
	WriteSDebug(3, "%s  - Increase Speed", "~cyan2~ACTION2~colour~");


}

void CameraEffects()
{
	Patch<char>(0x7A1364, 0);
	Patch<char>(0x7A1365, 0);
	Patch<char>(0x7A1366, 0);
	Patch<char>(0x7A1367, 0);
	Patch<char>(0x7A1368, 0);
	Patch<char>(0x7A1369, 0);
}

void EmptyFunctionHook()
{

}