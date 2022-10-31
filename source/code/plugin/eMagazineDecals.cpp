#include "eMagazineDecals.h"
#include "modloader/eModLoader.h"

CAutoPed* eMagazineDecals::ms_pLastPed = nullptr;

CParticleModel* eMagazineDecals::CreateClipDecal(CAutoPed* ped)
{
	CParticleModel* particle = nullptr;

	CEntity* weapon = (CEntity*)ped->GetCurrentWeapon()->m_pCollectable;
	if (weapon)
	{
		CCollectableTypeData* ctd = (CCollectableTypeData*)weapon->m_pTypeData;
		int modelType = 6;
		const char* magName = GetWeaponClip(ctd->m_nCollectableType);

		if (magName)
		{
			CClump* mag_clump = eModLoader::GetModloaderClump(magName);
			if (mag_clump)
			{
				int clump = (int)mag_clump;

				CVector pos = *weapon->GetLocation();
				CVector null = {};
				float radius = 0.06f;
				float bounce = 0.0f;

				particle = CParticleModel::CreateParticle(modelType, weapon, (int)clump, &pos, (CMatrix*)weapon->GetClumpMatrix(), &null, &null, radius, bounce, 1.0, 0, 0, 0);
				if (particle)
					CParticleModel::RegisterParticle(particle);
			}
		}
		


	}

	return particle;
}

void __declspec(naked) eMagazineDecals::Hook_GetLastReloadingPed()
{
	static int jmp_continue = 0x4B1136;
	static CAutoPed* ent;
	_asm {
		mov ent, ebp
		pushad
	}
	ms_pLastPed = ent;
	_asm {
		popad
		mov     ecx, [ebp + 764]
		jmp jmp_continue
	}
}

void __declspec(naked) eMagazineDecals::Hook_CreateClipDecal()
{
	static int jmp_continue = 0x428D32;
	static CPedTorsoAnimFSM* fsm = nullptr;
	_asm {
		pushad
		mov fsm, edx
	}

	CreateClipDecal((CAutoPed*)fsm->m_pOwner);

	_asm {
		popad
		mov[edx + 128], eax
		jmp		jmp_continue
	}
}

bool eMagazineDecals::IsWeaponAllowed(int id)
{
	if (id == CT_SHOTGUN || id == CT_SHOTGUN_TORCH || id == CT_SAWNOFF)
		return false;
	return true;
}

const char* eMagazineDecals::GetWeaponClip(int id)
{
	switch (id)
	{
	case CT_GLOCK:
	case CT_DESERT_EAGLE:
		return "mag_glock";
		break;
	case CT_UZI:
		return "mag_uzi";
		break;
	case CT_COLT_COMMANDO:
		return "mag_colt";
		break;
	case CT_SNIPER_RIFLE:
		return "mag_sniper";
		break;
	case CT_TRANQ_RIFLE:
		return "mag_tranq";
		break;
	default:
		break;
	}

	return nullptr;
}
