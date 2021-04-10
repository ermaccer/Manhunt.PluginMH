#include "eSettingsManager.h"
#include "..\..\IniReader.h"
#include "..\manhunt\core.h"

bool eSettingsManager::bEnableLog;
bool eSettingsManager::bUseEmptyPAKFile;
bool eSettingsManager::bHookSkinLoader;

bool eSettingsManager::bIncreaseMapLimits;
bool eSettingsManager::bForceStaticExecutionCamera;
bool eSettingsManager::bEnableStatsManager;

bool eSettingsManager::bDisableHeartBeat;
bool eSettingsManager::bDisableBreathing;
bool eSettingsManager::bHookCustomAnimManager;
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
	CIniReader reader("");
	bEnableLog = reader.ReadBoolean("Settings", "bEnableLog", false);

	bEnableStatsManager = reader.ReadBoolean("Settings.Features", "bEnableStatsManager", false);
	bHookSkinLoader = reader.ReadBoolean("Settings.Features", "bHookSkinLoader", false);

	bIncreaseMapLimits = reader.ReadBoolean("Settings", "bIncreaseMapLimits", false);
	bForceStaticExecutionCamera = reader.ReadBoolean("Settings", "bForceStaticExecutionCamera", false);

	bHookCustomAnimManager = reader.ReadBoolean("Settings", "bHookCustomAnimManager", false);
	bCustomAnimManagerUseGlobalFile = reader.ReadBoolean("Settings", "bCustomAnimMangerUseGlobalFile", false);
	iCustomAnimManagerSize = reader.ReadInteger("Limits", "Animations", 1000);


	bHookCustomTableOfContents = reader.ReadBoolean("Settings", "bHookCustomTableOfContents", false);
	iCustomTableOfContentsBufferSize = reader.ReadInteger("Settings", "iCustomTableOfContentsBufferSize", 25);

	szCustomUserFilesDirectory = reader.ReadString("Settings", "szCustomUserFilesDirectory", 0);


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
	iForcePlayerSkin = reader.ReadInteger("Settings.Game", "iForcePlayerSkin", 0);

	keyToggleDebugMenu = reader.ReadInteger("Keys", "keyToggleDevMenu", VK_F1);
	keyToggleConsole = reader.ReadInteger("Keys", "keyToggleConsole", VK_OEM_3);
	keyToggleScreenshotMode = reader.ReadInteger("Keys", "keyToggleScreenshotMode", VK_F3);
	keyToggleHUD = reader.ReadInteger("Keys", "keyToggleHUD", VK_F4);
}
