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
#include "..\..\resource.h"
#include "..\manhunt\Clump.h"
#include "..\manhunt\ClumpDict.h"
#include "..\manhunt\Entity.h"
#include "..\RenderWare.h"
#include "eSkinLoader.h"
#include "..\core\eSettingsManager.h"
#include "eGUI.h"
#include "..\manhunt\AudioManager.h"
#include "..\..\MHWSF.h"
#include <iostream>

#define MODS_PER_PAGE 10
#define SKINS_PER_PAGE 12

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
float eNewFrontend::m_fMaxStatsWidth;
int eNewFrontend::m_nCurrentModsPage;
int   eNewFrontend::m_allModsPages;
int eNewFrontend::m_nCurrentSkinPos;
int eNewFrontend::m_nSkinAdjustID;
int eNewFrontend::m_allSkinsPages;
int eNewFrontend::m_nCurrentSkinPage;
float eNewFrontend::m_fSkinRotationX;
float eNewFrontend::m_fSkinRotationY;
int eNewFrontend::m_nCurrentModPos;
int eNewFrontend::m_nModAdjustID;
wchar_t* eNewFrontend::m_szCheatText = (wchar_t*)0x7D6360;
RpWorld * eNewFrontend::ms_pMenuWorld;
RpLight * eNewFrontend::ms_pMenuLight;
bool eNewFrontend::m_bNewLevels;
bool eNewFrontend::m_bSkinsFreezeRotation;


void eNewFrontend::InitHooks()
{

	InjectHook(0x600C20, eNewFrontend::MainMenu, PATCH_JUMP);
	InjectHook(0x600B34, eNewFrontend::ProcessMainMenu, PATCH_JUMP);
	InjectHook(0x5D70F9, eNewFrontend::HookSelectMenuBackground, PATCH_JUMP);
	InjectHook(0x5D75D7, eNewFrontend::HookExecuteMenuProcess, PATCH_JUMP);

	// lcd display
	if ( !eSettingsManager::bOldStyleMenu )
		InjectHook(0x5D74B0, 0x5D7511, PATCH_JUMP);
	// lines?
	InjectHook(0x5D77B1, eNewFrontend::HookDrawRasterLineFX, PATCH_CALL);
	InjectHook(0x4D7A91, eNewFrontend::HookCreateMenuLight, PATCH_CALL);

}

void eNewFrontend::Init()
{
	m_fBoxPositionX = 0.5f-0.69f/2.0f;
	m_fBoxPositionY = 0.5f-0.55f/2.0f;
	m_fSkinsBoxPositionX = 0.532f;
	m_fSkinsBoxPositionY = 0.5f-0.6f/2.0f;
	m_nCurrentStatsPage = 0;
	m_nCurrentModsPage = 0;
	m_allModsPages = ((int)ceil(float(eModLoader::modFolders.size()) / float(MODS_PER_PAGE)));
	m_allStatsPages = 3;

	eSkinLoader::ReadFile();



	m_nCurrentSkinPos = eSkinLoader::ms_iCurrentSkin;
	//m_nSkinAdjustID = eSkinLoader::ms_iCurrentSkinAdjust;
	m_allSkinsPages = ((int)ceil(float(eSkinLoader::vSkins.size()) / float(SKINS_PER_PAGE)));
	m_nCurrentSkinPage = 0;
	m_fSkinRotationX = 0.0f;
	m_fSkinRotationY = 0.0f;
	m_nModAdjustID = 0;
	m_nCurrentModPos = 0;
	m_bSkinsFreezeRotation = false;
}


