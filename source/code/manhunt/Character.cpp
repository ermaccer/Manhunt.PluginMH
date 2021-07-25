#include "Character.h"
#include "core.h"

void CCharacter::CreateInventoryItem(CEntity * entity, int collectable, bool settoactive)
{
	CallMethod<0x49A5C0, CEntity*, int, bool>(entity, collectable, settoactive);
}

CWeapon * CCharacter::GetCurrentWeapon()
{
	return CallMethodAndReturn<CWeapon*,0x49A360, CCharacter*>(this);
}
