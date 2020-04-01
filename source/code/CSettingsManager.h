#pragma once
#include "..\IniReader.h"


class CSettingsManager {
public:
	void Init();

	// vars
	bool bEnableCheatsOnBonusLevels;
	bool bEnableWeaponSpawner;
	bool bHookWeaponAdjuster;
	bool bEnableFirearmsExecutions;
	bool bEnableConsoleOutput;
	bool bEnableFXMode;
	bool bEnableFPSMode;
	bool bEnableConfirmationIcon;
	bool bEnableExperimentalRIBLoopFix;
	bool bHookPlayerModelLoader;
	bool bDisableLegalScreen;
	bool bEnableRIBStreamFix;

	int  iForcePlayerSkin;
	char iRestrictedHeliumCheatWeaponType;
	int  iDebugMenuKey;
	int  iQuickScreenshotKeyMain;
	int  iQuickScreenshotKeySub;

	char* szCustomWeapon[3];
	int   iCustomWeapon[3];

	char* szSkinsLine;
};

extern CSettingsManager* SettingsMgr;