#pragma once
#include "..\manhunt\Vector.h"
#include "..\manhunt\Entity.h"
CEntity* CreateEntity(char* name, CVector* pos);
void GiveWeaponToEntity(CEntity* ent, int weaponID);
void GiveWeaponToPlayer(int weaponID);
void StripAllWeapons(CEntity* ent);

void MakeABodyguard(char* name, int weaponID, CVector* pos = nullptr);


CEntity* GetHunterAboutToBeExecuted();