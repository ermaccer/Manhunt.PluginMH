#include "Collectable.h"
#include "core.h"

char tempBuffer[256];

wchar_t * CCollectable::GetNameKey16(int id)
{
	return CallAndReturn<wchar_t*, 0x4C5870, int>(id);
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
