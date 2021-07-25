#include "AmmoWeapon.h"
#include "core.h"
bool& CAmmoWeapon::ms_bHeadShot = *(bool*)0x7920C8;
void CAmmoWeapon::Reload(int flag)
{
	CallMethod<0x4F9B20, CAmmoWeapon*, int>(this, flag);
}
void CAmmoWeapon::SetAmmo(unsigned int amount)
{
	CallMethod<0x4F8B40, CAmmoWeapon* , unsigned int>(this, amount);
}

void CAmmoWeapon::GetFiringDirection(CVector * dest, float unk, int unk2, int unk3)
{
	CallMethod<0x4F92F0, CAmmoWeapon*, CVector*, float, int, int>(this, dest, unk, unk2, unk3);
}

void CAmmoWeapon::UpdateFiringDirection(float unk)
{
	CallMethod<0x4F96C0, CAmmoWeapon*, float>(this, unk);
}
