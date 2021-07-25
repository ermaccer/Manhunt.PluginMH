#include "EntityManager.h"
#include "core.h"


int& CEntityManager::ms_playerCharacterID = *(int*)0x6A94C0;

CTypeData * CEntityManager::GetEntityTypeDataFromName(char * name)
{
	return CallAndReturn<CTypeData*, 0x437C50, const char*>(name);
}

CEntity * CEntityManager::GetEntity(char * name)
{
	return CallAndReturn<CEntity*, 0x437BE0, const char*>(name);
}

CEntity * CEntityManager::FindInstance(char * name)
{
	return CallAndReturn<CEntity*, 0x437CA0, const char*>(name);
}

void CEntityManager::CreateArchetypes()
{
	Call<0x4381C0>();
}

void CEntityManager::LoadCharacterClumpDict(int skinID)
{
	Call<0x437FB0, int>(skinID);
}
