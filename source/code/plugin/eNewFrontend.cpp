﻿#include "eNewFrontend.h"
#include "..\core\eMain.h"
#include "..\manhunt\Frontend.h"
#include "..\manhunt\Text.h"
#include "..\manhunt\Input.h"
#include "..\manhunt\core.h"
#include "..\manhunt\Filenames.h"
#include "..\manhunt\Renderer.h"
#include "..\manhunt\Scene.h"
#include "..\manhunt\App.h"
#include "..\manhunt\Cheats.h"
#include "..\manhunt\Time.h"
#include "..\plugin\modloader\eModLoader.h"
#include "eStatsManager.h"
#include "..\..\resource.h"
#include "..\manhunt\Clump.h"
#include "..\manhunt\ClumpDict.h"
#include "..\manhunt\Entity.h";
#include "..\RenderWare.h"
#include "eSkinLoader.h"
#include "..\core\eSettingsManager.h"
#include "eGUI.h"
#include <iostream>

int eNewFrontend::m_pStatsMenu[2] = { (int)eNewFrontend::ProcessStatsMenu, (int)eNewFrontend::StatsMenu };
int eNewFrontend::ms_lastCustomMenu;
float eNewFrontend::m_fBoxPositionX;
float eNewFrontend::m_fBoxPositionY;
float eNewFrontend::m_fSkinsBoxPositionX;
float eNewFrontend::m_fSkinsBoxPositionY;
char eNewFrontend::statsBuffer[256];
wchar_t eNewFrontend::m_szStatsBuffer[128];
int eNewFrontend::m_allStatsPages;
int eNewFrontend::m_leftoverStatsPage;
int eNewFrontend::m_nCurrentStatsPage;
int eNewFrontend::m_nCurrentModsPage;
int eNewFrontend::m_nCurrentSkinPos;
int eNewFrontend::m_nSkinAdjustID;
wchar_t* eNewFrontend::m_szCheatText = (wchar_t*)0x7D6360;
RpWorld * eNewFrontend::ms_pMenuWorld;
RpLight * eNewFrontend::ms_pMenuLight;
bool eNewFrontend::m_bNewLevels;
	
void eNewFrontend::InitHooks()
{

	InjectHook(0x600C20, eNewFrontend::MainMenu, PATCH_JUMP);
	InjectHook(0x600B34, eNewFrontend::ProcessMainMenu, PATCH_JUMP);
	InjectHook(0x5D70F9, eNewFrontend::HookSelectMenuBackground, PATCH_JUMP);
	InjectHook(0x5D75D7, eNewFrontend::HookExecuteMenuProcess, PATCH_JUMP);

	// lcd display
	Nop(0x5D7504, 5);
	// lines?
	InjectHook(0x5D77B1, eNewFrontend::HookDrawRasterLineFX, PATCH_CALL);
	InjectHook(0x4D7A91, eNewFrontend::HookCreateMenuLight, PATCH_CALL);

}

void eNewFrontend::Init()
{
	m_fBoxPositionX = 0.155f;
	m_fBoxPositionY = 0.277f;
	m_fSkinsBoxPositionX = 0.50f;
	m_fSkinsBoxPositionY = 0.277f;
	m_nCurrentStatsPage = 0;
	m_nCurrentModsPage = 0;
	m_allStatsPages = 3;

	eSkinLoader::ReadFile();



	m_nCurrentSkinPos = eSkinLoader::ms_iCurrentSkinPos;
	m_nSkinAdjustID = eSkinLoader::ms_iCurrentSkinAdjust;
}


