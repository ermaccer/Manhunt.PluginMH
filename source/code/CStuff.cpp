#include "CStuff.h"
#include "ManhuntSDK.h"
#include <fstream>
#include "..\MemoryMgr.h"
#include "CSettingsManager.h"
#include "CWeaponSpawner.h"

using namespace Memory::VP;
using namespace ManhuntDebugMenu;
using namespace ManhuntFunctions;

int buffer1, buffer2, buffer3, buffer4;

void CStuff::EnableCheatsOnBonusLevels()
{

}

bool CStuff::KeyHit(unsigned int keyCode)
{
	return (GetKeyState(keyCode) & 0x8000) != 0;
}

int CStuff::HookDebugEntires()
{
	int result;
	if (!*(char*)0x7A13D0)
	{
		EditVariableInt("Cheat: Helium Hunters", (int*)0x7C84BC);
		EditVariableInt("Freeze World", (int*)0x715BA0);
		if (SettingsMgr->bEnableWeaponSpawner)
		{
			CallFunction("Spawn: Can", CWeaponSpawner::Can);
			CallFunction("Spawn: Bottle", CWeaponSpawner::Bottle);
			CallFunction("Spawn: Brick", CWeaponSpawner::Brick);
			CallFunction("Spawn: Knife", CWeaponSpawner::Knife);
			CallFunction("Spawn: Shard", CWeaponSpawner::Shard);
			CallFunction("Spawn: Shard (Piggsy)", CWeaponSpawner::ShardP);
			CallFunction("Spawn: Bag", CWeaponSpawner::Bag);
			CallFunction("Spawn: Wire", CWeaponSpawner::Wire);
			CallFunction("Spawn: Wire (Piggsy)", CWeaponSpawner::WireP);
			CallFunction("Spawn: Spike (Piggsy)", CWeaponSpawner::Wood);
			CallFunction("Spawn: Cleaver", CWeaponSpawner::Cleaver);
			CallFunction("Spawn: Crowbar", CWeaponSpawner::Crowbar);
			CallFunction("Spawn: Machete", CWeaponSpawner::Machete);
			CallFunction("Spawn: Axe", CWeaponSpawner::Axe);
			CallFunction("Spawn: IcePick", CWeaponSpawner::IcePick);
			CallFunction("Spawn: Sickle", CWeaponSpawner::Sickle);
			CallFunction("Spawn: Nightstick", CWeaponSpawner::NightStick);
			CallFunction("Spawn: Small Bat", CWeaponSpawner::SmallBat);
			CallFunction("Spawn: Hammer", CWeaponSpawner::Hammer);
			CallFunction("Spawn: Baseball Bat", CWeaponSpawner::WBat);
			CallFunction("Spawn: Metal Bat", CWeaponSpawner::Bat);
			CallFunction("Spawn: Spiked Bat", CWeaponSpawner::SpikedBat);
			CallFunction("Spawn: Glock", CWeaponSpawner::Glock);
			CallFunction("Spawn: Nailgun", CWeaponSpawner::NailGun);
			CallFunction("Spawn: Desert Eagle", CWeaponSpawner::Deagle);
			CallFunction("Spawn: Uzi", CWeaponSpawner::Uzi);
			CallFunction("Spawn: 6Shooter", CWeaponSpawner::Revolver);
			CallFunction("Spawn: Shotgun", CWeaponSpawner::Shotgun);
			CallFunction("Spawn: Shotgun + Torch", CWeaponSpawner::ShotgunT);
			CallFunction("Spawn: Sawnoff", CWeaponSpawner::SawnOff);
			CallFunction("Spawn: Sniper Rifle", CWeaponSpawner::Sniper);
			CallFunction("Spawn: C. Commando", CWeaponSpawner::Colt);
			CallFunction("Spawn: Tranq. Rifle", CWeaponSpawner::Tranq);
			CallFunction("Spawn: Chainsaw", CWeaponSpawner::Chainsaw);
			CallFunction("Spawn: Custom #1", CWeaponSpawner::Custom1);
			CallFunction("Spawn: Custom #2", CWeaponSpawner::Custom2);
			CallFunction("Spawn: Custom #3", CWeaponSpawner::Custom3);
		}
		result = CallFunction("Dump player coords", CStuff::DumpPlayerCoords);
	}
	Patch<char>(0x7A0FAC + 0x424, 1);
	return result;
}

void CStuff::DisplayVariousData()
{
	WriteDebug(1, "Level ID: %d", *(int*)0x75622C);
	WriteDebug(2, "Total debug menu items: %d/170", *(int*)0x7CF55C);
}

void CStuff::DumpPlayerCoords()
{
	std::ofstream oFile("data\\out.txt", std::ofstream::binary);

	oFile << "Text output: " << *(float*)0x821430 << " " << *(float*)0x821434 << " " << *(float*)0x821438 << std::endl;

	oFile << "Raw output (use hex editor to see):\n";

	for (int i = 0; i < 3; i++)
	{
		float pos = *(float*)(0x821430 + i * 4);
		oFile.write((char*)&pos, sizeof(float));
	}

	WriteDebug(12, "Saved coords to data\\out.txt!");
}

void CStuff::LoadSkins(char * line)
{
	sscanf(line, "%d %d %d %d", &buffer1, &buffer2, &buffer3, &buffer4);
}

void CStuff::DisplayWeaponsHook()
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

void CStuff::HookManTriIcon(float x, float y, float scaleX, float scaleY, int red, int green, int blue, int alpha, int pTexture)
{
	Call<0x5F96F0, float, float, float, float, int, int, int, int, int>(x, y, scaleX, scaleY, red, green, blue, alpha, pTexture);
	if (*(int*)0x7D343C)
	Call<0x5F96F0, float, float, float, float, int, int, int, int, int>(0.81300002,0.88100001, 0.04, 0.05, 255, 255, 255, 255, *(int*)0x7D343C);
}

void CStuff::LoadTrashman()
{
	Call<0x4D82C0, const char*>("attic");
}

void __declspec(naked) CStuff::HookSkipIntroSeq()
{
	static int jmpPoint = 0x5E276E;
	_asm jmp jmpPoint

}

void __declspec(naked) CStuff::DisableExecutionCamera()
{
	static int jmpPoint = 0x589D10;
	_asm jmp jmpPoint
}



