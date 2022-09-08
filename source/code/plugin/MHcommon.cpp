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
#include "..\manhunt\Player.h"
#include "..\manhunt\Ped.h"
#include "..\manhunt\Graph.h"

CEntity* CreateEntity(char * name, CVector* pos)
{	
	CTypeData* typeData = CEntityManager::GetEntityTypeDataFromName(name);
	CEntity* entity = nullptr;
	if (!typeData)
	{
		TheConsole.m_messages.push_back("Entity does not exist - " + (std::string)name);
	}
	if (typeData)
	{
		entity = CCreationManager::CreateEntity(typeData);
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

	return entity;
}

void GiveWeaponToEntity(CEntity * ent, int weaponID)
{
	if (ent)
	{
		CCharacter* character = (CCharacter*)ent;
		character->CreateInventoryItem(weaponID, true);
		CInventory* inv = character->m_pInventory;
		CCollectable* item = inv->FindItemWithCollectableType(weaponID);

		CWeapon* wep = (CWeapon*)*(int*)((int)item + 428);

		if (wep->m_TypeData->m_eWeaponClass == WC_AMMO)
		{
			CAmmoWeapon* ammo = (CAmmoWeapon*)*(int*)((int)item + 428);
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

void StripAllWeapons(CEntity * ent)
{
	CCharacter* character = (CCharacter*)ent;



	//for (int i = 0; i < TOTAL_COLLECTABLES; i++)
	//{
	//	CCollectable* item = inv->FindItemWithCollectableType(i);
	///	if (item)
	//		inv->RemoveItem(item);
	//}

}

void MakeABodyguard(char* name, int weaponID, CVector* pos)
{
	CVector position;

	RwMatrix* matrix = CScene::FindPlayer()->GetEntityMatrix();
	CVector forward(matrix->at.x, matrix->at.y, matrix->at.z);
	position = *CScene::FindPlayer()->GetLocation();

	position += forward * 1.5f;


	if (pos)
		position = *pos;


	CAutoPed* bodyguard = (CAutoPed*)CreateEntity(name, &position);
	if (bodyguard)
	{
		if (!(weaponID == CT_FISTS))
		GiveWeaponToEntity(bodyguard, weaponID);
		char line[256] = {};
		sprintf(line, "buddy %s", bodyguard->m_szName);
		ConsoleCommands::ai(line);
	}
}

CEntity * GetHunterAboutToBeExecuted()
{
	CPlayer* plr = (CPlayer*)CScene::FindPlayer();
	CEntity* hunt = *(CEntity**)((int)plr + 0x8B4);

	return hunt;
}
