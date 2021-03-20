#pragma once
#include "Entity.h"
#include "Collectable.h"

class CCharacter {
public:
	static void CreateInventoryItem(CEntity* entity, int collectable, bool settoactive);
};