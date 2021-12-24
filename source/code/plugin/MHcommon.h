#pragma once
#include "..\manhunt\Vector.h"
#include "..\manhunt\Entity.h"
void CreateEntity(char* name, CVector* pos);
void GiveWeaponToEntity(CEntity* ent, int weaponID);

void GiveWeaponToPlayer(int weaponID);

CEntity* GetHunterAboutToBeExecuted();