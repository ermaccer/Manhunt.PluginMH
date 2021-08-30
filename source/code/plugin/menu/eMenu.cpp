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


#include "..\..\core\eSettingsManager.h"
#include "..\..\core\eMain.h"
#include "..\..\plugin\eCustomAnimManager.h"
#include "..\..\manhunt\core.h"
#include "..\..\..\IniReader.h"
#include "..\eMapLimits.h"
#include "..\MHcommon.h"


// custom

int bDisplayPlayerCoords = 0;
int bDisplayPlayerCoordsReal = 0;
int bControllerDebug = 0;
int bNewManagerDebug = 0;
int bDisableLockonTriangles = 0;
int bDisplaySavedPositionMarker = 0;
int bGodMode = 0;
int bPlayerInfiniteHealth = 0;
int bHideMoon = 0;
int bHideStars = 0;
int bFallDamage = 1;
int bLevelTimer = 0;
int bSilenceWeapons = 0;

char& bTimer = *(char*)0x7D5A08;
char& bActivateTimer = *(char*)0x7D5A0C;
char& bBodyCount = *(char*)0x7D5A18;

int bEnableKillCounter = 0;
int bInfiniteAmmo = 0;


static unsigned int iTimer = GetTickCount();
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

	AddToggleIntEntry("Infinite Health", &bPlayerInfiniteHealth);
	AddToggleIntEntry("God Mode", &bGodMode);
	AddToggleIntEntry("Fall Damage", &bFallDamage);
	AddFunctionEntry("Save Position", SavePosition);
	AddFunctionEntry("Load Position", LoadPosition);
	AddToggleIntEntry("Display Coordinates", &bDisplayPlayerCoords);
	AddToggleIntEntry("Use INST Coordinates For Display", &bDisplayPlayerCoordsReal);
	AddToggleIntEntry("Display Saved Position", &bDisplaySavedPositionMarker);
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
	AddCategory("Weapons", true);

	AddToggleCharEntry("Timer", &bTimer);
	AddToggleCharEntry("Body Count", &bBodyCount);
	AddToggleIntEntry("Enable Body Count", &bEnableKillCounter);
	AddToggleIntEntry("Hide Lock-on Triangles (use with free cam)", &bDisableLockonTriangles);
	AddCategory("HUD");


	AddToggleCharEntry("Cheats Active", (char*)&CCheatHandler::m_bCheatsActive);
	AddToggleIntEntry("Helium Hunters", &CCheatHandler::m_heliumHunters);
	AddToggleIntEntry("Runner", &CCheatHandler::m_runner);
	AddToggleIntEntry("Regenerate", &CCheatHandler::m_regenerate);
	AddToggleIntEntry("Invisiblity", &CCheatHandler::m_invisibility);
	AddToggleIntEntry("Super Punch", &CCheatHandler::m_superPunch);

	AddCategory("Cheats");

	if (eSettingsManager::bIncreaseMapLimits)
		AddToggleIntEntry("New Material Manager Debug", &bNewManagerDebug);
	AddToggleIntEntry("Hide Moon", &bHideMoon);
	AddToggleIntEntry("Hide Stars", &bHideStars);

	AddCategory("World");

	AddFunctionEntry("Free",	CWeather::SetWeatherFree);
	AddFunctionEntry("Clear",	CWeather::SetWeatherClear);
	AddFunctionEntry("Cloudy",	CWeather::SetWeatherCloudy);
	AddFunctionEntry("Thunder", CWeather::SetWeatherThunder);
	AddFunctionEntry("Rainy",	CWeather::SetWeatherRainy);
	AddFunctionEntry("Foggy",	CWeather::SetWeatherFoggy);
	AddFunctionEntry("Windy",	CWeather::SetWeatherWindy);
	AddCategory("Weather");

	AddToggleIntEntry("Log Gamepad",&bControllerDebug);
	AddToggleIntEntry("Silence Firearms", &bSilenceWeapons);
	AddToggleIntEntry("Infinite Ammo", &bInfiniteAmmo);
	AddFunctionEntry("Set Difficulty To Fetish", SetDifficultyEasy);
	AddFunctionEntry("Set Difficulty To Hardcore", SetDifficultyHard);
	AddCategory("Misc.");


}

