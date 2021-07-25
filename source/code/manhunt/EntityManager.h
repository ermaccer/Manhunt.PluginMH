#pragma once
#include"Entity.h"

class CEntityManager {
public:
	static int& ms_playerCharacterID;
	static CTypeData* GetEntityTypeDataFromName(char* name);
	static CEntity* GetEntity(char* name);
	static CEntity* FindInstance(char* name);
	static void     CreateArchetypes();

	static void		LoadCharacterClumpDict(int skinID);

};