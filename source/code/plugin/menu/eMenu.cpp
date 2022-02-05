#include "eMenu.h"
#include <Windows.h>
#include <string>

// manhunt includes

#include "..\..\manhunt\Inventory.h"
#include "..\..\manhunt\Cheats.h"
#include "..\..\manhunt\Frontend.h"
#include "..\..\manhunt\Renderer.h"
#include "..\..\manhunt\EntityManager.h"
#include "..\..\manhunt\Collectable.h"
#include "..\..\manhunt\Anim.h"
#include "..\..\manhunt\Scene.h"
#include "..\..\manhunt\Inventory.h"
#include "..\..\manhunt\Character.h"
#include "..\..\manhunt\AmmoWeapon.h"
#include "..\..\manhunt\Player.h"
#include "..\..\manhunt\Weather.h"
#include "..\..\manhunt\String.h"
#include "..\..\manhunt\SpecialFX.h"
#include "..\..\manhunt\AI.h"
#include "..\..\manhunt\Ped.h"
#include "..\..\manhunt\PtrList.h"
#include "..\..\manhunt\Graph.h"
#include "..\..\manhunt\Camera.h"
#include "..\..\manhunt\MusicManager.h"

#include "..\..\core\eSettingsManager.h"
#include "..\..\core\eMain.h"
#include "..\..\plugin\eCustomAnimManager.h"
#include "..\..\plugin\console\eConsole.h"
#include "..\..\manhunt\core.h"
#include "..\..\..\IniReader.h"
#include "..\eMapLimits.h"
#include "..\MHcommon.h"


// custom


char& bTimer = *(char*)0x7D5A08;
char& bActivateTimer = *(char*)0x7D5A0C;
char& bBodyCount = *(char*)0x7D5A18;

char msgBuffer[256];
char buffer[256];
eMenu TheMenu;


void eMenu::PreInitialize()
{
	CIniReader ini("");

	KeyEnableMenu = ini.ReadInteger("Keys.Menu", "keyMenuEnable", VK_F2);
	KeyMenuExecute = ini.ReadInteger("Keys.Menu", "keyMenuExecute", VK_RETURN);
	KeyMenuGoBack = ini.ReadInteger("Keys.Menu", "keyMenuBack", VK_BACK);
	KeyMenuItemDOWN = ini.ReadInteger("Keys.Menu", "keyMenuDown", VK_DOWN);
	KeyMenuItemUP = ini.ReadInteger("Keys.Menu", "keyMenuUp", VK_UP);
	KeyMenuItemLEFT = ini.ReadInteger("Keys.Menu", "keyMenuLeft", VK_LEFT);
	KeyMenuItemRIGHT = ini.ReadInteger("Keys.Menu", "keyMenuRight", VK_RIGHT);
}