void eNewFrontend::MainMenu()
{
	CFrontend::ms_fMenuPositionX = 0.15f;
	float y_pos = CFrontend::ms_fMenuPositionY;
	float y_temp = 0.0f;
	float y_adjust = 0.30000001f;


	if (!m_bNewLevels)
		CFrontend::DrawMenuCameraCounter(CText::GetFromKey16("MAINM"));
	else
		CFrontend::DrawMenuCameraCounter(CText::GetFromKey16("SELSCE"));

	float m_fHudStretch = *(float*)0x7D3458;
	float m_fLogoScale = *(float*)0x7D63FC;

	float logoX = m_fHudStretch * m_fLogoScale;
	int logoTexture = CFrontend::GetTextureFromTXD(*(int*)0x7C8704, "logo");


	CRenderer::DrawQuad2d(*(float*)0x7D6408 + 0.45f, *(float*)0x7D6404, logoX, *(float*)0x7D6400, 180, 180, 180, 255, logoTexture);

	if (!m_bNewLevels)
	{
		y_temp = y_pos + y_adjust - CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("PLAY"), CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_PLAY);

		y_temp = y_pos + y_adjust;
		CFrontend::AddOption(CText::GetFromKey16("SELSCE"), CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_SELSCE);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("LOADG"), CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_LOADG);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("SETT"), CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_SETT);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("BONFEA"), CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_BONFEA);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"STATS", CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_STATS);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"MODIFICATIONS", CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_MODIFICATIONS);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"SKINS", CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_SKINS);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("QUITPRG"), CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_QUITPRG);
	}
	else
	{
		y_temp = y_pos + y_adjust - CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"ORIGINAL", CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_PLAY);

		y_temp = y_pos + y_adjust;
		CFrontend::AddOption(L"CUSTOM", CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_SELSCE);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"BACK", CFrontend::ms_fMenuPositionX, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_LOADG);
	}

}

bool __declspec(naked) eNewFrontend::ProcessMainMenu()
{
	static int lastLevel = 0;
	static int jmpPoint = 0x6025B6;

	static int maxButton = MB_QUITPRG;
	static int totalButton = MB_TOTAL_MENUS;


	if (m_bNewLevels)
	{
		maxButton = MB_LOADG;
		totalButton = MB_LOADG + 1;
	}
	else
	{
		maxButton = MB_QUITPRG;
		totalButton = MB_TOTAL_MENUS;
	}


	
	if (CInputManager::FrontendPressedUp())
	{
		if (--CFrontend::ms_menuButton < 0)
			CFrontend::ms_menuButton = maxButton;
	}

	if (CInputManager::FrontendPressedDown())
	{
		if (++CFrontend::ms_menuButton >= totalButton)
			CFrontend::ms_menuButton = 0;
	}

	if (CInputManager::FrontedMouseHovered())
		CFrontend::ms_menuButton = CFrontend::GetHoveredItem();

	if (CInputManager::FrontendPressedEscape())
	{
		if (m_bNewLevels)
			m_bNewLevels = false;
		else
			CFrontend::SetCurrentMenu(MENU_QUIT);
	}




	if (CInputManager::FrontendButtonEnter())
	{
		if (!m_bNewLevels)
		{
			switch (CFrontend::ms_menuButton)
			{
			case MB_PLAY:
				lastLevel = CFrontend::GetLastPlayedLevel();
				if (lastLevel == -1)
				{
					Call<0x5D6A60>(); // resets something
					CFrontend::m_bNewGame = 0;
					*(int*)0x7C86F4 = 0;
					CFrontend::SetCurrentMenu(MENU_GAMMA_SETTINGS);
				}
				else
					CFrontend::ForceAndPlayLevel(lastLevel, 1);
				break;
			case MB_SELSCE:
				//m_bNewLevels = true;
				*(int*)0x7C89E4 = 7;
				CFrontend::SetCurrentMenu(MENU_LEVEL_SELECT);
				break;
			case MB_LOADG:
				CFrontend::SetCurrentMenu(MENU_START_LOAD_GAME);
				break;
			case MB_SETT:
				CFrontend::SetCurrentMenu(MENU_SETTINGS);
				break;
			case MB_BONFEA:
				CFrontend::SetCurrentMenu(MENU_BONUS_FEATURES);
				break;
			case MB_STATS:
				CFrontend::SetCurrentMenu(MENU_STATS);
				break;
			case MB_MODIFICATIONS:
				CFrontend::SetCurrentMenu(MENU_MODS);
				break;
			case MB_SKINS:
				CFrontend::SetCurrentMenu(MENU_SKINS);
				break;
			case MB_QUITPRG:
				CFrontend::SetCurrentMenu(MENU_QUIT);
				break;
			}
		}
		else
		{
			switch (CFrontend::ms_menuButton)
			{
			case MB_PLAY:
				*(int*)0x7C89E4 = 7;
				CFrontend::SetCurrentMenu(MENU_LEVEL_SELECT);
				break;
			case MB_SELSCE:
				CFrontend::SetCurrentMenu(MENU_LEVEL_SELECT_DUO);
				break;
			case MB_LOADG:
				m_bNewLevels = false;
				break;
			}
		}			
	}

	if (CCheatHandler::m_lastCheat)
	{
		switch (CCheatHandler::m_lastCheat)
		{
		case CHEAT_RUNNER:
			m_szCheatText = CText::GetFromKey16("C_RUN");
			break;
		case CHEAT_SILENCE:
			m_szCheatText = CText::GetFromKey16("C_SILEN");
			break;
		case CHEAT_REGENERATION:
			m_szCheatText = CText::GetFromKey16("C_REGEN");
			break;
		case CHEAT_EXPLODE:
			m_szCheatText = CText::GetFromKey16("C_HELI");
			break;
		case CHEAT_EQUIPPED:
			m_szCheatText = CText::GetFromKey16("C_FULEQ");
			break;
		case CHEAT_SUPERPUNCH:
			m_szCheatText = CText::GetFromKey16("C_SUPUN");
			break;
		case CHEAT_RABBIT:
			m_szCheatText = CText::GetFromKey16("C_RABBI");
			break;
		case CHEAT_MONKEY:
			m_szCheatText = CText::GetFromKey16("C_MONKE");
			break;
		case CHEAT_INVIS:
			m_szCheatText = CText::GetFromKey16("C_INVIS");
			break;
		case CHEAT_PIGGSY:
			m_szCheatText = CText::GetFromKey16("C_PIGGS");
			break;
		case CHEAT_GODMODE:
			m_szCheatText = CText::GetFromKey16("C_GOD");
			break;
		}
	}

	if (CCheatHandler::m_bCheatsActive)
		CFrontend::PrintInfo(m_szCheatText, (wchar_t*)0x7D6360, (wchar_t*)0x7D6360, (wchar_t*)0x7D6360);

	_asm jmp jmpPoint

}

