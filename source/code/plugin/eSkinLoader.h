#pragma once
#include <string>
#include <vector>
#include <rwcore.h>
#include <rpworld.h>
#include <rwplcore.h>

struct eSkinEntry
{
	std::string sName;
	std::string sModelFile;
	std::string sTxdFile;
	std::string sRootName;
	bool  iShowWeapons;
	int  iFlag;
};

class eSkinLoader {
public:
	static std::vector<eSkinEntry> vSkins;
	static bool ms_bSkinLoaded;
	static RpClump* ms_pPlayerClump;
	static float ms_fPlayerRotation;
	static int ms_iLastCharacterID;
	static int ms_iCurrentSkin;
	static int ms_iCurrentSkinAdjust;
	static int ms_iCurrentSkinPos;

	static void InitHooks();
	static int	ReadFolder(const char* folder);
	static int  Hook(int skinID);
	static void HookRabbitCheat();
	static void HookMonkeyCheat();
	static void HookPiggsyCheat();

	static void LoadSkin(char* file);

	static void SaveFile(int pos, int adj);
	static void ReadFile();



	static void LoadDff(const char* dffpath, const char* txdpath);
	static void LoadPlayerDff();
	static void ReloadPlayerDff(int id);

	static void Shutdown();

};

void SkinLoader_HookWeapon();

