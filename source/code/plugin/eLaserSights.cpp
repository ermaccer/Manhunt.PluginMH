#include "eLaserSights.h"
#include "..\manhunt\core.h"
#include "..\manhunt\Player.h"
#include "..\manhunt\Scene.h"
#include "..\manhunt\ColLine.h"
#include "..\manhunt\ContactInfo.h"
#include "..\manhunt\Collectable.h"
#include "..\manhunt\Frontend.h"
#include "..\manhunt\AmmoWeapon.h"


void eLaserSights::Initialize()
{
	Nop(0x487EE3, 8);
	InjectHook(0x487EE3, Hook_Draw, PATCH_JUMP);
}

void eLaserSights::Draw()
{
	CPlayer* plr = (CPlayer*)CScene::FindPlayer();

	if (plr)
	{
		CWeaponCollectable* wep;
		CInventory* inv = plr->m_pInventory;
		eHolsterSlot slot = (eHolsterSlot)plr->m_nCurrentSlot;
		
		if (slot > 0)
		{
			wep = (CWeaponCollectable*)inv->m_inventory[slot];

			if (wep && wep->m_pLaserBone)
			{
				RwMatrix* laserBone = RwFrameGetLTM((RwFrame*)wep->m_pLaserBone);
				RwMatrix* plrMatrix = plr->GetEntityMatrix();
				CVector* pos = (CVector*)&laserBone->pos;
				CVector forward(plrMatrix->at.x, plrMatrix->at.y, plrMatrix->at.z);

				

				CVector target = forward;
				target.y = -(plr->m_fAngle / 47.0f);

				target.Normalise();


				CVector start = *pos;

				CVector end = start;
				end += target * 15.5f;

				//CVector aimPos = {};
				//
				//CWeapon* w = (CWeapon*)*(int*)((int)wep + 428);
				//
				//if (w->m_TypeData->m_eWeaponClass == WC_AMMO)
				//{
				//
				//	CAmmoWeapon* ammo = (CAmmoWeapon*)*(int*)((int)wep + 428);
				//	ammo->GetFiringPoint(&aimPos, 0);
				//}
				//
				//end.x = aimPos.x;
				//end.y = aimPos.y;
				//end.z = aimPos.z;
				//

				CFrontend::LaserDraw(&start, &end);
				CFrontend::LaserDraw(&start, &end);
				CFrontend::LaserDraw(&start, &end);
				CFrontend::LaserDraw(&start, &end);
				CFrontend::LaserDraw(&start, &end);
				CFrontend::LaserDraw(&start, &end);
			}
		}


	}
}

void __declspec(naked) eLaserSights::Hook_Draw()
{
	static int jmp_continue = 0x487EEB;

	_asm {
		pushad
		call eLaserSights::Draw
		popad
		mov     dword ptr[esp + 8], 0
		jmp jmp_continue
	}
}