void eNewFrontend::SettingsMenu()
{
	float x_pos = *(float*)0x7C8718;
	float y_pos = *(float*)0x7C871C;
	float y_temp = 0.0f;
	float y_adjust = 0.30000001f;


	CFrontend::DrawMenuCameraCounter(CText::GetFromKey16("MAINM"));

}

bool eNewFrontend::IsCustomMenu(int menu)
{
	if (menu > MENU_QUIT && menu < MENU_MODS)
		return true;
	else
		return false;
}

void eNewFrontend::DrawEVisionMark()
{
	if (!eSettingsManager::bHideVersionInfo)
	{
		CFrontend::SetDrawRGBA(255, 255, 255, 48);
		char tmp[128] = {};
		sprintf(tmp, "PluginMH %d.%d.%d by ermaccer", VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION);
		CFrontend::Print8(tmp, 0.0, 0.0, 0.28f, 0.28f, 0.0f, FONT_TYPE_DEFAULT);
	}
}

void eNewFrontend::StatsMenu()
{
	wsprintfW(m_szStatsBuffer, L"STATS %d/%d", m_nCurrentStatsPage + 1, m_allStatsPages);
	CFrontend::DrawMenuCameraCounter(m_szStatsBuffer);
	CRenderer::DrawQuad2d(m_fBoxPositionX, m_fBoxPositionY, 0.69f, 0.55f, 180, 180, 180, 128, 0);
	for (int i = 0; i < STATS_PER_PAGE; i++)
	{
		if (m_nCurrentStatsPage > 0)
			DrawStatText(i + (STATS_PER_PAGE * m_nCurrentStatsPage));
		else
			DrawStatText(i);
	}


	CFrontend::PrintInfo(L"Press ESC to quit, ~up~ or ~down~ to navigate", (wchar_t*)0x7D6360, (wchar_t*)0x7D6360, (wchar_t*)0x7D6360);
}

