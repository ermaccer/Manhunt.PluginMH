#pragma once
#include <string>

struct CCustomPlayer
{
	int    iID;
	std::string sModelFile;
	std::string sTxdFile;
	std::string sRootName;
	int  iShowWeapons;
	int  iFlag;
};

namespace CPlayerModelLoader {
	int ReadFile(const char* name);
	int Hook(int skinID);
	int FindSkin(int skinID);
	void HookWeapon();
}