#include "ManhuntSDK.h"

void ManhuntFunctions::FlashScreen(int red, int green, int blue)
{
	Call<0x5EF890, int, int, int>(red, green, blue);
}

CEntity * ManhuntFunctions::FindPlayer()
{
	return *(CEntity**)0x715B9C;
}

void ManhuntFunctions::SetHelpMessage(wchar_t * msg)
{
	Call<0x489F40, wchar_t*>(msg);
}

void ManhuntFunctions::CreateInventoryItem(CEntity * ent, int item, bool b1)
{
	CallMethod<0x49A5C0, CEntity*, int, bool>(ent, item, b1);
}

void ManhuntFunctions::AddAmmoToInventoryWeapon(CEntity * ent, int amount, int item)
{
	int weapon_ptr = *(int*)(ent + 336);
	int v1 = ((int(__thiscall*)(int, int))0x4929E0)(weapon_ptr, item);

	((void(__thiscall*)(int, int))0x4F8B40)(*(int*)(v1 + 428), amount);
}


CVector* ManhuntFunctions::GetEntityPosition(CEntity * ent)
{
	return CallMethodAndReturn<CVector*, 0x4317E0, CEntity*>(ent);
}

void ManhuntFunctions::SetHealth(CEntity * ent, float health)
{
}

void ManhuntFunctions::UnlockBonusLevels()
{
	Call<0x5E4D00>();
}

void ManhuntFunctions::UnlockBonusFeatures()
{
	Call<0x5E4D10>();
}

void ManhuntFunctions::HUDToggleFlashFlags(int elem, bool state)
{
	Call<0x5EA490, int, bool>(elem, state);
}

int ManhuntFunctions::GetLevelStars(int level)
{
	return CallAndReturn<int, 0x5D1E80, int>(level);
}

void ManhuntFunctions::CompleteLevel()
{
	Call<0x5D1F00>();
}

int ManhuntFunctions::LoadTexture(int txd, const char * name)
{
	return CallAndReturn<int,0x62F660,int, const char*>(txd,name);
}

wchar_t * ManhuntFunctions::GetText(int buffer, const char * entry)
{
	return CallMethodAndReturn<wchar_t*,0x4937E0,int,const char*>(buffer,entry);
}

void ManhuntFunctions::GiveAmmo(int amount, int item)
{
	int v0 = *(int*)(*(int*)0x715B9C + 336);
	int v1 = ((int(__thiscall*)(int, int))0x4929E0)(v0, item);

	((void(__thiscall*)(int, int))0x4F8B40)(*(int*)(v1 + 428), amount);
}

CEntity * ManhuntFunctions::GetEntity(const char * name)
{
	return CallAndReturn<CEntity*, 0x437BE0, const char*>(name);
}

void ManhuntDebugMenu::EditVariableInt(const char * name, int * variable)
{
	Call<0x5E9840, const char*, int*>(name, variable);
}

void ManhuntDebugMenu::EnableItemIfTrue(int * variable)
{
	Call<0x5E9960, int*>(variable);
}

int ManhuntDebugMenu::CallFunction(const char * name, void * function)
{
	return CallAndReturn<int,0x5E9920, const char*, void*>(name, function);
}
