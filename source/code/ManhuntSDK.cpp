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

wchar_t * ManhuntFunctions::FastGetText(const char * entry)
{
	return CallMethodAndReturn<wchar_t*, 0x4937E0, int, const char*>(0x725A38, entry);
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

void ManhuntFunctions::AddMenuEntry(wchar_t * name, float posX, float posY, float textScaleX, float textScaleY, int buttonID)
{

    Call<0x5D55C0, wchar_t*, float, float, float, int>(name, posX, posY, textScaleX, textScaleY, buttonID);
	Call<0x5D5B30, wchar_t*, float, float, float, float>(name, posX, posY, textScaleX, textScaleY);
}

void ManhuntFunctions::DrawTexture(float posx, float posy, float scaleX, float scaleY, int r, int g, int b, int a, int pTexture)
{
	Call<0x5F96F0, float, float, float, float, int, int, int, int, int>(posx, posy, scaleX, scaleY, r, g, b, a, pTexture);
}

void ManhuntFunctions::SetDrawRGBA(int r, int g, int b, int a)
{
	int col = b | (g << 8) | (a << 24) | (r << 16);
	*(int*)(0x7D35C0 + 16) = col;
}

void ManhuntFunctions::PrintText(const char * text, float x, float y, float sizex, float sizey, float unk, EFontType font)
{
	Call<0x5E55E0, const char*, float, float, float, float, float, EFontType>(text, x, y, sizex, sizey, unk, font);
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

int MLSOperators::GetParam(int mls)
{
	return CallMethodAndReturn<int, 0x4822A0, int>(mls);
}

int MLSOperators::GetStringParam(int mls)
{
	return CallMethodAndReturn<int, 0x4822E0,int>(mls);
}

CFile * ManhuntFileFunctions::Rockstar_fopen(int mode, int fMode, char* extraParam)
{
	return CallAndReturn<CFile*, 0x6121A0, int, int, char*>(mode, fMode, extraParam);
}

int ManhuntFileFunctions::ReadFileBytes(CFile * src, int dst, int size)
{
	return CallAndReturn<int, 0x611C80, CFile*, int, int>(src, dst, size);
}
