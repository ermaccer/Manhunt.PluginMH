#pragma once
#include"Entity.h"

class CEntityManager {
public:
	static int& ms_playerCharacterID;
	static bool& ms_disableHunters;
	static CTypeData* GetEntityTypeDataFromName(char* name);
	static CEntity* GetEntity(char* name);
	static CEntity* FindInstance(char* name);

	static void     CreateArchetypes();
	static void     CreateEntityTypesFromIni();

	static void		LoadCharacterClumpDict(int skinID);
	static void		ShutDown();

};