#include "eNewFrontend.h"
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
#include <iostream>

int eNewFrontend::m_pStatsMenu[2] = { (int)eNewFrontend::ProcessStatsMenu, (int)eNewFrontend::StatsMenu };
int eNewFrontend::ms_lastCustomMenu;
float eNewFrontend::m_fBoxPositionX;
float eNewFrontend::m_fBoxPositionY;
char eNewFrontend::statsBuffer[256];
wchar_t eNewFrontend::m_szStatsBuffer[128];
int eNewFrontend::m_allStatsPages;
int eNewFrontend::m_leftoverStatsPage;
int eNewFrontend::m_nCurrentStatsPage;
int eNewFrontend::m_nCurrentModsPage;
wchar_t* eNewFrontend::m_szCheatText = (wchar_t*)0x7D6360;

void eNewFrontend::InitHooks()
{
	InjectHook(0x600C20, eNewFrontend::MainMenu, PATCH_JUMP);
	InjectHook(0x600B34, eNewFrontend::ProcessMainMenu, PATCH_JUMP);
	InjectHook(0x5D70F9, eNewFrontend::HookSelectMenuBackground, PATCH_JUMP);
	InjectHook(0x5D75D7, eNewFrontend::HookExecuteMenuProcess, PATCH_JUMP);

	// lcd display
	Nop(0x5D7504, 5);

}

void eNewFrontend::Init()
{
	m_fBoxPositionX = 0.155f;
	m_fBoxPositionY = 0.277f;
	m_nCurrentStatsPage = 0;
	m_nCurrentModsPage = 0;
	m_allStatsPages = 3;

}


void eNewFrontend::MainMenu()
{
	CFrontend::ms_fMenuPositionX = 0.15f;
	float y_pos = CFrontend::ms_fMenuPositionY;
	float y_temp = 0.0f;
	float y_adjust = 0.30000001f;

	CFrontend::DrawMenuCameraCounter(CText::GetFromKey16("MAINM"));


	float m_fHudStretch = *(float*)0x7D3458;
	float m_fLogoScale = *(float*)0x7D63FC;

	float logoX = m_fHudStretch * m_fLogoScale;
	int logoTexture = CFrontend::GetTextureFromTXD(*(int*)0x7C8704, "logo");


	CRenderer::DrawQuad2d(*(float*)0x7D6408 + 0.45f,*(float*)0x7D6404,logoX,*(float*)0x7D6400, 180, 180, 180, 255, logoTexture);


	y_temp = y_pos + y_adjust - CFrontend::ms_fMenuPositionY;
	CFrontend::AddOption(CText::GetFromKey16("PLAY"), CFrontend::ms_fMenuPositionX, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_PLAY);

	y_temp = y_pos +  y_adjust;
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
	CFrontend::AddOption(CText::GetFromKey16("QUITPRG"), CFrontend::ms_fMenuPositionX, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_QUITPRG);
}

bool __declspec(naked) eNewFrontend::ProcessMainMenu()
{
	static int arg = 0;
	static int jmpPoint = 0x6025B6;
	
	if (CInputManager::FrontendPressedUp())
	{
		if (--CFrontend::ms_menuButton < 0)
			CFrontend::ms_menuButton = MB_QUITPRG;
	}

	if (CInputManager::FrontendPressedDown())
	{
		if (++CFrontend::ms_menuButton >= MB_TOTAL_MENUS)
			CFrontend::ms_menuButton = 0;
	}

	if (CInputManager::FrontedMouseHovered())
		CFrontend::ms_menuButton = CFrontend::GetHoveredItem();

	if (CInputManager::FrontendPressedEscape())
			CFrontend::SetCurrentMenu(MENU_QUIT);



	if (CInputManager::FrontendButtonEnter())
	{
		switch (CFrontend::ms_menuButton)
		{
		case MB_PLAY:
			arg = CallAndReturn<int, 0x5D6900>();
			if (arg == -1)
			{
				Call<0x5D6A60>();
				CFrontend::m_bNewGame = 0;
				*(int*)0x7C86F4 = 0;
				CFrontend::SetCurrentMenu(MENU_GAMMA_SETTINGS);
			}
			else
				Call<0x5D6720, int, int>(arg, 1);
			break;
		case MB_SELSCE:
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
		case MB_QUITPRG:
			CFrontend::SetCurrentMenu(MENU_QUIT);
			break;
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

bool eNewFrontend::IsCustomMenu(int menu)
{
	if (menu > MENU_QUIT && menu < MENU_MODS)
		return true;
	else
		return false;
}

void eNewFrontend::DrawEVisionMark()
{

	CFrontend::SetDrawRGBA(255, 255, 255, 48);
	CFrontend::Print8("PluginMH 0.5 by ermaccer", 0.0, 0.0, 0.28f, 0.28f, 0.0f, FONT_TYPE_DEFAULT);
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

	sprintf(tmp, "LOADED MODIFICATIONS: %d", eModLoader::modFolders.size());
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
	//CFrontend::ms_fMenuPositionX = 0.15f;
	float y_pos = CFrontend::ms_fMenuPositionY;
	float y_temp = 0.0f;
	float y_adjust = 0.30000001f;

	CFrontend::DrawMenuCameraCounter(CText::GetFromKey16("MAINM"));


	y_temp = y_pos + y_adjust - CFrontend::ms_fMenuPositionY;
	CFrontend::AddOption(L"ORIGINAL", CFrontend::ms_fMenuPositionX, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == LS_ORIGINAL);
	y_temp = y_pos + y_adjust;
	CFrontend::AddOption(L"CUSTOM", CFrontend::ms_fMenuPositionX, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == LS_NEW);
	y_temp += CFrontend::ms_fMenuPositionY;
	CFrontend::AddOption(L"BACK", CFrontend::ms_fMenuPositionX, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == LS_BACK);

}

void eNewFrontend::ProcessNewLevelSelect()
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
			Sleep(250);
			CFrontend::SetCurrentMenu(MENU_LEVEL_SELECT);

			break;
		case LS_NEW:
			//*(int*)0x7C89E4 = 7;
			CFrontend::SetCurrentMenu(MENU_19);
			break;
		case LS_BACK:
			CFrontend::SetCurrentMenu(MENU_FRONTEND);
			break;
		}
	}
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
	CFrontend::AddOption(L"MOD SETTINGS", CFrontend::ms_fMenuPositionX, y_temp
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

	_asm
	{
		mov eax, ds:0x7C86F8
		jmp originalSwitchExec
	}
}
