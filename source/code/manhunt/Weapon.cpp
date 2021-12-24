#include "Weapon.h"
#include "String.h"
#include "core.h"

void CWeaponManager::CreateAndFireAWeapon(const char* name, CVector * pos, CVector * dir)
{
	CString str(name);
	Call<0x4FACC0, CString*, CVector*, CVector*>(&str, pos, dir);
}
