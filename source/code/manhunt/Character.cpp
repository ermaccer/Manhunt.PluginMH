#include "Character.h"
#include "core.h"

void CCharacter::CreateInventoryItem(int collectable, bool settoactive)
{
	CallMethod<0x49A5C0, CCharacter*, int, bool>(this, collectable, settoactive);
}

void CCharacter::UseInventoryCollectable(int unk, int slot)
{
	CallMethod<0x49A3D0, CCharacter*, int, int>(this, unk, slot);
}

CWeapon * CCharacter::GetCurrentWeapon()
{
	return CallMethodAndReturn<CWeapon*,0x49A360, CCharacter*>(this);
}
