#pragma once
#include <rwcore.h>
#include <rwplcore.h>
#include <rpworld.h>

enum eNewMenuTypes {
	// new menus
	MENU_STATS = 24,
	MENU_LEVEL_SELECT_DUO,
	MENU_NEW_SETTINGS,
	MENU_MODS,
	MENU_SKINS
};

enum eLevelSelectButtons {
	LS_ORIGINAL,
	LS_NEW,
	LS_BACK
};

class eNewFrontend {
private:
	static char statsBuffer[256];
	static char szMenuPath[128];
	static wchar_t* m_szCheatText;
public:
	static void InitHooks();
	static int  ms_lastCustomMenu;
	static RpWorld* ms_pMenuWorld;
	static RpLight* ms_pMenuLight;


	static void Init();
	static void MainMenu();
	static bool ProcessMainMenu();

	static void SettingsMenu();

	static bool IsCustomMenu(int menu);

	static void DrawEVisionMark();

	static float m_fBoxPositionX;
	static float m_fBoxPositionY;
	static float m_fSkinsBoxPositionX;
	static float m_fSkinsBoxPositionY;

	static int   m_pStatsMenu[2];
	static int   m_allStatsPages;
	static int   m_leftoverStatsPage;
	static int   m_nCurrentStatsPage;
	static int   m_nCurrentModsPage;
	static wchar_t  m_szStatsBuffer[128];
	static void StatsMenu();
	static void ProcessStatsMenu();
	static int m_nCurrentModPos;
	static int m_nModAdjustID;

	static void ModsMenu();
	static void ProcessModsMenu();

	static bool m_bNewLevels;

	static void NewLevelSelect();
	static void ProcessNewLevelSelect();
	static void NewSettingMenu();
	static void ProcessNewSettingMenu();

	static int m_nCurrentSkinPos;
	static int m_nSkinAdjustID;

	static void Skins();
	static void ProcessSkins();

	static void AddSkinButton(int id, int pos);


	static void DrawStatText(int id);
	static void DrawModText(int id);


	// hooks 
	static void HookSelectMenuBackground();
	static void HookExecuteMenuProcess();

	static void HookDrawRasterLineFX(int a1, int a2, int a3, int a4);
	static void HookCreateMenuLight();

	static void DestroyMenuLightWorld();
};

