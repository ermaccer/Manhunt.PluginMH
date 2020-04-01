#include "CSettingsManager.h"
#include "ManhuntSDK.h"

CSettingsManager* SettingsMgr = new CSettingsManager();

void CSettingsManager::Init()
{
	CIniReader reader("");
	bEnableCheatsOnBonusLevels = reader.ReadBoolean("Settings", "bEnableCheatsOnBonusLevels", false);
	bEnableWeaponSpawner = reader.ReadBoolean("Settings", "bEnableWeaponSpawner", false);
	bHookWeaponAdjuster = reader.ReadBoolean("Settings", "bHookWeaponAdjuster", false);
	bEnableFirearmsExecutions = reader.ReadBoolean("Settings", "bEnableFirearmsExecutions", false);
	bEnableConsoleOutput = reader.ReadBoolean("Settings", "bEnableConsoleOutput", false);
	bEnableFPSMode = reader.ReadBoolean("Settings", "bEnableFPSMode", false);
	bEnableFXMode = reader.ReadBoolean("Settings","bEnableFXMode", false);
	bEnableConfirmationIcon = reader.ReadBoolean("Patches", "bEnableConfirmationIcon", false);
	bEnableExperimentalRIBLoopFix = reader.ReadBoolean("Patches", "bEnableExperimentalRIBLoopFix", false);
	bHookPlayerModelLoader = reader.ReadBoolean("Settings", "bHookPlayerModelLoader", false);
	bDisableLegalScreen = reader.ReadBoolean("Patches", "bDisableLegalScreen", true);
	bEnableRIBStreamFix = reader.ReadBoolean("Patches", "bEnableRIBStreamFix", true);
	iForcePlayerSkin = reader.ReadInteger("Settings", "iForcePlayerSkin", 0);
	iRestrictedHeliumCheatWeaponType = reader.ReadInteger("Settings", "iRestrictedHeliumCheatWeaponType", 0);
	iDebugMenuKey = reader.ReadInteger("Settings", "iDebugMenuKey", 0);
	iQuickScreenshotKeyMain = reader.ReadInteger("Settings", "iQuickScreenshotKeyMain", 0);
	iQuickScreenshotKeySub = reader.ReadInteger("Settings", "iQuickScreenshotKeySub", 0);
	
	// custom weaps
	szCustomWeapon[0] = reader.ReadString("Spawner", "szCustomWeapon1Record",0);
	szCustomWeapon[1] = reader.ReadString("Spawner", "szCustomWeapon2Record",0);
	szCustomWeapon[2] = reader.ReadString("Spawner", "szCustomWeapon3Record",0);

	iCustomWeapon[0] = reader.ReadInteger("Spawner", "iCustomWeapon1Record", -1);
	iCustomWeapon[1] = reader.ReadInteger("Spawner", "iCustomWeapon2Record", -1);
	iCustomWeapon[2] = reader.ReadInteger("Spawner", "iCustomWeapon3Record", -1);


	szSkinsLine = reader.ReadString("Settings", "szDisplayWeaponsOn", "0 1");
}
