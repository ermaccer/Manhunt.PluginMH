#pragma once
#include "..\manhunt\ParticleModel.h"
#include "..\manhunt\Ped.h"

class eMagazineDecals {
public:
	static CAutoPed* ms_pLastPed;

	static CParticleModel* CreateClipDecal(CAutoPed* ped);

	static void Hook_GetLastReloadingPed();
	static void Hook_CreateClipDecal();

	static bool IsWeaponAllowed(int id);

	static const char* GetWeaponClip(int id);

};