void eMenu::ProcessMenu()
{

	if (bPlayerInfiniteHealth)
	{
		if (CScene::FindPlayer())
		{
			CScene::FindPlayer()->m_fHealth = 100.0f;
		}
	}

	if (CScene::FindPlayer())
		CScene::FindPlayer()->SetFlag(0x100, bGodMode);


	if (bEnableKillCounter)
		CFrontend::ms_cnt = *(int*)0x7B7D84 + *(int*)0x7B7DA0;


	if (!bFallDamage)
	{
		Patch<float>(0x4313F7 + 3,100.0f);
		Patch<float>(0x43152B + 3,100.0f);
	}
	else
	{
		Patch<float>(0x4313F7 + 3,-1.0f);
		Patch<float>(0x43152B + 3,-1.0f);
	}

	if (bSilenceWeapons)
		Patch<char>(0x4C9C92 + 1, 8);
	else
		Patch<char>(0x4C9C92 + 1, 7);


	if (bInfiniteAmmo)
		Patch<char>(0x4F9073 + 6, 0);
	else
		Patch<char>(0x4F9073 + 6, 1);

	if (bDisableLockonTriangles)
		Patch<float>(0x728138, 0.0f);
	else
		Patch<float>(0x728138, 0.5f);

	if (bHideMoon)
		Nop(0x5CB59D, 5);
	else
		InjectHook(0x5CB59D, CRenderer::DrawQuad2d, PATCH_CALL);

	if (bHideStars)
		Nop(0x5CB81D, 5);
	else
		InjectHook(0x5CB81D, CRenderer::DrawQuad2dSet, PATCH_CALL);


	
	if (bDisplayPlayerCoords)
	{
		CVector* pos = CScene::FindPlayer()->GetLocation();
		if (bDisplayPlayerCoordsReal)
			sprintf(buffer, "(INST) X: %.3f Y: %.3f Z: %.3f", pos->x, pos->z * -1.0f, pos->y);
		else
			sprintf(buffer, "X: %.3f Y: %.3f Z: %.3f", pos->x, pos->y, pos->z);
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(buffer, 0.552f, 0, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(buffer, 0.554f, 0, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}

	if (bControllerDebug)
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


	if (bDisplaySavedPositionMarker)
	{
		sprintf(buffer, "X: %.3f Y: %.3f Z: %.3f", savedPosition.x,savedPosition.y,savedPosition.z);
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(buffer, 0.552f, 0.1f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(buffer, 0.554f, 0.1f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}

	if (bNewManagerDebug)
	{
		sprintf(buffer, "Materials = %d/%d Missing Materials = %d", gNewCollisionMaterialManager.m_numWorldMaterials, AMOUNT_OF_MATERIALS, gNewCollisionMaterialManager.m_numMissingMaterials);
		CFrontend::SetDrawRGBA(255, 255,255, 255);
		CFrontend::Print8(buffer, 0.1f, 0, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}

	if (bLevelTimer)
	{
		CPlayer* plr = (CPlayer*)CScene::FindPlayer();
		if (plr)
		{
			plr->AccumulateTime();
			Call<0x5DB4C0, int>(*(int*)0x7108F0 + *(int*)(CScene::ms_pPlayer + 2112) - *(int*)(CScene::ms_pPlayer + 2108));

			int minutes = *(int*)0x7C9604 % 60;
			int seconds = *(int*)0x7C9608;
			char timer[256];
			sprintf(timer,"%02d:%02d", minutes, seconds);
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
			CFrontend::Print8(timer, 0.45f, 0.04f, 1.0f, 1.0f, 0, FONT_TYPE_DEFAULT);

		}

	}

	if (IsWindowFocused())
	ProcessToggle();

	if (bDisplayMenu)
	{
		DrawMenu();

		if (IsWindowFocused())
			ProcessControls();
	}


}

void eMenu::ProcessToggle()
{
	if (KeyHit(KeyEnableMenu))
	{
		if (GetTickCount() - iTimer <= 240) return;
		iTimer = GetTickCount();
		bDisplayMenu ^= 1;
		iCurrentCategory = 0;
		iCurrentItem = 0;
		bCategoryOpen = false;
		bNavigatingInCategory = false;
		vCategories[iCurrentCategory].vPages.clear();
		vCategories[iCurrentCategory].vWeapons.clear();
		vTempPages.clear();
		vTempWeapons.clear();
	}
}

void eMenu::ProcessControls()
{
	if (bPressedEnter)
		ProcessEnter();

	if (KeyHit(KeyMenuItemUP))
	{


		if (GetTickCount() - iTimer <= 100) return;
		iTimer = GetTickCount();
		if (bCategoryOpen && vCategories[iCurrentCategory].bHasItems)
		{

			iCurrentItem--;
			if (iCurrentItem < 0)
				iCurrentItem = iTotalItems - 1;
		}

		else
			iCurrentCategory--;
	}

	if (KeyHit(KeyMenuItemDOWN))
	{


		if (GetTickCount() - iTimer <= 100) return;
		iTimer = GetTickCount();
		if (bCategoryOpen && vCategories[iCurrentCategory].bHasItems)
		{
			iCurrentItem++;
			if (iCurrentItem + 1 > iTotalItems)
				iCurrentItem = 0;

		}
		else
			iCurrentCategory++;


	}

	if (KeyHit(KeyMenuItemLEFT))
	{
		if (GetTickCount() - iTimer <= 100) return;
		iTimer = GetTickCount();
		iCurrentItem = 0;
		iCurrentPage--;
	}
	if (KeyHit(KeyMenuItemRIGHT))
	{
		if (GetTickCount() - iTimer <= 140) return;
		iTimer = GetTickCount();
		iCurrentItem = 0;
		iCurrentPage++;
	}

	if (!bCategoryOpen && !bNavigatingInCategory)
	{
		if (vCategories[iCurrentCategory].bHasItems && vCategories[iCurrentCategory].vItems.size() > 0)
		{
			if (KeyHit(KeyMenuExecute))
			{
				if (GetTickCount() - iTimer <= 140) return;
				iTimer = GetTickCount();
				if (vCategories[iCurrentCategory].bIsWeapon)
				{
					vCategories[iCurrentCategory].vWeapons.clear();
					vCategories[iCurrentCategory].bHasBeenWeaponsPopulated = false;

				}
				vTempPages.clear();
				vCategories[iCurrentCategory].vPages.clear();
				vCategories[iCurrentCategory].bHaveBeenPagesCalculated = false;
				bCategoryOpen = true;
				bPressedEnter = true;
				bNavigatingInCategory = true;
			}
		}

	}

	if (bCategoryOpen)
	{
		if (KeyHit(KeyMenuGoBack))
		{
			if (vCategories[iCurrentCategory].bIsWeapon)
			{
				vCategories[iCurrentCategory].vWeapons.clear();
				vTempWeapons.clear();
				vCategories[iCurrentCategory].bHasBeenWeaponsPopulated = false;

			}

			if (GetTickCount() - iTimer <= 140) return;
			iTimer = GetTickCount();
			bCategoryOpen = false;
			bNavigatingInCategory = false;
			vTempPages.clear();
			vCategories[iCurrentCategory].vPages.clear();
			vCategories[iCurrentCategory].bHaveBeenPagesCalculated = false;
			iCurrentItem = 0;
		}
	}

	if (bNavigatingInCategory && bCategoryOpen && !bPressedEnter)
	{
		if (KeyHit(KeyMenuExecute))
		{
			if (vCategories[iCurrentCategory].bIsWeapon && vCategories[iCurrentCategory].bHasBeenWeaponsPopulated)
			{
				int weapon = iCurrentItem + vCategories[iCurrentCategory].vPages[iCurrentPage].iStart;
				if (vCategories[iCurrentCategory].vWeapons[weapon].bIsWeapon)
					GiveWeaponToPlayer(vCategories[iCurrentCategory].vWeapons[weapon].iWeaponID);

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
					if (GetTickCount() - iTimer <= 140) return;
					iTimer = GetTickCount();
					*vCategories[iCurrentCategory].vItems[item].ptrCharValue ^= 1;
				}
				if (vCategories[iCurrentCategory].vItems[item].bIsIntegerToggle)
				{
					if (GetTickCount() - iTimer <= 140) return;
					iTimer = GetTickCount();
					*vCategories[iCurrentCategory].vItems[item].ptrIntValue ^= 1;
				}
			}
		}
	}



	if (iCurrentPage + 1 > vCategories[iCurrentCategory].vPages.size()) iCurrentPage = 0;
	if (iCurrentPage < 0) iCurrentPage = vCategories[iCurrentCategory].vPages.size() - 1;
	if (iCurrentCategory + 1 > vCategories.size()) iCurrentCategory = 0;
	if (iCurrentCategory < 0) iCurrentCategory = vCategories.size() - 1;

}

void eMenu::DrawMenu()
{
	if (bDisplayMenu)
	{
		// control execution

		for (int i = 0; i < vCategories.size(); i++)
		{

			//	sprintf(msgBuffer, "ermaccer / dixmor-hospital.com", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
			//	CFrontend::SetDrawRGBA(0, 0, 0, 255);
			//	CFrontend::Print8(msgBuffer, 0.048f, 0.012f, 0.5f, 0.5f, 0.0, FONT_TYPE_DEFAULT);
			//	CFrontend::SetDrawRGBA(255, 255, 255, 255);
			//	CFrontend::Print8(msgBuffer, 0.050f, 0.010f, 0.5f, 0.5f, 0.0, FONT_TYPE_DEFAULT);


			CFrontend::SetDrawRGBA(0, 0, 0, 255);
			CFrontend::Print8(vCategories[i].strName.c_str(), 0.048f, 0.102f + 0.04 * i, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
			if (i == iCurrentCategory)
				CFrontend::SetDrawRGBA(51, 153, 255, 255);
			else
				CFrontend::SetDrawRGBA(255, 255, 255, 255);
			CFrontend::Print8(vCategories[i].strName.c_str(), 0.050f, 0.10f + 0.04 * i, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);

			// draw sub items
			if (vCategories[i].bHasItems && bCategoryOpen)
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
							CFrontend::Print8(entry.c_str(), 0.122f, 0.102f + 0.04 * (j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)), 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
							if ((j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)) == iCurrentItem)
								CFrontend::SetDrawRGBA(51, 153, 255, 255);
							else
								CFrontend::SetDrawRGBA(255, 255, 255, 255);
							CFrontend::Print8(entry.c_str(), 0.124f, 0.10f + 0.04 * (j - (vCategories[iCurrentCategory].vPages[iCurrentPage].iStart)), 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
						}
						if (vCategories[iCurrentCategory].vPages.size() > 1)
						{
							sprintf(msgBuffer, "Page %d/%d", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
							CFrontend::SetDrawRGBA(0, 0, 0, 255);
							CFrontend::Print8(msgBuffer, 0.122f, 0.808f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
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





							CFrontend::SetDrawRGBA(0, 0, 0, 255);
							CFrontend::Print8(entry.c_str(), 0.122f, 0.102f + 0.04 * j, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
							if (j == iCurrentItem)
								CFrontend::SetDrawRGBA(51, 153, 255, 255);
							else
								CFrontend::SetDrawRGBA(255, 255, 255, 255);
							CFrontend::Print8(entry.c_str(), 0.124f, 0.10f + 0.04 * j, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);



							if (vCategories[iCurrentCategory].vPages.size() > 1)
							{
								sprintf(msgBuffer, "Page %d/%d", iCurrentPage + 1, vCategories[iCurrentCategory].vPages.size());
								CFrontend::SetDrawRGBA(0, 0, 0, 255);
								CFrontend::Print8(msgBuffer, 0.122f, 0.808f, 0.6f, 0.6f, 0.0, FONT_TYPE_DEFAULT);
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
void eMenu::ProcessEnter()
{
	if (GetTickCount() - iTimer <= 155)  return;
	iTimer = GetTickCount();
	bPressedEnter = false;
}

void eMenu::Clear()
{
	vCategories.clear();
	vTempItems.clear();
	vTempPages.clear();
	vTempWeapons.clear();
	vTempAnims.clear();
	bDisplayMenu = false;
	iCurrentItem = 0;
	iActualItemID = 0;
	iCurrentPage = 0;
	iCurrentCategory = 0;
	iBaseCategoryID = 0;
	iTotalItems = 0;
	bNavigatingInCategory = false;
	bCategoryOpen = false;
	bPressedEnter = false;
	bIsHoldingMenu = false;

}



void eMenu::AddCategory(std::string name, bool isWeap)
{
	eMenuCategory newCat;
	newCat.strName = name;
	newCat.bIsWeapon = isWeap;
	newCat.iID = iBaseCategoryID;
	newCat.bHasBeenWeaponsPopulated = false;
	newCat.bHasBeenAnimsPopulated = false;
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

void eMenu::AddAnimsCategory(std::string name)
{
	eMenuCategory newCat;
	newCat.strName = name;
	newCat.bIsWeapon = false;
	newCat.bIsAnims = true;
	newCat.iID = iBaseCategoryID;
	newCat.bHasBeenWeaponsPopulated = false;
	newCat.bHasBeenAnimsPopulated = false;
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
	bool adjInt, int adjStep, int adjMin, int adjMax, bool adjFloat, float fAdjStep, float fAdjMin, float fAdjMax, bool isAnim, std::string strAnim)
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
	item.bIsAnim = isAnim;
	item.strAnim = strAnim;

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

void eMenu::AddAnimEntry(std::string str)
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



std::string GetStatusAsString(int value)
{
	if (value) return "true";
	else return "false";
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

bool KeyHit(unsigned int keyCode)
{
	if (IsWindowFocused() && CFrontend::m_gameIsRunning)
		return (GetKeyState(keyCode) & 0x8000) != 0;
	else
		return false;
}

