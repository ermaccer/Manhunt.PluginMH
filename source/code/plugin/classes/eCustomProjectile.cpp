#include "eCustomProjectile.h"
#include "..\..\manhunt\core.h"
#include "..\..\manhunt\SpecialFX.h"
#include "..\..\manhunt\AI.h"
void CCustomProjectile::Spawn(RwMatrix * mat)
{
	CWeaponCollectable* wep = (CWeaponCollectable*)this;
	wep->Spawn(mat);

	if (strcmp(m_TypeData->m_szModel, "Grenade_(CT)") == 0)
	{
		CVector pos = *GetLocation();
		CWeaponManager::CreateAndFireAWeapon("explodingBarrel", &pos, 0);
		FXSystem_Play("Drum_Explode", &pos, 0);

		Destroy();
	}

}

void CCustomProjectileShot::NewDestroy(bool create_weapon)
{
	CWeaponCollectable* wep = *(CWeaponCollectable**)((int)this + 36);

	if (strcmp(wep->m_TypeData->m_szModel, "Grenade_(CT)") == 0)
	{
		// use health as timer
		CEntity* entity = *(CEntity**)((int)this + 32);



		(int)entity->m_fHealth++;

		if ((int)entity->m_fHealth == 1000100)
		{
			Destroy(create_weapon);
		}
	}
	else
		Destroy(create_weapon);

}
