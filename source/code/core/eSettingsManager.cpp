#include "eSettingsManager.h"
#include "..\..\IniReader.h"
#include "..\manhunt\core.h"

bool eSettingsManager::bEnableLog;
bool eSettingsManager::bHideVersionInfo;
bool eSettingsManager::bHookSkinLoader;
bool eSettingsManager::bCustomLevelsLoader;
bool eSettingsManager::bIncreaseMapLimits;
bool eSettingsManager::bForceStaticExecutionCamera;
bool eSettingsManager::bEnableStatsManager;
bool eSettingsManager::bHookExtraWeapons;
bool eSettingsManager::bHookExtraScriptCommands;
bool eSettingsManager::bEnableWeaponAdjuster;
bool eSettingsManager::bEnableExecutionsWithFirearms;

bool eSettingsManager::bDisableHeartBeat;
bool eSettingsManager::bDisableBreathing;
bool eSettingsManager::bHookCustomAnimManager;
bool eSettingsManager::bRestoreDamageDirectionIndicator;
bool eSettingsManager::bDisableExecutionCamera;
bool eSettingsManager::bUseExclamationMarkForConfirmationIcon;
bool eSettingsManager::bFixExplodingDecappedHeads;
int  eSettingsManager::iCustomAnimManagerSize;

bool eSettingsManager::bCustomAnimManagerUseGlobalFile;
bool eSettingsManager::bHookCustomTableOfContents;
int  eSettingsManager::iCustomTableOfContentsBufferSize;
char* eSettingsManager::szCustomUserFilesDirectory;


bool eSettingsManager::bSkipIntroSequence;
bool eSettingsManager::bEnableCheatsInBonusLevels;
bool eSettingsManager::bDisableAutoAim;
bool eSettingsManager::bRestoreConfirmationIcon;
bool eSettingsManager::bAllowAllWeaponsExplodeCheat;
bool eSettingsManager::bHideBSPWarnings;
bool eSettingsManager::bForceFXMode;
bool eSettingsManager::bEnableFirstPersonMode;
int  eSettingsManager::iForcePlayerSkin;

int  eSettingsManager::keyToggleDebugMenu;
int  eSettingsManager::keyToggleConsole;
int  eSettingsManager::keyToggleHUD;
int  eSettingsManager::keyToggleScreenshotMode;
void eSettingsManager::Init()
{
	bCustomLevelsLoader = false;
	CIniReader reader("");
	bEnableLog = reader.ReadBoolean("Settings", "bEnableLog", false);
	bHideVersionInfo = reader.ReadBoolean("Settings", "bHideVersionInfo", false);
	bEnableStatsManager = reader.ReadBoolean("Settings.Features", "bEnableStatsManager", false);


	bIncreaseMapLimits = reader.ReadBoolean("Settings", "bIncreaseMapLimits", false);
	bForceStaticExecutionCamera = reader.ReadBoolean("Settings", "bForceStaticExecutionCamera", false);

	bHookCustomAnimManager = reader.ReadBoolean("Settings", "bHookCustomAnimManager", false);
	bCustomAnimManagerUseGlobalFile = reader.ReadBoolean("Settings", "bCustomAnimMangerUseGlobalFile", false);
	iCustomAnimManagerSize = reader.ReadInteger("Limits", "Animations", 1000);

	bEnableWeaponAdjuster = reader.ReadBoolean("Settings", "bEnableWeaponAdjuster", false);
	bEnableExecutionsWithFirearms = reader.ReadBoolean("Settings", "bEnableExecutionsWithFirearms", false);

	bHookCustomTableOfContents = reader.ReadBoolean("Settings", "bHookCustomTableOfContents", false);
	iCustomTableOfContentsBufferSize = reader.ReadInteger("Settings", "iCustomTableOfContentsBufferSize", 25);

	szCustomUserFilesDirectory = reader.ReadString("Settings", "szCustomUserFilesDirectory", 0);
	bHookExtraWeapons = reader.ReadBoolean("Settings", "bHookExtraWeapons", false);
	bHookExtraScriptCommands = reader.ReadBoolean("Settings", "bHookExtraScriptCommands", false);


	bDisableBreathing = reader.ReadBoolean("Settings.Game", "bDisableBreathingSound", false);
	bDisableHeartBeat = reader.ReadBoolean("Settings.Game", "bDisableHeartBeatSound", false);
	bSkipIntroSequence = reader.ReadBoolean("Settings.Game", "bSkipIntroSequence", false);
	bEnableCheatsInBonusLevels = reader.ReadBoolean("Settings.Game", "bEnableCheatsInBonusLevels", false);
	bDisableAutoAim = reader.ReadBoolean("Settings.Game", "bDisableAutoAim", false);
	bAllowAllWeaponsExplodeCheat = reader.ReadBoolean("Settings.Game", "bAllowAllWeaponsExplodeCheat", false);
	bRestoreConfirmationIcon = reader.ReadBoolean("Settings.Game", "bRestoreConfirmationIcon", false);
	bHideBSPWarnings = reader.ReadBoolean("Settings.Game", "bHideBSPWarnings", false);
	bForceFXMode = reader.ReadBoolean("Settings.Game", "bForceFXMode", false);
	bEnableFirstPersonMode = reader.ReadBoolean("Settings.Game", "bEnableFirstPersonMode", false);
	bFixExplodingDecappedHeads = reader.ReadBoolean("Settings.Game", "bFixExplodingDecappedHeads", false);
	iForcePlayerSkin = reader.ReadInteger("Settings.Game", "iForcePlayerSkin", 0);

	bRestoreDamageDirectionIndicator = reader.ReadBoolean("Settings.Game", "bRestoreDamageDirectionIndicator", false);
	bDisableExecutionCamera = reader.ReadBoolean("Settings", "bDisableExecutionCamera", false);
	bUseExclamationMarkForConfirmationIcon = reader.ReadBoolean("Settings.Game", "bUseExclamationMarkForConfirmationIcon", false);
	keyToggleDebugMenu = reader.ReadInteger("Keys", "keyToggleDevMenu", VK_F1);
	keyToggleConsole = reader.ReadInteger("Keys", "keyToggleConsole", VK_OEM_3);
	keyToggleScreenshotMode = reader.ReadInteger("Keys", "keyToggleScreenshotMode", VK_F3);
	keyToggleHUD = reader.ReadInteger("Keys", "keyToggleHUD", VK_F4);
}
