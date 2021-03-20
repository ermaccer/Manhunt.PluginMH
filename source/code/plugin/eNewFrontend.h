#pragma once

enum eNewMenuTypes {
	// new menus
	MENU_STATS = 24,
	MENU_LEVEL_SELECT_DUO,
	MENU_NEW_SETTINGS,
	MENU_MODS
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
	static void Init();
	static void MainMenu();
	static bool ProcessMainMenu();
	static bool IsCustomMenu(int menu);

	static void DrawEVisionMark();

	static float m_fBoxPositionX;
	static float m_fBoxPositionY;
	static int   m_pStatsMenu[2];
	static int   m_allStatsPages;
	static int   m_leftoverStatsPage;
	static int   m_nCurrentStatsPage;
	static int   m_nCurrentModsPage;
	static wchar_t  m_szStatsBuffer[128];
	static void StatsMenu();
	static void ProcessStatsMenu();
	static void ModsMenu();
	static void ProcessModsMenu();
	static void NewLevelSelect();
	static void ProcessNewLevelSelect();
	static void NewSettingMenu();
	static void ProcessNewSettingMenu();
	static void DrawStatText(int id);
	static void DrawModText(int id);


	// hooks 
	static void HookSelectMenuBackground();
	static void HookExecuteMenuProcess();
};