void eNewFrontend::MainMenu()
{
	float x_pos = !eSettingsManager::bOldStyleMenu ? SCREEN_FROM_CENTER(0.15f) : CFrontend::ms_fMenuPositionX;
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


	CRenderer::DrawQuad2d(*(float*)0x7D6408 + (!eSettingsManager::bOldStyleMenu ? SCREEN_SCLX(0.45f) : 0.0f), *(float*)0x7D6404, logoX, *(float*)0x7D6400, 180, 180, 180, 255, logoTexture);

	if (!m_bNewLevels)
	{
		y_temp = 0.4f-CFrontend::ms_fMenuPositionY*2.0f;/*y_adjust*/
		
		CFrontend::AddOption(CText::GetFromKey16("PLAY"), x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_PLAY);
		
		y_temp += CFrontend::ms_fMenuPositionY;
		
		CFrontend::AddOption(CText::GetFromKey16("SELSCE"), x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_SELSCE);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("LOADG"), x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_LOADG);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("SETT"), x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_SETT);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("BONFEA"), x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_BONFEA);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"STATS", x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_STATS);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"MODIFICATIONS", x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_MODIFICATIONS);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"SKINS", x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_SKINS);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(CText::GetFromKey16("QUITPRG"), x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_QUITPRG);
	}
	else
	{
		y_temp = 0.4f;
		
		CFrontend::AddOption(L"ORIGINAL", x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_PLAY);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"CUSTOM", x_pos, y_temp
			, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == MB_SELSCE);

		y_temp += CFrontend::ms_fMenuPositionY;
		CFrontend::AddOption(L"BACK", x_pos, y_temp
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
					CFrontend::m_bNewGame = 1;
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
				m_nCurrentStatsPage = 0;
				CFrontend::SetCurrentMenu(MENU_STATS);
				break;
			case MB_MODIFICATIONS:
				m_nCurrentModsPage = 0;
				CFrontend::SetCurrentMenu(MENU_MODS);
				break;
			case MB_SKINS:
				m_nCurrentSkinPage = 0;
				m_fSkinRotationX = 0.0f;
				m_fSkinRotationY = 0.0f;
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
	
	m_fMaxStatsWidth = 0.0f;
	for (int p = 0; p < m_allStatsPages; p++)
	{
		for (int i = 0; i < STATS_PER_PAGE; i++)
		{
			int id = i + (STATS_PER_PAGE * p);
			if ( eStatsManager::GetStatName(id) )
			{
				sprintf(statsBuffer, "%d", eStatsManager::GetStat(id));
				float textw = CFrontend::GetTextWidth8(statsBuffer, 0.7f, FONT_TYPE_DEFAULT);
				
				if ( textw > m_fMaxStatsWidth )
					m_fMaxStatsWidth = textw;
			}
		}
	}
	
	for (int i = 0; i < STATS_PER_PAGE; i++)
	{
		if ( i & 1 )
			CRenderer::DrawQuad2d(SCREEN_FROM_CENTER(m_fBoxPositionX), m_fBoxPositionY + 0.05f * i, SCREEN_SCLX(0.69f), 0.05f, 128, 128, 128, 128, 0);
		else
			CRenderer::DrawQuad2d(SCREEN_FROM_CENTER(m_fBoxPositionX), m_fBoxPositionY + 0.05f * i, SCREEN_SCLX(0.69f), 0.05f, 64, 64, 64, 128, 0);
	}
	
	for (int i = 0; i < STATS_PER_PAGE; i++)
	{	
		if (m_nCurrentStatsPage > 0)
			DrawStatText(i + (STATS_PER_PAGE * m_nCurrentStatsPage));
		else
			DrawStatText(i);
		
	}
	
	bool isDown = false;
	bool isUp = false;

	FEMouse mouse = CInputManager::GetFrontendMouse();

	float size = 0.7f*1.5f;
	float pad = 0.005f*1.5f;
	
	if ( m_nCurrentStatsPage > 0 )
	{
		float h = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size) * 0.723f;
		float w = CFrontend::GetTextWidth8("~up~", size, FONT_TYPE_DEFAULT);
		
		float px = SCREEN_FROM_CENTER(m_fBoxPositionX + 0.69f)-w;
		float py = m_fBoxPositionY-h-pad;
		float pw = w;
		float ph = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size);
		
		if (mouse.X >= px && mouse.X < px+pw && mouse.Y >= py && mouse.Y < py+ph)
			isUp = true;
		
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8("~up~", px+SCREEN_SCLX(0.004f), py+0.004f, size, size, 0.0, FONT_TYPE_DEFAULT);
		if ( isUp && *(int*)0x7C8E44 )
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
		else
			CFrontend::SetDrawRGBA(128, 128, 128, 255);
		CFrontend::Print8("~up~", px, py, size, size, 0.0, FONT_TYPE_DEFAULT);
	}
	
	if ( m_nCurrentStatsPage < m_allStatsPages-1 )
	{
		float h = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size)*0.384f;
		float w = CFrontend::GetTextWidth8("~down~", size, FONT_TYPE_DEFAULT);
		
		float px = SCREEN_FROM_CENTER(m_fBoxPositionX + 0.69f)-w;
		float py = m_fBoxPositionY-h+pad + 0.05f * (STATS_PER_PAGE);
		float pw = w;
		float ph = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size);
		
		if (mouse.X >= px && mouse.X < px+pw && mouse.Y >= py && mouse.Y < py+ph)
			isDown = true;
		
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8("~down~", px+SCREEN_SCLX(0.004f), py+0.004f, size, size, 0.0, FONT_TYPE_DEFAULT);
		if ( isDown && *(int*)0x7C8E44 )
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
		else
			CFrontend::SetDrawRGBA(128, 128, 128, 255);
		CFrontend::Print8("~down~", px, py, size, size, 0.0, FONT_TYPE_DEFAULT);
	}
	
	if (isUp && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		m_nCurrentStatsPage--;

	if (isDown && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		m_nCurrentStatsPage++;

	if (m_nCurrentStatsPage < 0)
		m_nCurrentStatsPage = 0;
	
	if (m_nCurrentStatsPage > m_allStatsPages - 1)
		m_nCurrentStatsPage = m_allStatsPages - 1;

	CFrontend::PrintInfo(L"Press ~up~ or ~down~ to navigate", L"", CText::GetFromKey16("IBACK"), L"");
}

void eNewFrontend::ProcessStatsMenu()
{
	if (CInputManager::FrontendPressedEscape() || CFrontend::GetInfoBarInput3())
		CFrontend::SetCurrentMenu(MENU_19);

	if (CInputManager::FrontendPressedUp() || (CPad::NewMouseControllerState.wheelUp && !CPad::OldMouseControllerState.wheelUp))
		m_nCurrentStatsPage--;

	if (CInputManager::FrontendPressedDown() || (CPad::NewMouseControllerState.wheelDown && !CPad::OldMouseControllerState.wheelDown))
		m_nCurrentStatsPage++;

	if (m_nCurrentStatsPage < 0)
		m_nCurrentStatsPage = 0;

	if (m_nCurrentStatsPage > m_allStatsPages - 1)
		m_nCurrentStatsPage = m_allStatsPages - 1;

}

void eNewFrontend::ModsMenu()
{
	float infoBarOffset = -0.08f;
	float SizeX = 0.80f;
	float PosX = 0.5f-SizeX/2.0f;
	int mods = eModLoader::modFolders.size();
	wchar_t tmp[128];
			
	CFrontend::SetDrawRGBA(255,255,255, 255);
	wsprintfW(m_szStatsBuffer, L"MODIFICATIONS %d/%d", m_nCurrentModsPage + 1, m_allModsPages);
	CFrontend::DrawMenuCameraCounter(m_szStatsBuffer);

	for (int i = 0; i < MODS_PER_PAGE; i++)
	{
		if ( i & 1 )
			CRenderer::DrawQuad2d(SCREEN_FROM_CENTER(PosX), m_fBoxPositionY + 0.05f * i, SCREEN_SCLX(SizeX), 0.05f, 128, 128, 128, 128, 0);
		else
			CRenderer::DrawQuad2d(SCREEN_FROM_CENTER(PosX), m_fBoxPositionY + 0.05f * i, SCREEN_SCLX(SizeX), 0.05f, 64, 64, 64, 128, 0);
	}
	

	/*const char* modHelp = "Press ~up~ or ~down~ or use mouse to select a mod. ESC to quit.";
	CFrontend::SetDrawRGBA(0, 0, 0, 255);
	CFrontend::Print8(skinsHelp, 0.05f + 0.004f, 0.90f + 0.004, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	CFrontend::SetDrawRGBA(255, 255, 255, 255);
	CFrontend::Print8(skinsHelp, 0.05f, 0.90f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);*/

	
	float maxModsWidth = 0.0f;
	for (int i = 0; i < mods; i++)
	{
		sprintf(statsBuffer, "%d file(s)", eModLoader::m_vMods[i].files.size());
		if ( eModLoader::m_vMods[i].conficlts.size() != 0 )
			sprintf(statsBuffer, "%s, %d conflict(s)", statsBuffer, eModLoader::m_vMods[i].conficlts.size());
		if ( eModLoader::m_vMods[i].ignored.size() != 0 )
			sprintf(statsBuffer, "%s, %d ignored", statsBuffer, eModLoader::m_vMods[i].ignored.size());
		float textw = CFrontend::GetTextWidth8(statsBuffer, 0.7f, FONT_TYPE_DEFAULT);
				
		if ( textw > maxModsWidth )
			maxModsWidth = textw;
	}
	
	for ( int i = m_nCurrentModsPage*MODS_PER_PAGE; i < min(m_nCurrentModsPage*MODS_PER_PAGE+MODS_PER_PAGE, mods); i++ )
	{
		bool red = false;
		bool yellow = false;
		int drawID = i - (m_nCurrentModsPage*MODS_PER_PAGE);
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(eModLoader::modFolders[i].c_str(), SCREEN_FROM_CENTER(PosX + 0.02f + 0.004f), m_fBoxPositionY + 0.05f * drawID + 0.004f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(eModLoader::modFolders[i].c_str(), SCREEN_FROM_CENTER(PosX + 0.02f), m_fBoxPositionY + 0.05f * drawID, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		
		sprintf(statsBuffer, "%d file(s)", eModLoader::m_vMods[i].files.size());
		if ( eModLoader::m_vMods[i].conficlts.size() != 0 )
			sprintf(statsBuffer, "%s, %d conflict(s)", statsBuffer, eModLoader::m_vMods[i].conficlts.size());
		if ( eModLoader::m_vMods[i].ignored.size() != 0 )
			sprintf(statsBuffer, "%s, %d ignored", statsBuffer, eModLoader::m_vMods[i].ignored.size());
		
		if ( eModLoader::m_vMods[i].ignored.size() != 0 )
			yellow = true;
		if ( eModLoader::m_vMods[i].conficlts.size() != 0 )
			red = true;
		
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(statsBuffer, SCREEN_FROM_CENTER(PosX + SizeX - 0.02f + 0.004f) - maxModsWidth, m_fBoxPositionY + 0.05f * drawID + 0.004f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		
		if ( red )
			CFrontend::SetDrawRGBA(255, 0, 0, 255);
		else if ( yellow )
			CFrontend::SetDrawRGBA(255, 255, 0, 255);
		else
			CFrontend::SetDrawRGBA(255, 255, 255, 255);                              
		CFrontend::Print8(statsBuffer, SCREEN_FROM_CENTER(PosX + SizeX - 0.02f) - maxModsWidth, m_fBoxPositionY + 0.05f * drawID, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);	
	}
	
	bool isDown = false;
	bool isUp = false;

	FEMouse mouse = CInputManager::GetFrontendMouse();

	float size = 0.7f*1.5f;
	float pad = 0.005f*1.5f;
	
	if ( m_nCurrentModsPage > 0 )
	{
		float h = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size) * 0.723f;
		float w = CFrontend::GetTextWidth8("~up~", size, FONT_TYPE_DEFAULT);
		
		float px = SCREEN_FROM_CENTER(PosX + SizeX)-w;
		float py = m_fBoxPositionY-h-pad;
		float pw = w;
		float ph = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size);
		
		if (mouse.X >= px && mouse.X < px+pw && mouse.Y >= py && mouse.Y < py+ph)
			isUp = true;
		
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8("~up~", px+SCREEN_SCLX(0.004f), py+0.004f, size, size, 0.0, FONT_TYPE_DEFAULT);
		if ( isUp && *(int*)0x7C8E44 )
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
		else
			CFrontend::SetDrawRGBA(128, 128, 128, 255);
		CFrontend::Print8("~up~", px, py, size, size, 0.0, FONT_TYPE_DEFAULT);
	}
	
	if ( m_nCurrentModsPage < m_allModsPages-1 )
	{
		float h = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size)*0.384f;
		float w = CFrontend::GetTextWidth8("~down~", size, FONT_TYPE_DEFAULT);
		
		float px = SCREEN_FROM_CENTER(PosX + SizeX)-w;
		float py = m_fBoxPositionY-h+pad + 0.05f * (STATS_PER_PAGE);
		float pw = w;
		float ph = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size);
		
		if (mouse.X >= px && mouse.X < px+pw && mouse.Y >= py && mouse.Y < py+ph)
			isDown = true;
		
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8("~down~", px+SCREEN_SCLX(0.004f), py+0.004f, size, size, 0.0, FONT_TYPE_DEFAULT);
		if ( isDown && *(int*)0x7C8E44 )
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
		else
			CFrontend::SetDrawRGBA(128, 128, 128, 255);
		CFrontend::Print8("~down~", px, py, size, size, 0.0, FONT_TYPE_DEFAULT);
	}
	
	if (isUp && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		m_nCurrentModsPage--;

	if (isDown && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		m_nCurrentModsPage++;

	if (m_nCurrentModsPage < 0)
		m_nCurrentModsPage = 0;
	
	if (m_nCurrentModsPage > m_allModsPages - 1)
		m_nCurrentModsPage = m_allModsPages - 1;


	wsprintfW(tmp, L"Mods: %d", mods);
	CFrontend::PrintInfo(L"Press ~up~ or ~down~ to navigate", tmp, CText::GetFromKey16("IBACK"), L"");
}

void eNewFrontend::ProcessModsMenu()
{
	if (CInputManager::FrontendPressedEscape() || CFrontend::GetInfoBarInput3())
		CFrontend::SetCurrentMenu(MENU_19);

	if (CInputManager::FrontendPressedUp() || (CPad::NewMouseControllerState.wheelUp && !CPad::OldMouseControllerState.wheelUp))
		m_nCurrentModsPage--;

	if (CInputManager::FrontendPressedDown() || (CPad::NewMouseControllerState.wheelDown && !CPad::OldMouseControllerState.wheelDown))
		m_nCurrentModsPage++;

	if (m_nCurrentModsPage < 0)
		m_nCurrentModsPage = 0;
	
	if (m_nCurrentModsPage > m_allModsPages - 1)
		m_nCurrentModsPage = m_allModsPages - 1;
	
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
	float x_pos = !eSettingsManager::bOldStyleMenu ? SCREEN_FROM_CENTER(0.15f) : CFrontend::ms_fMenuPositionX;
	float y_pos = CFrontend::ms_fMenuPositionY;
	float y_temp = 0.0f;
	float y_adjust = 0.30000001f;



	CFrontend::DrawMenuCameraCounter(CText::GetFromKey16("MAINM"));


	y_temp = y_pos + y_adjust - CFrontend::ms_fMenuPositionY;
	CFrontend::AddOption(CText::GetFromKey16("SETT"), x_pos, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == LS_ORIGINAL);
	y_temp = y_pos + y_adjust;
	CFrontend::AddOption(L"PLUGINMH SETTINGS", x_pos, y_temp
		, CFrontend::ms_fTextXScale, CFrontend::ms_fTextYScale, CFrontend::ms_menuButton == LS_NEW);
	y_temp += CFrontend::ms_fMenuPositionY;
	CFrontend::AddOption(L"BACK", x_pos, y_temp
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

void eNewFrontend::UpdateSkinId()
{
	m_nCurrentSkinPos = eSkinLoader::ms_iCurrentSkin;
}

void eNewFrontend::RenderSkin()
{
	if (eSkinLoader::ms_pPlayerClump && eSkinLoader::ms_bSkinLoaded)
	{
		RwV2d vw;
		vw.x = SCREEN_VIEWWINDOW * (SCREEN_ASPECT_RATIO / DEFAULT_ASPECT_RATIO);
		vw.y = SCREEN_VIEWWINDOW / DEFAULT_ASPECT_RATIO;
		
		vw.x /= 0.7f;
		vw.y /= 0.7f;
		
		RwCameraSetViewWindow(CFrontend::GetFrontendCamera(), &vw);
	
		static unsigned int LastFlash = 0;

		const RwV3d pos = { 1.05f, -1.00f, 4.05f };
		RwRGBAReal AmbientColor = { 0.80f, 0.80f, 0.80f, 1.0f };
		if (GetTickCount() - LastFlash > 7 && !m_bSkinsFreezeRotation) {
			m_fSkinRotationX += 1.0f;
			if (m_fSkinRotationX > 360.0f)
				m_fSkinRotationX -= 360.0f;
			LastFlash = GetTickCount();
		}
		
		if ( m_bSkinsFreezeRotation )
		{
			if( CPad::NewMouseControllerState.lmb )
			{
				float xx = CPad::NewMouseControllerState.X/2.0f;
				float yy = -CPad::NewMouseControllerState.Y/2.0f;
				
				m_fSkinRotationX += xx;
				if (m_fSkinRotationX > 360.0f)
					m_fSkinRotationX -= 360.0f;
				
				if (m_fSkinRotationX < 0.0f)
					m_fSkinRotationX -= 360.0f;
				
				m_fSkinRotationY += yy;
				
				if (m_fSkinRotationY > 360.0f)
					m_fSkinRotationY -= 360.0f;
				
				if (m_fSkinRotationY < 0.0f)
					m_fSkinRotationY -= 360.0f;
			}
		}
		else
			m_fSkinRotationY = 0.0f;
					
		RwFrame *frame = RpClumpGetFrame(eSkinLoader::ms_pPlayerClump);		
		RwFrameTransform(frame, RwFrameGetMatrix(RwCameraGetFrame(CFrontend::GetFrontendCamera())), rwCOMBINEREPLACE);		
		RwFrameTranslate(frame, &pos, rwCOMBINEPRECONCAT);
		RwFrameUpdateObjects(frame);
		
		ClumpRotate(eSkinLoader::ms_pPlayerClump, CFrontend::GetFrontendCamera(), m_fSkinRotationX, m_fSkinRotationY);

		CRenderer::SetIngameInfoRenderStates(1);

		RpWorld *oldWorld = (RpWorld *)RWSRCGLOBAL(curWorld);
		
		RWSRCGLOBAL(curWorld) = ms_pMenuWorld;
		RpLightSetColor(ms_pMenuLight, &AmbientColor);
		RpClumpRender(eSkinLoader::ms_pPlayerClump);
		RWSRCGLOBAL(curWorld) = oldWorld;
		

		CRenderer::SetIngameInfoRenderStates(0);
	}
}

void eNewFrontend::Skins()
{
	float infoBarOffset = -0.03f;//-0.08f;
	
	wsprintfW(m_szStatsBuffer, L"SKINS %d/%d", m_nCurrentSkinPage + 1, m_allSkinsPages);
	CFrontend::DrawMenuCameraCounter(m_szStatsBuffer);


	CRenderer::DrawQuad2d(SCREEN_FROM_CENTER(m_fSkinsBoxPositionX), m_fSkinsBoxPositionY + infoBarOffset, SCREEN_SCLX(0.40f), 0.6f, 180, 180, 180, 90, 0);


	int skins = eSkinLoader::vSkins.size();
		
	for ( int i = m_nCurrentSkinPage*SKINS_PER_PAGE; i < min(m_nCurrentSkinPage*SKINS_PER_PAGE+SKINS_PER_PAGE, skins); i++ )
	{
		int drawID = i - (m_nCurrentSkinPage*SKINS_PER_PAGE);
		AddSkinButton(i, drawID, infoBarOffset);
	}
	
	FEMouse mouse = CInputManager::GetFrontendMouse();
	
	bool isDown = false;
	bool isUp = false;
	
	float size = 0.7f*1.5f;
	float pad = 0.005f*1.5f;
	
	if ( m_nCurrentSkinPage > 0 )
	{
		float h = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size) * 0.723f;
		float w = CFrontend::GetTextWidth8("~up~", size, FONT_TYPE_DEFAULT);
		
		float px = SCREEN_FROM_CENTER(m_fSkinsBoxPositionX + 0.40f)-w;
		float py = m_fSkinsBoxPositionY + infoBarOffset-h-pad;
		float pw = w;
		float ph = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size);
		
		if (mouse.X >= px && mouse.X < px+pw && mouse.Y >= py && mouse.Y < py+ph)
			isUp = true;
		
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8("~up~", px+SCREEN_SCLX(0.004f), py+0.004f, size, size, 0.0, FONT_TYPE_DEFAULT);
		if ( isUp && *(int*)0x7C8E44 )
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
		else
			CFrontend::SetDrawRGBA(128, 128, 128, 255);
		CFrontend::Print8("~up~", px, py, size, size, 0.0, FONT_TYPE_DEFAULT);
	}
	
	if ( m_nCurrentSkinPage < m_allSkinsPages-1 )
	{
		float h = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size)*0.384f;
		float w = CFrontend::GetTextWidth8("~down~", size, FONT_TYPE_DEFAULT);
		
		float px = SCREEN_FROM_CENTER(m_fSkinsBoxPositionX + 0.40f)-w;
		float py = m_fSkinsBoxPositionY + infoBarOffset + 0.6f-h+pad;
		float pw = w;
		float ph = CFrontend::GetFontHeight(FONT_TYPE_DEFAULT, size);
		
		if (mouse.X >= px && mouse.X < px+pw && mouse.Y >= py && mouse.Y < py+ph)
			isDown = true;
		
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8("~down~", px+SCREEN_SCLX(0.004f), py+0.004f, size, size, 0.0, FONT_TYPE_DEFAULT);
		if ( isDown && *(int*)0x7C8E44 )
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
		else
			CFrontend::SetDrawRGBA(128, 128, 128, 255);
		CFrontend::Print8("~down~", px, py, size, size, 0.0, FONT_TYPE_DEFAULT);
	}
	
	if (isUp && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		m_nCurrentSkinPage--;

	if (isDown && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		m_nCurrentSkinPage++;

	if (m_nCurrentSkinPage < 0)
		m_nCurrentSkinPage = 0;
	
	if (m_nCurrentSkinPage > m_allSkinsPages - 1)
		m_nCurrentSkinPage = m_allSkinsPages - 1;
	
	
	wsprintfW(m_szStatsBuffer, L"Skins: %d", eSkinLoader::vSkins.size());
	CFrontend::PrintInfo(L"Press ~up~ or ~down~ to change skin", m_szStatsBuffer, CText::GetFromKey16("IBACK"), m_bSkinsFreezeRotation ? L"Rotate" : L"Freeze");
	
	CRenderer::DrawRasterLineFX(0, 0, 0, 32);
	
	RenderSkin();
}
	
void eNewFrontend::ProcessSkins()
{
	eSkinLoader::LoadPlayerDff();

	if (CInputManager::FrontendPressedEscape() || CFrontend::GetInfoBarInput3())
	{
		eSkinLoader::SaveFile(m_nCurrentSkinPos, 0);
		CFrontend::SetCurrentMenu(MENU_19);
	}

	if (CFrontend::GetInfoBarInput4())
		m_bSkinsFreezeRotation ^= 1;

	if (CInputManager::FrontendPressedUp())
	{
		if (--m_nCurrentSkinPos < 0)
			m_nCurrentSkinPos = 0;
		
		m_nCurrentSkinPage = ((int)ceil(float(m_nCurrentSkinPos + 1) / float(SKINS_PER_PAGE))) - 1;

		eSkinLoader::ReloadPlayerDff(m_nCurrentSkinPos);
	}

	if (CInputManager::FrontendPressedDown())
	{
		if (++m_nCurrentSkinPos > eSkinLoader::vSkins.size() - 1)
			m_nCurrentSkinPos = eSkinLoader::vSkins.size() - 1;
		
		m_nCurrentSkinPage = ((int)ceil(float(m_nCurrentSkinPos + 1) / float(SKINS_PER_PAGE))) - 1;
		
		eSkinLoader::ReloadPlayerDff(m_nCurrentSkinPos);
	}

	if (CPad::NewMouseControllerState.wheelUp && !CPad::OldMouseControllerState.wheelUp)
		m_nCurrentSkinPage--;
	
	if (CPad::NewMouseControllerState.wheelDown && !CPad::OldMouseControllerState.wheelDown)
		m_nCurrentSkinPage++;
	
	if (m_nCurrentSkinPage < 0)
		m_nCurrentSkinPage = 0;
	
	if (m_nCurrentSkinPage > m_allSkinsPages - 1)
		m_nCurrentSkinPage = m_allSkinsPages - 1;
}

void eNewFrontend::AddSkinButton(int id, int pos, float offset)
{
	int len = eSkinLoader::vSkins[id].sName.length();

	float x = SCREEN_FROM_CENTER(m_fSkinsBoxPositionX + 0.01f);
	float y = m_fSkinsBoxPositionY /*+ 0.03f*/ + 0.05f* pos + offset;
	float x_size = len * 0.0097f;
	float y_size = 0.045f;

	
	FEMouse mouse = CInputManager::GetFrontendMouse();

	bool isInside = false;

	if (mouse.X >= x && mouse.X < x + x_size && mouse.Y >= y && mouse.Y < y + y_size)
		isInside = true;


	if (isInside)
	{
		if (CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		{
			if ( !m_bSkinsFreezeRotation )
			{
				m_fSkinRotationX = 0.0f;
				m_fSkinRotationY = 0.0f;
			}
			m_nCurrentSkinPos = id;
			eSkinLoader::ReloadPlayerDff(id);
			DMAudio.PlayFrontEndSound(0, -1.0f);
		}
	}
	
	CFrontend::SetDrawRGBA(0, 0, 0, 255);
	CFrontend::Print8(eSkinLoader::vSkins[id].sName.c_str(), x + SCREEN_SCLX(0.002f), y + 0.004f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);

	if ( isInside && id != m_nCurrentSkinPos )
		CFrontend::SetDrawRGBA(200, 200, 200, 255);
	else
	{
		if (id == m_nCurrentSkinPos)
			CFrontend::SetDrawRGBA(255, 255, 255, 255);
		else
			CFrontend::SetDrawRGBA(130, 130, 130, 255);
	}

	CFrontend::Print8(eSkinLoader::vSkins[id].sName.c_str(), x, y, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
}

void eNewFrontend::DrawStatText(int id)
{
	if (eStatsManager::GetStatName(id))
	{
		int drawID = id - (STATS_PER_PAGE * m_nCurrentStatsPage);

		// stat names
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(eStatsManager::GetStatName(id), SCREEN_FROM_CENTER(m_fBoxPositionX + 0.02f + 0.004f), m_fBoxPositionY + 0.05f * drawID + 0.004f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
		CFrontend::Print8(eStatsManager::GetStatName(id), SCREEN_FROM_CENTER(m_fBoxPositionX + 0.02f), m_fBoxPositionY + 0.05f * drawID, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		// stat values
		sprintf(statsBuffer, "%d", eStatsManager::GetStat(id));
		
		CFrontend::SetDrawRGBA(0, 0, 0, 255);
		CFrontend::Print8(statsBuffer, SCREEN_FROM_CENTER(m_fBoxPositionX - 0.02f + 0.69f + 0.004f) - m_fMaxStatsWidth, m_fBoxPositionY + 0.05f * drawID + 0.004f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
		CFrontend::SetDrawRGBA(255, 255, 255, 255);                              
		CFrontend::Print8(statsBuffer, SCREEN_FROM_CENTER(m_fBoxPositionX - 0.02f + 0.69f) - m_fMaxStatsWidth, m_fBoxPositionY + 0.05f * drawID, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
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
	/*
	float X = *(float*)0x829584;
	float Y = *(float*)0x829588;
	float unk = *(float*)0x7D3450;

	float ratio = X / Y;

	CameraSize(CFrontend::GetFrontendCamera(), NULL, SCREEN_VIEWWINDOW, DEFAULT_ASPECT_RATIO);
	*/
}

void eNewFrontend::DestroyMenuLightWorld()
{
	if (ms_pMenuWorld && ms_pMenuLight)
		RpWorldRemoveLight(ms_pMenuWorld, ms_pMenuLight);
	if (ms_pMenuLight)
		RpLightDestroy(ms_pMenuLight);
	if (ms_pMenuWorld)
		RpWorldDestroy(ms_pMenuWorld);
}