void eNewFrontend::ProcessStatsMenu()
{
	if (CInputManager::FrontendPressedEscape())
		CFrontend::SetCurrentMenu(MENU_19);

	if (CInputManager::FrontendPressedUp())
		m_nCurrentStatsPage--;

	if (CInputManager::FrontendPressedDown())
		m_nCurrentStatsPage++;

	if (m_nCurrentStatsPage < 0)
		m_nCurrentStatsPage = 0;

	if (m_nCurrentStatsPage > m_allStatsPages - 1)
		m_nCurrentStatsPage = m_allStatsPages - 1;

}

void eNewFrontend::ModsMenu()
{
	int mods = eModLoader::modFolders.size();
	char tmp[128];

	CFrontend::SetDrawRGBA(255,255,255, 255);

	sprintf(tmp, "LOADED MODIFICATIONS: %d", mods);
	CFrontend::Print8(tmp, m_fBoxPositionX, m_fBoxPositionY - 0.10f, 1.0, 1.0, 0.0, FONT_FRONTEND);
	CFrontend::DrawMenuCameraCounter(L"MODIFICATIONS");

	for (int i = 0; i < mods; i++)
	{
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(eModLoader::modFolders[i].c_str(), m_fBoxPositionX + 0.02 + 0.004, m_fBoxPositionY + 0.05 * i + 0.004, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(eModLoader::modFolders[i].c_str(), m_fBoxPositionX + 0.02, m_fBoxPositionY + 0.05 * i, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}
}

void eNewFrontend::ProcessModsMenu()
{
	if (CInputManager::FrontendPressedEscape())
		CFrontend::SetCurrentMenu(MENU_19);

}

void eNewFrontend::NewLevelSelect()
{
	if (eGUI::Button("play level 24", 0.5f, 0.5f))
		CFrontend::ForceAndPlayLevel(24, 1);
	if (eGUI::Button("play level 25", 0.5f, 0.6f))
		CFrontend::ForceAndPlayLevel(25, 1);
	if (eGUI::Button("play weasel", 0.5f, 0.7f))
		CFrontend::ForceAndPlayLevel(weasel, 1);
}

void eNewFrontend::ProcessNewLevelSelect()
{
	if (CInputManager::FrontendPressedEscape())
		CFrontend::SetCurrentMenu(MENU_19);

}

void eNewFrontend::NewSettingMenu()
{
	float y_pos = CFrontend::ms_fMenuPositionY;
	float y_temp = 0.0f;
	float y_adjust = 0.30000001f;



	CFrontend::DrawMenuCameraCounter(CText::GetFromKey16("MAINM"));


	y_temp = y_pos + y_adjust - CFrontend::ms_fMenuPositionY;
	CFrontend::AddOption(CText::GetFromKey16("SETT"), CFrontend::ms_fMenuPositionX, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == LS_ORIGINAL);
	y_temp = y_pos + y_adjust;
	CFrontend::AddOption(L"PLUGINMH SETTINGS", CFrontend::ms_fMenuPositionX, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == LS_NEW);
	y_temp += CFrontend::ms_fMenuPositionY;
	CFrontend::AddOption(L"BACK", CFrontend::ms_fMenuPositionX, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == LS_BACK);
}

void eNewFrontend::ProcessNewSettingMenu()
{
	if (CInputManager::FrontendPressedUp())
	{
		if (CFrontend::ms_menuButton-- < 0)
			CFrontend::ms_menuButton = LS_BACK;
	}

	if (CInputManager::FrontendPressedDown())
	{
		if (CFrontend::ms_menuButton++ >= LS_BACK)
			CFrontend::ms_menuButton = LS_ORIGINAL;
	}

	if (CInputManager::FrontedMouseHovered())
		CFrontend::ms_menuButton = CFrontend::GetHoveredItem();

	if (CInputManager::FrontendPressedEscape())
		CFrontend::SetCurrentMenu(MENU_19);



	if (CInputManager::FrontendButtonEnter())
	{
		switch (CFrontend::ms_menuButton)
		{
		case LS_ORIGINAL:
			//*(int*)0x7C89E4 = 7;
			CFrontend::ms_menuButton = -1;
			*(int*)0x7C8FAC = -1;
			CFrontend::SetCurrentMenu(MENU_SETTINGS);
			break;
		case LS_NEW:
			//*(int*)0x7C89E4 = 7;
			CFrontend::SetCurrentMenu(MENU_MODS);
			break;
		case LS_BACK:
			CFrontend::SetCurrentMenu(MENU_19);
			break;
		}
	}
}

void eNewFrontend::Skins()
{

	CFrontend::DrawMenuCameraCounter(L"SKINS");


	if (eSkinLoader::ms_pPlayerClump && eSkinLoader::ms_bSkinLoaded)
	{
		static float rotation = 0.0f;
		static unsigned int LastFlash = 0;

		const RwV3d pos = { 1.15f, -1.25f, 4.05f };
		const RwV3d axis2 = { 0.0f, 1.0f, 0.0f };
		RwRGBAReal AmbientColor = { 0.80, 0.80, 0.80, 1.0f };
		if (GetTickCount() - LastFlash > 7) {
			rotation += 1.0f;
			if (rotation > 360.0f)
				rotation -= 360.0f;
			LastFlash = GetTickCount();
		}

		RwFrame *frame = RpClumpGetFrame(eSkinLoader::ms_pPlayerClump);
		RwFrameTransform(frame, RwFrameGetMatrix(RwCameraGetFrame(CFrontend::GetFrontendCamera())), rwCOMBINEREPLACE);
		RwFrameTranslate(frame, &pos, rwCOMBINEPRECONCAT);
		RwFrameRotate(frame, &axis2, rotation, rwCOMBINEPRECONCAT);
		RwFrameUpdateObjects(frame);

		CRenderer::SetIngameInfoRenderStates(1);

		RpWorld *oldWorld = (RpWorld *)RWSRCGLOBAL(curWorld);

		RWSRCGLOBAL(curWorld) = ms_pMenuWorld;
		RpLightSetColor(ms_pMenuLight, &AmbientColor);
		RpClumpRender(eSkinLoader::ms_pPlayerClump);
		RWSRCGLOBAL(curWorld) = oldWorld;

		CRenderer::SetIngameInfoRenderStates(0);
	}

	CRenderer::DrawQuad2d(m_fSkinsBoxPositionX, m_fSkinsBoxPositionY, 0.40f, 0.6f, 180, 180, 180, 90, 0);

	const char* skinsHelp = "Press ~up~ or ~down~ to change skin. ESC to save & quit.";
	CFrontend::SetDrawRGBA(0, 0, 0, 255);
	CFrontend::Print8(skinsHelp, 0.05f + 0.004f, 0.90f + 0.004, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	CFrontend::SetDrawRGBA(255, 255, 255, 255);
	CFrontend::Print8(skinsHelp, 0.05f, 0.90f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);

	char skinNo[128] = {};
	sprintf(skinNo, "Skins: %d", eSkinLoader::vSkins.size());
	CFrontend::SetDrawRGBA(0, 0, 0, 255);
	CFrontend::Print8(skinNo, m_fSkinsBoxPositionX + 0.30f + 0.004f, m_fSkinsBoxPositionY + 0.60f + 0.004, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	CFrontend::SetDrawRGBA(255, 255, 255, 255);
	CFrontend::Print8(skinNo, m_fSkinsBoxPositionX + 0.30f, m_fSkinsBoxPositionY + 0.60f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);


	int skins = eSkinLoader::vSkins.size();

	float arrowX = m_fSkinsBoxPositionX + 0.37f;
	float downY = m_fSkinsBoxPositionY + 0.52f;
	float upY = m_fSkinsBoxPositionY;
	float arrow_x = 0.05f;
	float arrow_y = 0.055f;
	bool isDown = false;
	bool isUp = false;

	FEMouse mouse = CInputManager::GetFrontendMouse();

	if (mouse.X >= arrowX && mouse.X < arrowX + arrow_x && mouse.Y >= downY && mouse.Y < downY + arrow_y)
		isDown = true;

	if (mouse.X >= arrowX && mouse.X < arrowX + arrow_x && mouse.Y >= upY && mouse.Y < upY + arrow_y)
		isUp = true;



	static unsigned int lastMScroll = 0;
	if (GetTickCount() - lastMScroll > 25)
	{
		if (CPad::NewMouseControllerState.wheelUp)
		{
			isUp = true;
			if (m_nCurrentSkinPos == 0)
			{
				if (eSkinLoader::vSkins.size() >= 11)
					m_nSkinAdjustID--;
				if (m_nSkinAdjustID < 0)
					m_nSkinAdjustID = 0;
			}

			m_nCurrentSkinPos--;
			if (m_nCurrentSkinPos < 0)
				m_nCurrentSkinPos = 0;

			eSkinLoader::ReloadPlayerDff(m_nCurrentSkinPos + m_nSkinAdjustID);
		}
		if (CPad::NewMouseControllerState.wheelDown)
		{
			isDown = true;
			if (m_nCurrentSkinPos == 10)
			{
				if (eSkinLoader::vSkins.size() > 10)
					m_nSkinAdjustID++;
				if (m_nSkinAdjustID > eSkinLoader::vSkins.size() - 11)
					m_nSkinAdjustID = eSkinLoader::vSkins.size() - 11;
			}
			m_nCurrentSkinPos++;

			if (eSkinLoader::vSkins.size() >= 11)
			{
				if (m_nCurrentSkinPos > 10)
					m_nCurrentSkinPos = 10;
			}
			else
				if (m_nCurrentSkinPos > eSkinLoader::vSkins.size() - 1)
					m_nCurrentSkinPos = eSkinLoader::vSkins.size() - 1;

			eSkinLoader::ReloadPlayerDff(m_nCurrentSkinPos + m_nSkinAdjustID);
		}
		lastMScroll = GetTickCount();
	}

	if (eSkinLoader::vSkins.size() >= 11)
	{
		skins = 11;
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8("~down~", arrowX + 0.004f, downY + 0.004, 1.25f, 1.25f, 0.0, FONT_TYPE_DEFAULT);
		if (isDown)
			CFrontend::SetDrawRGBA(180, 180, 255, 255);
		else
			CFrontend::SetDrawRGBA(120, 120, 170, 255);
		CFrontend::Print8("~down~", arrowX, downY, 1.25f, 1.25f, 0.0, FONT_TYPE_DEFAULT);

		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8("~up~", m_fSkinsBoxPositionX + 0.37 + 0.004f, upY + 0.004, 1.25f, 1.25f, 0.0, FONT_TYPE_DEFAULT);
		if (isUp)
			CFrontend::SetDrawRGBA(180, 180, 255, 255);
		else
			CFrontend::SetDrawRGBA(120, 120, 170, 255);
		CFrontend::Print8("~up~", m_fSkinsBoxPositionX + 0.37, upY, 1.25f, 1.25f, 0.0, FONT_TYPE_DEFAULT);

	}




	if (CPad::NewMouseControllerState.lmb)
	{
		static unsigned int lastScroll = 0;
		if (GetTickCount() - lastScroll > 100)
		{
			if (isUp)
			{
				if (eSkinLoader::vSkins.size() > 10)
					m_nSkinAdjustID--;
				if (m_nSkinAdjustID < 0)
					m_nSkinAdjustID = 0;
				eSkinLoader::ReloadPlayerDff(m_nCurrentSkinPos + m_nSkinAdjustID);
			}
			if (isDown)
			{
				if (eSkinLoader::vSkins.size() > 10)
					m_nSkinAdjustID++;
				if (m_nSkinAdjustID > eSkinLoader::vSkins.size() - 11)
					m_nSkinAdjustID = eSkinLoader::vSkins.size() - 11;
				eSkinLoader::ReloadPlayerDff(m_nCurrentSkinPos + m_nSkinAdjustID);
			}
			lastScroll = GetTickCount();
		}


	}


	for (int i = 0; i < skins; i++)
	{
		AddSkinButton(i + m_nSkinAdjustID, i);
	}


}

void eNewFrontend::ProcessSkins()
{
	eSkinLoader::LoadPlayerDff();

	if (CInputManager::FrontendPressedEscape())
	{
		eSkinLoader::SaveFile(m_nCurrentSkinPos,m_nSkinAdjustID);
		CFrontend::SetCurrentMenu(MENU_19);
	}


	if (CInputManager::FrontendPressedUp())
	{
		if (m_nCurrentSkinPos == 0)
		{
			if (eSkinLoader::vSkins.size() > 10)
				m_nSkinAdjustID--;
			if (m_nSkinAdjustID < 0)
				m_nSkinAdjustID = 0;
		}

		m_nCurrentSkinPos--;
		if (m_nCurrentSkinPos < 0)
			m_nCurrentSkinPos = 0;

		eSkinLoader::ReloadPlayerDff(m_nCurrentSkinPos + m_nSkinAdjustID);
	}


	if (CInputManager::FrontendPressedDown())
	{
		if (m_nCurrentSkinPos == 10)
		{
			if (eSkinLoader::vSkins.size() >= 11)
				m_nSkinAdjustID++;
			if (m_nSkinAdjustID > eSkinLoader::vSkins.size() - 11)
				m_nSkinAdjustID = eSkinLoader::vSkins.size() - 11;
		}
		m_nCurrentSkinPos++;

		if (eSkinLoader::vSkins.size() >= 11)
		{
			if (m_nCurrentSkinPos > 10)
				m_nCurrentSkinPos = 10;
		}
		else
			if (m_nCurrentSkinPos > eSkinLoader::vSkins.size() - 1)
				m_nCurrentSkinPos = eSkinLoader::vSkins.size() - 1;



		eSkinLoader::ReloadPlayerDff(m_nCurrentSkinPos + m_nSkinAdjustID);
	}



}

void eNewFrontend::AddSkinButton(int id, int pos)
{
	int len = eSkinLoader::vSkins[id].sName.length();

	float x = m_fSkinsBoxPositionX + 0.01f;
	float y = m_fSkinsBoxPositionY + 0.03f + 0.05f* pos;
	float x_size = len * 0.0097f;
	float y_size = 0.045f;

	
	FEMouse mouse = CInputManager::GetFrontendMouse();

	bool isInside = false;

	if (mouse.X >= x && mouse.X < x + x_size && mouse.Y >= y && mouse.Y < y + y_size)
		isInside = true;


	if (isInside)
	{
		if (CPad::NewMouseControllerState.lmb)
		{
			m_nCurrentSkinPos = pos;
			eSkinLoader::ReloadPlayerDff(id);
		}
	}

	CFrontend::SetDrawRGBA(0, 0, 0, 255);
	CFrontend::Print8(eSkinLoader::vSkins[id].sName.c_str(), x + 0.002f, y + 0.004f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);

	if (pos == m_nCurrentSkinPos)
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
	else
		CFrontend::SetDrawRGBA(130, 130, 130, 255);

	CFrontend::Print8(eSkinLoader::vSkins[id].sName.c_str(), x, y, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
}

void eNewFrontend::DrawStatText(int id)
{
	if (eStatsManager::GetStatName(id))
	{
		int drawID = id - (STATS_PER_PAGE * m_nCurrentStatsPage);

		// stat names
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(eStatsManager::GetStatName(id), m_fBoxPositionX + 0.02 + 0.004, m_fBoxPositionY + 0.05 * drawID + 0.004, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(eStatsManager::GetStatName(id), m_fBoxPositionX + 0.02, m_fBoxPositionY + 0.05 * drawID, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		// stat values
		sprintf(statsBuffer, "%d", eStatsManager::GetStat(id));



		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(statsBuffer, m_fBoxPositionX + 0.02 + 0.55 + 0.004, m_fBoxPositionY + 0.05 * drawID + 0.004, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(statsBuffer, m_fBoxPositionX + 0.02 + 0.55, m_fBoxPositionY + 0.05 * drawID, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	}
}

void eNewFrontend::DrawModText(int id)
{

}

void __declspec(naked) eNewFrontend::HookSelectMenuBackground()
{
	static int originalSwitch = 0x5D70FE;

	if (CFrontend::ms_currentMenu == MENU_STATS)
	{
		CFrontend::SetMenuBackground(CFileNames::ms_BonusEpPath.str);
	}
	else if (CFrontend::ms_currentMenu == MENU_MODS)
	{
		CFrontend::SetMenuBackground(CFileNames::ms_MainEpPath.str);
	}
	else if (CFrontend::ms_currentMenu == MENU_LEVEL_SELECT_DUO || (CFrontend::ms_currentMenu == MENU_NEW_SETTINGS))
	{
		CFrontend::SetMenuBackground(CFileNames::ms_MainEpPath.str);
	}
	else if (CFrontend::ms_currentMenu == MENU_SKINS)
	{
		CFrontend::SetMenuBackground(CFileNames::ms_BonusEpPath.str);
	}

	_asm
	{
		mov eax, ds:0x7C86F8
		jmp originalSwitch
	}
}

void __declspec(naked) eNewFrontend::HookExecuteMenuProcess()
{
	static int originalSwitchExec = 0x5D75DC;

	DrawEVisionMark();

	if (CFrontend::ms_currentMenu == MENU_STATS)
	{
		ProcessStatsMenu();
		StatsMenu();
	}
	else if (CFrontend::ms_currentMenu == MENU_MODS)
	{
		ProcessModsMenu();
		ModsMenu();
	}
	else if (CFrontend::ms_currentMenu == MENU_LEVEL_SELECT_DUO)
	{
		ProcessNewLevelSelect();
		NewLevelSelect();
	}
	else if (CFrontend::ms_currentMenu == MENU_NEW_SETTINGS)
	{
		ProcessNewSettingMenu();
		NewSettingMenu();		
	}
	else if (CFrontend::ms_currentMenu == MENU_SKINS)
	{
		ProcessSkins();
		Skins();

	}
	_asm
	{
		mov eax, ds:0x7C86F8
		jmp originalSwitchExec
	}
}

void eNewFrontend::HookDrawRasterLineFX(int a1, int a2, int a3, int a4)
{
	if (CFrontend::ms_currentMenu == MENU_SKINS)
		return;
	CRenderer::DrawRasterLineFX(a1, a2, a3, a4);
}

void eNewFrontend::HookCreateMenuLight()
{
	RwBBox bb;

    bb.inf.x = bb.inf.y = bb.inf.z = -100.0f;
    bb.sup.x = bb.sup.y = bb.sup.z = 100.f;

	RpWorld *oldWorld = (RpWorld *)RWSRCGLOBAL(curWorld);
	{
		ms_pMenuWorld = RpWorldCreate(&bb);
	}
	RWSRCGLOBAL(curWorld) = oldWorld;
	
	ms_pMenuLight = RpLightCreate(rpLIGHTAMBIENT);
	RpLightSetFlags(ms_pMenuLight, rpLIGHTLIGHTATOMICS);
	
	RpWorldAddLight(ms_pMenuWorld, ms_pMenuLight);


	// 3d aspect ratio calculation
	float X = *(float*)0x829584;
	float Y = *(float*)0x829588;
	float unk = *(float*)0x7D3450;

	float ratio = X / Y;

	CameraSize(CFrontend::GetFrontendCamera(), NULL, SCREEN_VIEWWINDOW, ratio);
}

void eNewFrontend::DestroyMenuLightWorld()
{
	RpWorldRemoveLight(ms_pMenuWorld, ms_pMenuLight);
	RpLightDestroy(ms_pMenuLight);
	RpWorldDestroy(ms_pMenuWorld);
}