void eMenu::Initialize()
{
	Clear();
	savedPosition = { 0,0,0 };

	AddToggleIntEntry("Infinite Health", &m_infiniteHealth);
	AddToggleIntEntry("God Mode", &m_godMode);
	AddToggleIntEntry("Fall Damage", &m_fallDamage);
	AddFunctionEntry("Save Position", SavePosition);
	AddFunctionEntry("Load Position", LoadPosition);
	AddToggleIntEntry("Display Coordinates", &m_displayCoords);
	AddToggleIntEntry("Use INST Coordinates For Display", &m_displayRealCoords);
	AddToggleIntEntry("Display Saved Position", &m_displayPositionMarker);
	AddFunctionEntry("Drop All Weapons", PlayerDropAllWeapons);
	AddFunctionEntry("Make AI Ignore Player", AISENSES_IgnorePlayer);
	AddCategory("Player");


	// pistols
	AddWeaponEntry(CT_6SHOOTER);
	AddWeaponEntry(CT_GLOCK);
	AddWeaponEntry(CT_DESERT_EAGLE);
	AddWeaponEntry(CT_UZI);
	AddWeaponEntry(CT_NAILGUN);
	AddWeaponEntry(CT_TRANQ_RIFLE);
	// rifles
	AddWeaponEntry(CT_SHOTGUN);
	AddWeaponEntry(CT_SHOTGUN_TORCH);
	AddWeaponEntry(CT_COLT_COMMANDO);
	AddWeaponEntry(CT_SNIPER_RIFLE);
	AddWeaponEntry(CT_SAWNOFF);
	// melee
	AddWeaponEntry(CT_BASEBALL_BAT);
	AddWeaponEntry(CT_BASEBALL_BAT_BLADES);
	AddWeaponEntry(CT_W_BASEBALL_BAT);
	AddWeaponEntry(CT_CROWBAR);
	AddWeaponEntry(CT_SICKLE);
	AddWeaponEntry(CT_NIGHTSTICK);
	AddWeaponEntry(CT_CAN);
	AddWeaponEntry(CT_BOTTLE);
	AddWeaponEntry(CT_BRICK_HALF);
	AddWeaponEntry(CT_WIRE);
	AddWeaponEntry(CT_SHARD);
	AddWeaponEntry(CT_HAMMER);
	AddWeaponEntry(CT_CLEAVER);
	AddWeaponEntry(CT_SMALL_BAT);
	AddWeaponEntry(CT_ICEPICK);
	AddWeaponEntry(CT_AXE);
	AddWeaponEntry(CT_KNIFE);
	AddWeaponEntry(CT_MACHETE);
	AddWeaponEntry(CT_WOODEN_SPIKE);
	AddWeaponEntry(CT_CHAINSAW);
	AddWeaponEntry(CT_CHAINSAW_PLAYER);
	AddWeaponEntry(CT_PIGSY_WIRE);
	AddWeaponEntry(CT_PIGSY_SHARD);
	AddWeaponEntry(CT_BAG);

	AddCategory("Weapons", true);


	int list = *(int*)0x69BBC4;
	CEntity* entity = nullptr;
	do
	{
		if (list)
			entity = *(CEntity**)(list);
		else
			entity = 0;
		if (list)
			list = *(int*)(list + 8);

		if (entity)
			AddEntityEntry(entity->m_pTypeData->m_szRecordName);


	} while (entity);

	AddEntitiesCategory("Entities");


	AddToggleCharEntry("Timer", &bTimer);
	AddToggleCharEntry("Body Count", &bBodyCount);
	AddToggleIntEntry("Enable Body Count", &m_enableKillCounter);
	AddToggleIntEntry("Hide Lock-on Triangles (use with free cam)", &m_disableLockOnTriangles);
	AddCategory("HUD");


	AddToggleCharEntry("Cheats Active", (char*)&CCheatHandler::m_bCheatsActive);
	AddToggleIntEntry("Helium Hunters", &CCheatHandler::m_heliumHunters);
	AddToggleIntEntry("Runner", &CCheatHandler::m_runner);
	AddToggleIntEntry("Regenerate", &CCheatHandler::m_regenerate);
	AddToggleIntEntry("Invisiblity", &CCheatHandler::m_invisibility);
	AddToggleIntEntry("Super Punch", &CCheatHandler::m_superPunch);

	AddCategory("Cheats");

	if (eSettingsManager::bIncreaseMapLimits)
		AddToggleIntEntry("New Material Manager Debug", &m_materialManagerDebug);

	AddToggleIntEntry("Hide Moon", &m_hideMoon);
	AddToggleIntEntry("Hide Stars", &m_hideStars);

	AddCategory("World");

	AddSliderFloatEntry("Camera Offset X", &TheCamera.m_vCameraOffsets.x, -INT_MAX, INT_MAX);
	AddSliderFloatEntry("Camera Offset Y", &TheCamera.m_vCameraOffsets.y, -INT_MAX, INT_MAX);
	AddSliderFloatEntry("Camera Offset Z", &TheCamera.m_vCameraOffsets.z, -INT_MAX, INT_MAX);
	AddSliderFloatEntry("Aim Camera Offset X", &TheCamera.m_vAimingCameraOffset.x, -INT_MAX, INT_MAX);
	AddSliderFloatEntry("Aim Camera Offset Y", &TheCamera.m_vAimingCameraOffset.y, -INT_MAX, INT_MAX);
	AddSliderFloatEntry("Aim Camera Offset Z", &TheCamera.m_vAimingCameraOffset.z, -INT_MAX, INT_MAX);
	AddSliderFloatEntry("Free Camera Rotation Speed", &CCamera::ms_freeCameraRotationSpeed, -INT_MAX, INT_MAX);
	AddSliderFloatEntry("Free Camera Speed", &CCamera::ms_freeCameraSpeed, -INT_MAX, INT_MAX);
	AddCategory("Camera");

	AddFunctionEntry("Free",	CWeather::SetWeatherFree);
	AddFunctionEntry("Clear",	CWeather::SetWeatherClear);
	AddFunctionEntry("Cloudy",	CWeather::SetWeatherCloudy);
	AddFunctionEntry("Thunder", CWeather::SetWeatherThunder);
	AddFunctionEntry("Rainy",	CWeather::SetWeatherRainy);
	AddFunctionEntry("Foggy",	CWeather::SetWeatherFoggy);
	AddFunctionEntry("Windy",	CWeather::SetWeatherWindy);
	AddCategory("Weather");

	AddToggleIntEntry("Log Gamepad",&m_controllerDebug);
	AddToggleIntEntry("Silence Firearms", &m_silenceWeapons);
	AddToggleIntEntry("Infinite Ammo", &m_infiniteAmmo);
	AddFunctionEntry("Set Difficulty To Fetish", SetDifficultyEasy);
	AddFunctionEntry("Set Difficulty To Hardcore", SetDifficultyHard);
	AddFunctionEntry("Place Bag On Head", PutBagOnPlayerHead);
	AddToggleIntEntry("Execution Debug", &m_displayHunter);
	AddToggleCharEntry("Disable Hunters", (char*)&CEntityManager::ms_disableHunters);
	AddCategory("Misc.");
}

