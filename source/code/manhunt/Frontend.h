#pragma once
#include "Vector.h"
#include <rwcore.h>
#include <rwplcore.h>

enum eFrontendMainMenuButtons {
	MB_PLAY,
	MB_SELSCE,
	MB_LOADG,
	MB_SETT,
	MB_BONFEA,
	// custom menus
	MB_STATS,
	MB_MODIFICATIONS,
	MB_SKINS,
	// end custom menus
	MB_QUITPRG,
	MB_TOTAL_MENUS
};


enum eFrontendSettingsButtons {
	MB_DIFF,
	MB_CONTR,
	MB_LANGUA,
	MB_AUDIO,
	MB_VIDEO,
	MB_BRIGHTN,
	MB_DEFSET
};


enum eMenuTypes {
	MENU_EMPTY,
	MENU_CHANGE_LANGUAGE,
	MENU_EMPTY_2,
	MENU_DIFFICULTY_SELECT,
	MENU_START_LOAD_GAME,
	MENU_LOAD_GAME,
	MENU_SAVE_GAME,
	MENU_FRONTEND,
	MENU_PAUSE,
	MENU_LEVEL_SELECT,
	MENU_SETTINGS,
	MENU_AUDIO_SETTINGS,
	MENU_HEADSET_SETTINGS, // most likely
	MENU_VIDEO_SETTINGS,
	MENU_BONUS_FEATURES,
	MENU_BONUS_PREVIEW,
	MENU_GAME_COMPLETED,
	MENU_GAMMA_SETTINGS,
	MENU_CONTROL_SETTINGS,
	MENU_RESTORE_DEFAULTS,
	MENU_19,
	MENU_CREDITS,
	// pc exclusive
	MENU_REMAP_CONTROLS,
	MENU_QUIT,
};

enum eFontType {
	FONT_TYPE_DEBUG,
	FONT_TYPE_DEFAULT,
	FONT_FRONTEND,
	FONT_TYPE_LOADING
};


struct CRGBA {
	int r, g, b, a;
};



struct CRGB3 {
	int r, g, b;
};

struct CStoredHalo {
	CVector position;
	float scale;
	int r;
	int g;
	int b;
	float radius;
};




class CFrontend {
public:
	static int& ms_devMenu;
	static int& ms_draw2d;
	static int& ms_misc;
	static int& m_gameIsRunning;
	static int& ms_cnt;
	// menu stuff
	static bool&  m_bNewGame;
	static int&   ms_currentMenu;
	static int&   ms_lastMenu;
	static int&   ms_menuButton;
	static float& ms_fTextXScale;
	static float& ms_fTextYScale;
	static float& ms_fMenuPositionX;
	static float& ms_fMenuPositionY;
	static float& ms_fTextAdjust;
	static int&   ms_mouseHoverButton;
	static int&   NumStoredHalos;

	static CRGBA& ColorSet1;
	static CRGBA& ColorSet2;
	static CRGBA& ColorSet3;
	static CRGBA& ColorSet4;


	static void SetLevel(int level);
	static void ForceLevel(int level);


	static void SetCurrentMenu(int menu);
	static void DrawMenuCameraCounter(wchar_t* text);
	static void AddOption(wchar_t* text, float x, float y, float textScaleX, float textScaleY, int menuID);
	static int  GetHoveredItem();
	static void SetDrawRGBA(int r, int g, int b, int a);
	static void Print8(const char* text, float x, float y, float sizex, float sizey, float unk, eFontType font);
	static void SetMenuBackground(char* file);
	static void PrintInfo(wchar_t* button1, wchar_t* button2, wchar_t* button3, wchar_t* button4);
	static void PrintDebugInfo(int lineID, char* format, ...);
	static int GetTextureFromTXD(int txd, const char* texture);

	static int GetLastPlayedLevel();
	static void ForceAndPlayLevel(int levelID, int unk);

	static float CalculateTextLen(wchar_t* text, float charScale, int byteLen);

	static void DrawDisc2D(CVector* pos, float scale, int red, int green, int blue, float a6);
	static void DrawDisc3D(CVector* pos, float scale, int red, int green, int blue, float a6);

	static void Set_Difficulty(int difficulty);

	static RwCamera* GetFrontendCamera();
};