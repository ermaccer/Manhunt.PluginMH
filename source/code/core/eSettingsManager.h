#pragma once

class eSettingsManager {
public:
	static bool bEnableLog;

	
	static bool	bEnableStatsManager;
	static bool bHookSkinLoader;
	static bool bUseEmptyPAKFile;

	static bool bIncreaseMapLimits;
	static bool bForceStaticExecutionCamera;
	
	// anims
	static bool bHookCustomAnimManager;
	static bool bCustomAnimManagerUseGlobalFile;
	static int  iCustomAnimManagerSize;

	// toc
	static bool bHookCustomTableOfContents;
	static int  iCustomTableOfContentsBufferSize;

	// common
	static char* szCustomUserFilesDirectory;

	// adjustements
	static bool bDisableHeartBeat;
	static bool bDisableBreathing;
	static bool bEnableCheatsInBonusLevels;
	static bool bSkipIntroSequence;
	static bool bDisableAutoAim;
	static bool bAllowAllWeaponsExplodeCheat;
	static bool bRestoreConfirmationIcon;
	static bool bHideBSPWarnings;
	static int  iForcePlayerSkin;
	static bool bForceFXMode;
	static bool bEnableFirstPersonMode;


	// keys
	static int  keyToggleDebugMenu;
	static int  keyToggleConsole;
	static int  keyToggleScreenshotMode;
	static int  keyToggleHUD;
	static void Init();
};