#include "eCustomPed.h"
#include "..\..\manhunt\core.h"
#include "..\..\core\eSettingsManager.h"
#include "..\.\weapon_adjuster\eWeaponAdjuster.h"
#include "..\..\manhunt\ParticleModel.h"
#include "..\eMagazineDecals.h"
#include "..\..\manhunt\AmmoWeapon.h"

void CPedEx::UseCollectableEx(eCollectableType item, bool createIfDoesntExist)
{
	UseCollectable(CT_NIGHTSTICK, createIfDoesntExist);
}

void CPedEx::ExplodeHeadEx(CVector* pos, int headSelection)
{
	if (eSettingsManager::bFixExplodingDecappedHeads)
	{
		if (m_pPedHead->m_bIsHidden)
			return;
	}

	if (eWeaponAdjuster::ms_bShouldDecapHead)
	{
		CVector newPos = {1.0f, 1.0f, 1.0f};
		SeverHead(&newPos);
		eWeaponAdjuster::ms_bShouldDecapHead = false;
	}
	else
		ExplodeHead(pos, headSelection);
}

void CPedEx::PreUpdateEx()
{
}