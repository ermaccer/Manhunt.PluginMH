#include "MHcommon.h"
#include "..\manhunt\core.h"
#include "..\manhunt\Vector.h"
#include "..\manhunt\EntityManager.h"
#include "..\manhunt\CreationManager.h"
#include "..\plugin\console\eConsole.h"
#include "..\manhunt\Character.h"
#include "..\manhunt\AmmoWeapon.h"
#include "..\manhunt\Inventory.h"
#include "..\manhunt\Scene.h"
#include "..\manhunt\AI.h"

void CreateEntity(char * name, CVector* pos)
{
	
	CTypeData* typeData = CEntityManager::GetEntityTypeDataFromName(name);

	if (!typeData)
	{
		TheConsole.m_messages.push_back("Entity does not exist - " + (std::string)name);
	}
	if (typeData)
	{
		CEntity* entity = CCreationManager::CreateEntity(typeData);
		if (entity)
		{
			char ent[256];
			char tmp[256];
			sprintf(ent, "%s%d",name,TheConsole.m_entityID);
			entity->SetName(ent);
			sprintf(tmp, "Created - %s [%x] [%s]", name, entity, ent);
			TheConsole.m_messages.push_back(tmp);
			entity->SetFrozen(0);
			entity->Spawn(pos, 0);
			TheConsole.m_entityID++;
		}
	}
}

void GiveWeaponToEntity(CEntity * ent, int weaponID)
{
	if (ent)
	{
		CCharacter::CreateInventoryItem(ent, weaponID, true);
		int inventory_handle = *(int*)((int)ent + 336);
		int item = CInventory::FindItemWithCollectableType(inventory_handle, weaponID);

		CWeapon* wep = (CWeapon*)*(int*)(item + 428);

		if (wep->m_TypeData->m_eWeaponClass == WC_AMMO)
		{
			CAmmoWeapon* ammo = (CAmmoWeapon*)*(int*)(item + 428);
			ammo->SetAmmo(1000);
		}



		char tmp[256];
		sprintf(tmp, "[%x] - Weapon %d spawned", ent, weaponID);
		TheConsole.m_messages.push_back(tmp);
	}
}

void GiveWeaponToPlayer(int weaponID)
{
	GiveWeaponToEntity(CScene::FindPlayer(), weaponID);
}
