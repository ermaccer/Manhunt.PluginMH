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