void eMenu::ProcessMenu()
{
	if (m_infiniteHealth)
	{
		if (CScene::FindPlayer())
		{
			CScene::FindPlayer()->m_fHealth = 100.0f;
		}
	}
	if (CScene::FindPlayer())
		CScene::FindPlayer()->SetFlag(0x100, m_godMode);

	if (m_displayHunter)
	{
		CPlayer* plr = (CPlayer*)CScene::FindPlayer();
		if (plr)
		{
			CHunter* hunter = plr->m_pExecuteHunter;

			if (hunter)
				sprintf(buffer, "Execute: %s Time: %f Stage: %d", hunter->m_pTypeData->m_szRecordName, plr->m_fExecuteTime, plr->GetExecuteStage());
			else
				sprintf(buffer, "No Entity to execute");

			CFrontend::SetDrawRGBA(0, 0, 0, 255);
			CFrontend::Print8(buffer, 0.15f + 0.005f, 0.005f, 0.5, 0.5, 0.0, FONT_TYPE_DEFAULT);
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
			CFrontend::Print8(buffer, 0.15f, 0, 0.5, 0.5, 0.0, FONT_TYPE_DEFAULT);
		}
	}

	if (m_enableKillCounter)
		CFrontend::ms_cnt = *(int*)0x7B7D84 + *(int*)0x7B7DA0;


	if (!m_fallDamage)
	{
		Patch<float>(0x4313F7 + 3,100.0f);
		Patch<float>(0x43152B + 3,100.0f);
	}
	else
	{
		Patch<float>(0x4313F7 + 3,-1.0f);
		Patch<float>(0x43152B + 3,-1.0f);
	}

	if (m_silenceWeapons)
		Patch<char>(0x4C9C92 + 1, 8);
	else
		Patch<char>(0x4C9C92 + 1, 7);


	if (m_infiniteAmmo)
		Patch<char>(0x4F9073 + 6, 0);
	else
		Patch<char>(0x4F9073 + 6, 1);

	if (m_disableLockOnTriangles)
		Patch<float>(0x728138, 0.0f);
	else
		Patch<float>(0x728138, 0.5f);

	if (m_hideMoon)
		Nop(0x5CB59D, 5);
	else
		InjectHook(0x5CB59D, CRenderer::DrawQuad2d, PATCH_CALL);

	if (m_hideStars)
		Nop(0x5CB81D, 5);
	else
		InjectHook(0x5CB81D, CRenderer::DrawQuad2dSet, PATCH_CALL);

	if (m_displayCoords)
	{
		CVector* pos = CScene::FindPlayer()->GetLocation();
		if (m_displayRealCoords)
			sprintf(buffer, "(INST) X: %.3f Y: %.3f Z: %.3f", pos->x, pos->z * -1.0f, pos->y);
		else
			sprintf(buffer, "X: %.3f Y: %.3f Z: %.3f", pos->x, pos->y, pos->z);
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(buffer, 0.552f, 0, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(buffer, 0.554f, 0, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}


	if (m_controllerDebug)
	{
		sprintf(buffer, "GAMEPAD BUTTON 0x%X", *(short*)0x725684);
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(buffer, 0.152f, 0.5, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(180, 255, 180, 255);
		CFrontend::Print8(buffer, 0.154f, 0.5f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);

		sprintf(buffer, "ANALOG STICK %d", *(short*)(0x725684 + 2));
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(buffer, 0.152f, 0.55, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(180, 255, 180, 255);
		CFrontend::Print8(buffer, 0.154f, 0.55f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);


		sprintf(buffer, "STICK STATES %f %f", *(float*)0x725674 ,*(float*)0x725678);
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(buffer, 0.152f, 0.6, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(180, 255, 180, 255);
		CFrontend::Print8(buffer, 0.154f, 0.6f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}


	if (m_displayPositionMarker)
	{
		sprintf(buffer, "X: %.3f Y: %.3f Z: %.3f", savedPosition.x,savedPosition.y,savedPosition.z);
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(buffer, 0.552f, 0.1f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(buffer, 0.554f, 0.1f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}

	if (m_materialManagerDebug)
	{
		sprintf(buffer, "Materials = %d/%d Missing Materials = %d", gNewCollisionMaterialManager.m_numWorldMaterials, AMOUNT_OF_MATERIALS, gNewCollisionMaterialManager.m_numMissingMaterials);
		CFrontend::SetDrawRGBA(255, 255,255, 255);
		CFrontend::Print8(buffer, 0.1f, 0, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}


	if (m_active)
	{
		DrawMenu();

		if (IsWindowFocused())
			ProcessControls();
	}


}


void eMenu::ProcessControls()
{
	if (iCurrentPage + 1 > vCategories[iCurrentCategory].vPages.size()) iCurrentPage = 0;
	if (iCurrentPage < 0) iCurrentPage = vCategories[iCurrentCategory].vPages.size() - 1;
	if (iCurrentCategory + 1 > vCategories.size()) iCurrentCategory = 0;
	if (iCurrentCategory < 0) iCurrentCategory = vCategories.size() - 1;
}

void eMenu::OnKeyLeft()
{
	if (m_bSelectedOption)
	{
		if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsAdjustable)
		{
			*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrIntValue -= vCategories[iCurrentCategory].vItems[iCurrentItem].iStep;

			if (*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrIntValue < vCategories[iCurrentCategory].vItems[iCurrentItem].iAdjustMin)
				*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrIntValue = vCategories[iCurrentCategory].vItems[iCurrentItem].iAdjustMin;
		}
		if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsAdjustableFloat)
		{
			*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrFloatValue -= vCategories[iCurrentCategory].vItems[iCurrentItem].fStep;

			if (*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrFloatValue < vCategories[iCurrentCategory].vItems[iCurrentItem].fAdjustMin)
				*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrFloatValue = vCategories[iCurrentCategory].vItems[iCurrentItem].fAdjustMin;
		}
	}
	else
	{
		if (vCategories[iCurrentCategory].vPages.size() > 0)
		{
			iCurrentItem = 0;
			iCurrentPage--;
		}
	}

}

void eMenu::OnKeyRight()
{
	if (m_bSelectedOption)
	{
		if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsAdjustable)
		{
			*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrIntValue += vCategories[iCurrentCategory].vItems[iCurrentItem].iStep;

			if (*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrIntValue > vCategories[iCurrentCategory].vItems[iCurrentItem].iAdjustMax)
				*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrIntValue = vCategories[iCurrentCategory].vItems[iCurrentItem].iAdjustMax;
		}
		if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsAdjustableFloat)
		{
			*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrFloatValue += vCategories[iCurrentCategory].vItems[iCurrentItem].fStep;

			if (*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrFloatValue > vCategories[iCurrentCategory].vItems[iCurrentItem].fAdjustMax)
				*vCategories[iCurrentCategory].vItems[iCurrentItem].ptrFloatValue = vCategories[iCurrentCategory].vItems[iCurrentItem].fAdjustMax;
		}
	}
	else
	{
		if (vCategories[iCurrentCategory].vPages.size() > 0)
		{
			iCurrentItem = 0;
			iCurrentPage++;
		}
	}
}

void eMenu::OnKeyDown()
{
	if (m_bSelectedOption)
		return;

	if (m_bCategoryOpen && vCategories[iCurrentCategory].bHasItems)
	{
		iCurrentItem++;
		if (iCurrentItem + 1 > iTotalItems)
			iCurrentItem = 0;

	}
	else
		iCurrentCategory++;
}

void eMenu::OnKeyUp()
{
	if (m_bSelectedOption)
		return;

	if (m_bCategoryOpen && vCategories[iCurrentCategory].bHasItems)
	{

		iCurrentItem--;
		if (iCurrentItem < 0)
			iCurrentItem = iTotalItems - 1;
	}

	else
		iCurrentCategory--;
}

void eMenu::OnKeyExecute()
{
	if (!m_bCategoryOpen && !m_bNavigatingCategory)
	{
		if (vCategories[iCurrentCategory].bHasItems && vCategories[iCurrentCategory].vItems.size() > 0)
		{
			if (vCategories[iCurrentCategory].bIsWeapon)
			{
				vCategories[iCurrentCategory].vWeapons.clear();
				vCategories[iCurrentCategory].bHasBeenWeaponsPopulated = false;

			}
			vTempPages.clear();
			vCategories[iCurrentCategory].vPages.clear();
			vCategories[iCurrentCategory].bHaveBeenPagesCalculated = false;
			m_bCategoryOpen = true;
			m_bPressedEnter = true;
			m_bNavigatingCategory = true;
		}

	}

	else if (m_bNavigatingCategory && m_bCategoryOpen)
	{
		if (vCategories[iCurrentCategory].bIsWeapon && vCategories[iCurrentCategory].bHasBeenWeaponsPopulated)
		{
			int weapon = iCurrentItem + vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;
			if (vCategories[iCurrentCategory].vWeapons[weapon].bIsWeapon)
				GiveWeaponToPlayer(vCategories[iCurrentCategory].vWeapons[weapon].iWeaponID);

		}
		if (vCategories[iCurrentCategory].bIsEntities && vCategories[iCurrentCategory].bHasBeenEntitiesPopulated)
		{
			int entity = iCurrentItem + vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;
			if (vCategories[iCurrentCategory].vEntities[entity].bIsEntity)
			{
				CEntity* plr = CScene::FindPlayer();
				RwMatrix* matrix = plr->GetEntityMatrix();

				CVector forward(matrix->at.x, matrix->at.y, matrix->at.z);
				CVector pos = *plr->GetLocation();

				pos += forward * 1.5f;

				CreateEntity((char*)vCategories[iCurrentCategory].vEntities[entity].strEntity.c_str(), &pos);
			}

		}

		if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsFunction)
		{
			int item = iCurrentItem + vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;
			vCategories[iCurrentCategory].vItems[item].fFunc();
		}
		if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsCharToggle || vCategories[iCurrentCategory].vItems[iCurrentItem].bIsShortToggle
			|| vCategories[iCurrentCategory].vItems[iCurrentItem].bIsIntegerToggle)
		{
			int item = iCurrentItem + vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;

			if (vCategories[iCurrentCategory].vItems[item].bIsCharToggle)
			{
				*vCategories[iCurrentCategory].vItems[item].ptrCharValue ^= 1;
			}
			if (vCategories[iCurrentCategory].vItems[item].bIsIntegerToggle)
			{
				*vCategories[iCurrentCategory].vItems[item].ptrIntValue ^= 1;
			}
		}

		if (vCategories[iCurrentCategory].vItems[iCurrentItem].bIsAdjustable || vCategories[iCurrentCategory].vItems[iCurrentItem].bIsAdjustableFloat)
		{
			m_bSelectedOption ^= 1;
		}

	}
}

void eMenu::OnKeyGoBack()
{
	if (m_bCategoryOpen)
	{
		if (vCategories[iCurrentCategory].bIsWeapon)
		{
			vCategories[iCurrentCategory].vWeapons.clear();
			vTempWeapons.clear();
			vCategories[iCurrentCategory].bHasBeenWeaponsPopulated = false;

		}
		m_bCategoryOpen = false;
		m_bNavigatingCategory = false;
		vTempPages.clear();
		vCategories[iCurrentCategory].vPages.clear();
		vCategories[iCurrentCategory].bHaveBeenPagesCalculated = false;
		iCurrentItem = 0;

		if (m_bSelectedOption)
			m_bSelectedOption = false;
	}

	
}

void eMenu::OnKeyToggle()
{
	m_active ^= 1;
	iCurrentCategory = 0;
	iCurrentItem = 0;
	m_bCategoryOpen = false;
	m_bNavigatingCategory = false;
	m_bSelectedOption = false;
	vCategories[iCurrentCategory].vPages.clear();
	vCategories[iCurrentCategory].vWeapons.clear();
	vTempPages.clear();
	vTempWeapons.clear();
}

void eMenu::DrawMenu()
{
	if (m_active)
	{
		for (int i = 0; i < vCategories.size(); i++)
		{
			CFrontend::SetDrawRGBA(0, 0, 0, 255);
			CFrontend::Print8(vCategories[i].strName.c_str(), 0.052f, 0.102f + 0.04 * i, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
			if (i == iCurrentCategory)
				CFrontend::SetDrawRGBA(51, 153, 255, 255);
			else
				CFrontend::SetDrawRGBA(255, 255, 255, 255);
			CFrontend::Print8(vCategories[i].strName.c_str(), 0.050f, 0.10f + 0.04 * i, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);

			// draw sub items
			if (vCategories[i].bHasItems && m_bCategoryOpen)
			{
				if (i == iCurrentCategory)
				{
					if (vCategories[i].bIsWeapon)
					{
						if (!vCategories[i].bHasBeenWeaponsPopulated)
						{
							for (int j = 0; j < vCategories[i].vItems.size(); j++)
							{
								if (vCategories[i].vItems[j].bIsWeapon)
								{
									if (CEntityManager::GetEntityTypeDataFromName(CCollectable::FastGetNameStringFromType(vCategories[i].vItems[j].iWeaponID)))
										vTempWeapons.push_back(vCategories[i].vItems[j]);
								}
							}
							vCategories[i].vWeapons = vTempWeapons;
							vCategories[i].bHasBeenWeaponsPopulated = true;
						}

						if (!vCategories[iCurrentCategory].bHaveBeenPagesCalculated)
						{
							eMenuPage page;
							int itemCounter = 0;
							int fullPages = vCategories[iCurrentCategory].vWeapons.size() / 16;
							int leftOver = vCategories[iCurrentCategory].vWeapons.size() % 16;
							int lastEnd = 0;
							page.iStart = 0;
							for (int p = 0; p < vCategories[iCurrentCategory].vWeapons.size(); p++)
							{
								if (itemCounter >= 16)
								{
									page.iEnd = p;
									page.iStart += lastEnd;
									lastEnd = page.iEnd - page.iStart;
									itemCounter = 0;
									vTempPages.push_back(page);
								}
								itemCounter++;
							}
							page.iEnd = vCategories[iCurrentCategory].vWeapons.size();
							page.iStart = vCategories[iCurrentCategory].vWeapons.size() - leftOver;
							vTempPages.push_back(page);
							vCategories[iCurrentCategory].vPages = vTempPages;
							vCategories[iCurrentCategory].bHaveBeenPagesCalculated = true;
						}
						iTotalItems = vCategories[iCurrentCategory].vPages[iCurrentPage].iEnd - vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;

						for (int j = vCategories[iCurrentCategory].vPages[iCurrentPage].iStart; j < vCategories[iCurrentCategory].vPages[iCurrentPage].iEnd; j++)
						{
							iActualItemID = j;
							std::string entry = vCategories[i].vWeapons[j].name.c_str();
							CFrontend::SetDrawRGBA(0, 0, 0, 255);
							CFrontend::Print8(entry.c_str(), 0.138f, 0.102f + 0.04 * (j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)), 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
							if ((j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)) == iCurrentItem)
								CFrontend::SetDrawRGBA(51, 153, 255, 255);
							else
								CFrontend::SetDrawRGBA(255, 255, 255, 255);
							CFrontend::Print8(entry.c_str(), 0.136f, 0.10f + 0.04 * (j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)), 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
						}
						if (vCategories[iCurrentCategory].vPages.size() > 1)
						{
							sprintf(msgBuffer, "Page %d/%d", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
							CFrontend::SetDrawRGBA(0, 0, 0, 255);
							CFrontend::Print8(msgBuffer, 0.126f, 0.812f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
							CFrontend::SetDrawRGBA(255, 255, 255, 255);
							CFrontend::Print8(msgBuffer, 0.124f, 0.810f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
						}

					}
					else if (vCategories[i].bIsEntities)
					{
						if (!vCategories[i].bHasBeenEntitiesPopulated)
						{
							for (int j = 0; j < vCategories[i].vItems.size(); j++)
							{
								if (vCategories[i].vItems[j].bIsEntity)
								{
									if (CEntityManager::GetEntityTypeDataFromName((char*)vCategories[i].vItems[j].strEntity.c_str()));
										vTempEntities.push_back(vCategories[i].vItems[j]);
								}
							}
							vCategories[i].vEntities = vTempEntities;
							vCategories[i].bHasBeenEntitiesPopulated = true;
						}

						if (!vCategories[iCurrentCategory].bHaveBeenPagesCalculated)
						{
							eMenuPage page;
							int itemCounter = 0;
							int fullPages = vCategories[iCurrentCategory].vEntities.size() / 16;
							int leftOver = vCategories[iCurrentCategory].vEntities.size() % 16;
							int lastEnd = 0;
							page.iStart = 0;
							for (int p = 0; p < vCategories[iCurrentCategory].vEntities.size(); p++)
							{
								if (itemCounter >= 16)
								{
									page.iEnd = p;
									page.iStart += lastEnd;
									lastEnd = page.iEnd - page.iStart;
									itemCounter = 0;
									vTempPages.push_back(page);
								}
								itemCounter++;
							}
							page.iEnd = vCategories[iCurrentCategory].vEntities.size();
							page.iStart = vCategories[iCurrentCategory].vEntities.size() - leftOver;
							vTempPages.push_back(page);
							vCategories[iCurrentCategory].vPages = vTempPages;
							vCategories[iCurrentCategory].bHaveBeenPagesCalculated = true;
						}
						iTotalItems = vCategories[iCurrentCategory].vPages[iCurrentPage].iEnd - vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;

						for (int j = vCategories[iCurrentCategory].vPages[iCurrentPage].iStart; j < vCategories[iCurrentCategory].vPages[iCurrentPage].iEnd; j++)
						{
							iActualItemID = j;
							std::string entry = vCategories[i].vEntities[j].name.c_str();
							CFrontend::SetDrawRGBA(0, 0, 0, 255);
							CFrontend::Print8(entry.c_str(), 0.138f, 0.102f + 0.04 * (j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)), 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
							if ((j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)) == iCurrentItem)
								CFrontend::SetDrawRGBA(51, 153, 255, 255);
							else
								CFrontend::SetDrawRGBA(255, 255, 255, 255);
							CFrontend::Print8(entry.c_str(), 0.136f, 0.10f + 0.04 * (j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)), 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
						}
						if (vCategories[iCurrentCategory].vPages.size() > 1)
						{
							sprintf(msgBuffer, "Page %d/%d", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
							CFrontend::SetDrawRGBA(0, 0, 0, 255);
							CFrontend::Print8(msgBuffer, 0.126f, 0.812f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
							CFrontend::SetDrawRGBA(255, 255, 255, 255);
							CFrontend::Print8(msgBuffer, 0.124f, 0.810f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
						}

					}
					else
					{
						iTotalItems = vCategories[i].vItems.size();

						if (!vCategories[iCurrentCategory].bHaveBeenPagesCalculated)
						{
							eMenuPage page;
							int itemCounter = 0;
							int fullPages = vCategories[iCurrentCategory].vItems.size() / 16;
							int leftOver = vCategories[iCurrentCategory].vItems.size() % 16;
							int lastEnd = 0;
							page.iStart = 0;
							for (int p = 0; p < vCategories[iCurrentCategory].vItems.size(); p++)
							{
								if (itemCounter >= 16)
								{
									page.iEnd = p;
									page.iStart += lastEnd;
									lastEnd = page.iEnd - page.iStart;
									itemCounter = 0;
									vTempPages.push_back(page);
								}
								itemCounter++;
							}
							page.iEnd = vCategories[iCurrentCategory].vItems.size();
							page.iStart = vCategories[iCurrentCategory].vItems.size() - leftOver;
							vTempPages.push_back(page);
							vCategories[iCurrentCategory].vPages = vTempPages;
							vCategories[iCurrentCategory].bHaveBeenPagesCalculated = true;
						}

						for (int j = vCategories[iCurrentCategory].vPages[iCurrentPage].iStart; j < vCategories[iCurrentCategory].vPages[iCurrentPage].iEnd; j++)
						{
							iActualItemID = j;
							std::string entry = vCategories[i].vItems[j].name.c_str();
							if (vCategories[i].vItems[j].bIsCharToggle || vCategories[i].vItems[j].bIsShortToggle || vCategories[i].vItems[j].bIsIntegerToggle)
							{
								entry.append(" = ");
								if (vCategories[i].vItems[j].bIsCharToggle)
									entry.append(GetStatusAsString(*vCategories[i].vItems[j].ptrCharValue));
								if (vCategories[i].vItems[j].bIsIntegerToggle)
									entry.append(GetStatusAsString(*vCategories[i].vItems[j].ptrIntValue));
							}

							if (vCategories[i].vItems[j].bIsAdjustable)
							{
								entry.append(" = ");
								if (m_bSelectedOption && j == iCurrentItem)
									entry.append("< ");
								entry.append(std::to_string(*vCategories[i].vItems[j].ptrIntValue));
								if (m_bSelectedOption && j == iCurrentItem)
									entry.append(" >");
							}
							if (vCategories[i].vItems[j].bIsAdjustableFloat)
							{
								entry.append(" = ");
								if (m_bSelectedOption && j == iCurrentItem)
									entry.append("< ");
								entry.append(std::to_string(*vCategories[i].vItems[j].ptrFloatValue));
								if (m_bSelectedOption && j == iCurrentItem)
									entry.append(" >");
							}
							CFrontend::SetDrawRGBA(0, 0, 0, 255);
							CFrontend::Print8(entry.c_str(), 0.138f, 0.102f + 0.04 * j, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
							if (j == iCurrentItem)
								CFrontend::SetDrawRGBA(51, 153, 255, 255);
							else
								CFrontend::SetDrawRGBA(255, 255, 255, 255);
							CFrontend::Print8(entry.c_str(), 0.136f, 0.10f + 0.04 * j, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);



							if (vCategories[iCurrentCategory].vPages.size() > 1)
							{
								sprintf(msgBuffer, "Page %d/%d", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
								CFrontend::SetDrawRGBA(0, 0, 0, 255);
								CFrontend::Print8(msgBuffer, 0.126f, 0.808f, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
								CFrontend::SetDrawRGBA(255, 255, 255, 255);
								CFrontend::Print8(msgBuffer, 0.124f, 0.810f, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
							}
						}
					}

				}
			}

		}

	}

}

void eMenu::Clear()
{
	vCategories.clear();
	vTempItems.clear();
	vTempPages.clear();
	vTempWeapons.clear();
	vTempEntities.clear();
	m_active = false;
	iCurrentItem = 0;
	iActualItemID = 0;
	iCurrentPage = 0;
	iCurrentCategory = 0;
	iBaseCategoryID = 0;
	iTotalItems = 0;
	m_bNavigatingCategory = false;
	m_bCategoryOpen = false;
	m_bPressedEnter = false;
	m_bIsHolding = false;
	m_bSelectedOption = false;

}



void eMenu::AddCategory(std::string name, bool isWeap)
{
	eMenuCategory newCat;
	newCat.strName = name;
	newCat.bIsWeapon = isWeap;
	newCat.bIsEntities = false;
	newCat.iID = iBaseCategoryID;
	newCat.bHasBeenWeaponsPopulated = false;
	newCat.bHasBeenEntitiesPopulated = false;
	newCat.bHaveBeenPagesCalculated = false;
	newCat.iPages = 0;
	if (vTempItems.size() > 0)
	{
		newCat.vItems = vTempItems;
		newCat.bHasItems = true;
	}

	vCategories.push_back(newCat);
	iBaseCategoryID++;
	vTempItems.clear();
}

void eMenu::AddEntitiesCategory(std::string name)
{
	eMenuCategory newCat;
	newCat.strName = name;
	newCat.bIsWeapon = false;
	newCat.bIsEntities = true;
	newCat.iID = iBaseCategoryID;
	newCat.bHasBeenWeaponsPopulated = false;
	newCat.bHasBeenEntitiesPopulated = false;
	newCat.bHaveBeenPagesCalculated = false;
	newCat.iPages = 0;
	if (vTempItems.size() > 0)
	{
		newCat.vItems = vTempItems;
		newCat.bHasItems = true;
	}

	vCategories.push_back(newCat);
	iBaseCategoryID++;
	vTempItems.clear();
}

void eMenu::AddItem(std::string name, bool isChar, bool isShort, bool isInt, bool isFunc, bool isWeapon, int weapID, char* ptrChar, short* ptrShort, int* ptrInt, std::function<void()> func,
	bool adjInt, int adjStep, int adjMin, int adjMax, bool adjFloat, float fAdjStep, float fAdjMin, float fAdjMax, bool isAnim, std::string strAnim, float* ptrFloat)
{
	eMenuItem item;
	item.ptrIntValue = ptrInt;
	item.ptrShortValue = ptrShort;
	item.ptrCharValue = ptrChar;
	item.bIsCharToggle = isChar;
	item.bIsShortToggle = isShort;
	item.bIsIntegerToggle = isInt;
	item.bIsFunction = isFunc;
	item.bIsWeapon = isWeapon;
	item.iWeaponID = weapID;
	item.name = name;
	item.fFunc = func;
	item.bIsAdjustable = adjInt;
	item.bIsAdjustableFloat = adjFloat;
	item.iStep = adjStep;
	item.iAdjustMin = adjMin;
	item.iAdjustMax = adjMax;
	item.fStep = fAdjStep;
	item.fAdjustMax = fAdjMax;
	item.fAdjustMin = fAdjMin;
	item.bIsEntity = isAnim;
	item.strEntity = strAnim;
	item.ptrFloatValue = ptrFloat;

	vTempItems.push_back(item);
}

void eMenu::AddWeaponEntry(int weaponID)
{
	std::string str = CCollectable::FastGetNameStringFromType(weaponID);// GetRecordName(weaponID);
	std::wstring wstr = CCollectable::GetNameKey16(weaponID);
	if (!wstr.empty())
		str = std::string(wstr.begin(), wstr.end());

	std::function<void()> dummy;
	AddItem(str, false, false, false, false, true, weaponID, nullptr, nullptr, nullptr, dummy, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");
}

void eMenu::AddEntityEntry(std::string str)
{
	std::function<void()> dummy;
	AddItem(str, false, false, false, false, false, false, nullptr, nullptr, nullptr, dummy, 0, 0, 0, 0, 0, 0, 0, 0, true, str);
}

void eMenu::AddToggleCharEntry(std::string name, char * ptr)
{
	std::function<void()> dummy;
	AddItem(name, true, false, false, false, false, false, ptr, nullptr, nullptr, dummy, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");
}

void eMenu::AddToggleIntEntry(std::string name, int * ptr)
{
	std::function<void()> dummy;
	AddItem(name, false, false, true, false, false, false, nullptr, nullptr, ptr, dummy, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");
}

void eMenu::AddFunctionEntry(std::string name, std::function<void()> func)
{
	AddItem(name, false, false, false, true, false, 0, nullptr, nullptr, nullptr, func, 0, 0, 0, 0, 0, 0, 0, 0, 0, "");
}

void eMenu::AddSliderIntEntry(std::string name, int * ptr, int min, int max, int step)
{
	std::function<void()> dummy;
	AddItem(name, false, false, false, false, false, false, nullptr, nullptr, ptr, dummy, true, step, min, max, 0, 0, 0, 0, 0, "");
}

void eMenu::AddSliderFloatEntry(std::string name, float* ptr, float min, float max, float step)
{
	std::function<void()> dummy;
	AddItem(name, false, false, false, false, false, false, nullptr, nullptr, nullptr, dummy, false, 0, 0, 0, true, step, min, max, 0, "", ptr);
}


std::string GetStatusAsString(int value)
{
	return value ? "true" : "false";
}

std::string GetAnimationName(int id)
{
	char tmp[128] = {};
	sprintf(tmp, "%s", (char*)(0x6851C0 + (id * 48)));
	return std::string(tmp, strlen(tmp));
}

void SavePosition()
{
	CEntity* plr = CScene::FindPlayer();
	CVector* pos = plr->GetLocation();
	TheMenu.savedPosition = *pos;
}

void LoadPosition()
{
	CEntity* plr = CScene::FindPlayer();
	plr->SetLocation(&TheMenu.savedPosition);
}

void SetDifficultyEasy()
{
	CFrontend::Set_Difficulty(0);
}

void SetDifficultyHard()
{
	CFrontend::Set_Difficulty(1);
}

void PutBagOnPlayerHead()
{
	CPed* ped = (CPed*)CScene::FindPlayer();
	ped->ChangePedHead("Bag_Head");
}

void PlayerDropAllWeapons()
{
	CPed* ped = (CPed*)CScene::FindPlayer();
	


	if (ped->m_pInventory->GetNumItems() > 1)
	{
		// move player
		CEntity* plr = CScene::FindPlayer();
		RwMatrix* matrix = plr->GetEntityMatrix();

		CVector forward(matrix->at.x, matrix->at.y, matrix->at.z);
		CVector pos = *plr->GetLocation();

		pos += forward * 1.25f;

		plr->SetLocation(&pos);
	}

	// ignore fists
	for (int i = 1; i < ped->m_pInventory->m_numSlots; i++)
	{
		CWeaponCollectable* weapon = (CWeaponCollectable*)ped->m_pInventory->m_inventory[i];
		if (weapon)
			weapon->Drop();
	}



}


void PrintEntities()
{
	int list = *(int*)0x69BBC4;
	CEntity* entity;
	do
	{
		if (list)
			entity = *(CEntity**)(list);
		else
			entity = 0;
		if (list)
			list = *(int*)(list + 8);

		if (entity)
		{
				TheConsole.m_messages.push_back(entity->m_pTypeData->m_szRecordName);
		}

	} while (entity);

}

void PrintExecuteHunter()
{
	CPlayer* plr = (CPlayer*)CScene::FindPlayer();
	CEntity* hunt = *(CEntity**)((int)plr + 0x8B4);
	if (hunt)
		printf("%x %s\n", hunt, hunt->m_pTypeData->m_szRecordName);
	else
		printf("no execute\n");
}

bool KeyHit(unsigned int keyCode)
{
	if (IsWindowFocused() && CFrontend::m_gameIsRunning)
		return (GetKeyState(keyCode) & 0x8000) != 0;
	else
		return false;
}

bool KeyHitOnce(unsigned int keyCode)
{
	if (IsWindowFocused() && CFrontend::m_gameIsRunning)
		return (GetAsyncKeyState(keyCode) & 1);
	else
		return false;
}

