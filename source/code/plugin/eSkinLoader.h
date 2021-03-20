#pragma once
#include <string>
#include <vector>

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
};

void SkinLoader_HookWeapon();