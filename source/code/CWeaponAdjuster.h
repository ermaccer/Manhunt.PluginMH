#pragma once
#include <string>

#define IS_SNIPER_RIFLE       1
#define IS_SHOTGUN            2
#define IS_HEALTH_ITEM        4
#define IS_AMMUNITION         8
#define AB_EXPLODE_HEAD_F     16
#define AB_AUTO_HEADSHOT      32
#define ST_IGNORE_EXP_DIST    64

struct CCustomWeapon {
	std::string       sRecordName;
	std::string       sWeaponCollectableName;
	std::string       sGxtEntryName;
	std::string       sFeIconName;
	std::string       sExecutionName;
	int               weaponID;
	int               weaponFlag;

};


namespace CWeaponAdjuster {
	int      ReadFile(const char* file);
	void     GetRecordName(int id, char* dest);
	int      GetWeaponIDFromString(std::string input);
	int      GetExecutionIDFromString(std::string input);
	int      GetWeaponID(int* line);
	wchar_t* GetWeaponText(int id);
	int      GetWeaponIcon(int id, int a2);
	int           __fastcall Executions(int* ptr);
	int           __fastcall CheckExecutionWeaponType(int ptr);
	signed int    __fastcall   HookSniperRifle(int ptr);
	int           __fastcall   HookShotgun(int ptr);
	signed int    __fastcall   HookHealthItem(int ptr);
	void        HookExplodeHeadF();
	void        HookAutoHeadshot();
}