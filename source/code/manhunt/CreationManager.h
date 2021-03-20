#pragma once
#include "Entity.h"

class CCreationManager {
public:
	static CEntity* CreateEntity(CTypeData* data);
};