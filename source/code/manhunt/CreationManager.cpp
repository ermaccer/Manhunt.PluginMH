#include "CreationManager.h"
#include "core.h"

CEntity * CCreationManager::CreateEntity(CTypeData * data)
{
	return CallAndReturn<CEntity*, 0x42DD60, CTypeData*>(data);
}
