#pragma once
#include <string>
#include <vector>
#include <rwcore.h>
#include <rpworld.h>
#include <rwplcore.h>

struct eSkinEntry
{
	int    iID;
	std::string sModelFile;
	std::string sTxdFile;
	std::string sRootName;
	int  iShowWeapons;
	int  iFlag;
};

class eSkinLoader {
public:
	static std::vector<eSkinEntry> vSkins;

	static void InitHooks();
	static int	ReadFile(const char* name);
	static int  Hook(int skinID);
	static int	FindSkin(int skinID);


	static bool ms_bSkinLoaded;
	static RpClump* ms_pPlayerClump;
	static float ms_fPlayerRotation;
	static unsigned int ms_iRotationTimer;

	static void LoadPlayerDff();

};

void SkinLoader_HookWeapon();

