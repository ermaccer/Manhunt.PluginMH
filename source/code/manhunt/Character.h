#pragma once
#include "Entity.h"
#include "Collectable.h"
#include "Weapon.h"
enum eCharacterVoiceType {
	VOICE_NONE,
	HOODED_SMALL,
	HOODED_MEDIUM,
	HOODED_BIG,
	INNOCENT_SMALL,
	INNOCENT_MEDIUM,
	INNOCENT_BIG,
	WARDOG_SMALL,
	WARDOG_MEDIUM,
	WARDOG_BIG,
	SMILEY_SMALL,
	SMILEY_MEDIUM,
	SMILEY_BIG,
	SKINZ_SMALL,
	SKINZ_MEDIUM,
	SKINZ_BIG,
	POLICE_SMALL,
	POLICE_MEDIUM,
	POLICE_BIG,
	CERBERUS,
	TRAMP,
	JOURNALIST,
	BUNNY,
	CERBERUS_LEADER,
	PIGGSY,
	RAMIREZ,
	MONKEY,
	DIRECTOR
};

class CCharacter {
public:
	static void CreateInventoryItem(CEntity* entity, int collectable, bool settoactive);

	CWeapon* GetCurrentWeapon();
};