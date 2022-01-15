#include "Collectable.h"
#include "core.h"

char tempBuffer[256] = {};

wchar_t * CCollectable::GetNameKey16(int id)
{
	wchar_t* result = CallAndReturn<wchar_t*, 0x4C5870, int>(id);
	return result;
}

void CCollectable::GetNameStringFromType(int weaponID, char * dest)
{
	Call<0x4C67F0, int, char*>(weaponID, dest);
}

char * CCollectable::FastGetNameStringFromType(int weaponID)
{
	Call<0x4C67F0, int, int>(weaponID, (int)&tempBuffer);
	return tempBuffer;
}

eCollectableType CCollectable::GetTypeFromNameString(char * string)
{
	return CallAndReturn<eCollectableType, 0x4C5A90, char*>(string);
}

void CCollectable::Drop()
{
	CallMethod<0x4CABE0, CCollectable*>(this);
}

eCollectableType CCollectable::GetCollectableType()
{
	return CallMethodAndReturn<eCollectableType, 0x4C6F10, CCollectable*>(this);
}

void CWeaponCollectable::Spawn(RwMatrix * mat)
{
	CallMethod<0x4CAEA0, CEntity*, RwMatrix*>(this, mat);
}

void CWeaponCollectable::Drop()
{
	CallMethod<0x4CABE0, CWeaponCollectable*>(this);
}
