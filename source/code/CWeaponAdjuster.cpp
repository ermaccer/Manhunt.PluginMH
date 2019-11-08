#include "CWeaponAdjuster.h"
#include "ManhuntSDK.h"
#include "..\MemoryMgr.h"
#include <vector>

using namespace ManhuntFunctions;
std::vector<CCustomWeapon> vWeapons;

int iExplodeWeapon_esp;
int iExplodeWeapon_id;
int iExplodeWeapon_true = 0x49D79A;
int iExplodeWeapon_false = 0x49D940;
int iExplodeWeapon_iFind;

int iAutoHeadL_esp;
int iAutoHeadL_id;
int iAutoHeadL_true = 0x49D976;
int iAutoHeadL_false = 0x49DE35;
int iAutoHeadL_iFind;

float ignoreDist = 100000.0f;

int CWeaponAdjuster::ReadFile(const char * file)
{
	FILE* pFile = fopen(file, "rb");
	if (!pFile)
	{
		printf("CWeaponAdjuster::ReadFile() | ERROR: Could not open %s!\n", file);
		return 0;
	}
	if (pFile)
	{
		printf("CWeaponAdjuster::ReadFile() | Reading %s\n", file);
		char line[1536];
		while (fgets(line, sizeof(line), pFile))
		{
			// check if comment
			if (line[0] == ';' || line[0] == '#' || line[0] == '\n')
				continue;

			int id = 0;
			if (sscanf(line, "%d", &id) == 1)
			{
				char t_recordname[128];
				char t_collectablename[128];
				char t_gxtname[128];
				char t_iconname[128];
				char t_executionName[128];
				int  flags;

				sscanf(line, "%d %s %s %s %s %d %s", &id, &t_recordname, &t_collectablename, &t_gxtname, &t_iconname, &flags, &t_executionName);

				// convert to strings
				std::string strRecordName(t_recordname, strlen(t_recordname));
				std::string strCollectableName(t_collectablename, strlen(t_collectablename));
				std::string strGXTName(t_gxtname, strlen(t_gxtname));
				std::string strIconName(t_iconname, strlen(t_iconname));
				std::string strExecName(t_executionName, strlen(t_executionName));
				// create weapon
				CCustomWeapon weap;

				weap.weaponID = id;
				weap.weaponFlag = flags;
				weap.sGxtEntryName = strGXTName;
				weap.sRecordName = strRecordName;
				weap.sWeaponCollectableName = strCollectableName;
				weap.sFeIconName = strIconName;
				weap.sExecutionName = strExecName;

				vWeapons.push_back(weap);
			}

		}
		printf("CWeaponAdjuster::ReadFile() | Found %d entities!\n", vWeapons.size());
		fclose(pFile);
	}
	return 1;
}

void CWeaponAdjuster::GetRecordName(int id, char * dest)
{
	int iFind = 0;
	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].weaponID == id)
		{
			iFind = i;
			break;
		}
	}
	if (iFind == 0)
	{
		printf("CWeaponAdjuster::GetRecordName() |  %d does not exist! Using fist instead!\n", id);
		sprintf(dest, "fists");
	}
	else
		sprintf(dest, vWeapons[iFind].sRecordName.c_str());
}

int CWeaponAdjuster::GetWeaponIDFromString(std::string input)
{
	int iFind = 0;
	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].sWeaponCollectableName == input)
		{
			iFind = i;
			break;
		}
	}
	return vWeapons[iFind].weaponID;
}

int CWeaponAdjuster::GetExecutionIDFromString(std::string input)
{
	int result = 15;

	if (input == "BAG")             result = EXEC_BAG;
	else if (input == "KNIFE")      result = EXEC_KNIFE;
	else if (input == "CROWBAR")    result = EXEC_CROWBAR;
	else if (input == "BAT")        result = EXEC_BAT;
	else if (input == "SICKLE")     result = EXEC_SICKLE;
	else if (input == "WIRE")       result = EXEC_WIRE;
	else if (input == "CLEAVER")    result = EXEC_CLEAVER;
	else if (input == "AXE")        result = EXEC_AXE;
	else if (input == "NIGHTSTICK") result = EXEC_NIGHTSTICK;
	else if (input == "HAMMER")     result = EXEC_HAMMER;
	else if (input == "CHAINSAW")   result = EXEC_CHAINSAW;
	else if (input == "PIGSHARD")   result = EXEC_PIGSHARD;
	else if (input == "PIGWIRE")    result = EXEC_PIGWIRE;
	else if (input == "PIGSPIK")    result = EXEC_PIGSPIK;
	else if (input == "RAMIREZ")    result = EXEC_RAMIREZ;
	else if (input == "DEFAULT")    result = EXEC_DEFAULT;
	else {
		result = 15;
	}
	return result;
}

int CWeaponAdjuster::GetWeaponID(int * line)
{
	std::string temp = (char*)*line;

	return 	GetWeaponIDFromString(temp);
}

wchar_t * CWeaponAdjuster::GetWeaponText(int id)
{
	int iFind = 0;
	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].weaponID == id)
		{
			iFind = i;
			break;
		}
	}
	wchar_t* result;


	if (vWeapons[iFind].sGxtEntryName.length() > 7)
	{
		printf("CWeaponAdjuster::GetWeaponText() | %s gxt entry name is too long!\n", vWeapons[iFind].sRecordName.c_str());
		result = L"(this item uses too long text entry)";
	}
	else
		//result = ((wchar_t*(__thiscall*)(int, const char*))0x4937E0)(0x725A38, vWeapons[iFind].sGxtEntryName.c_str());
		result = GetText(0x725A38, vWeapons[iFind].sGxtEntryName.c_str());
	return result;
}

int CWeaponAdjuster::GetWeaponIcon(int id, int a2)
{
	wchar_t *text;
	if (a2)
	{
		// display weapon text
		*(int*)0x7C9B78 = 1;
		*(int*)0x7C9C80 = 0;
		// fill the buffer
		text = GetWeaponText(id);
		((void(__cdecl*)(int, wchar_t*))0x5FC150)(0x7C9B7C, text);
	}
	int iFind = 0;
	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].weaponID == id)
		{
			iFind = i;
			break;
		}
	}
	int weaponIcon = LoadTexture(*(int*)0x7D366C, vWeapons[iFind].sFeIconName.c_str());
	if (!weaponIcon)
	{
		printf("CWeaponAdjuster::GetWeaponIcon() | Icon for %s does not exist! (%s)\n", vWeapons[iFind].sRecordName.c_str(), vWeapons[iFind].sFeIconName.c_str());
		weaponIcon = LoadTexture(*(int*)0x7D366C, "na");
	}
	return  weaponIcon;
}

int __fastcall CWeaponAdjuster::Executions(int * ptr)
{
	int execution;

	if (*(int*)(ptr + 80) && (*(int*)(*(int*)(ptr + 80) + 2228)) != 0 && ((int(__thiscall*)(int*))0x4B2F40)(ptr))
	{
		execution = 14;
	}
	else
	{
		int weaponID = (*(int*)(*(int*)(ptr + 31) + 356));
		int iFind = 0;
		for (int i = 0; i < vWeapons.size(); i++)
		{
			if (vWeapons[i].weaponID == weaponID)
			{
				iFind = i;
				break;
			}
		}

		execution = GetExecutionIDFromString(vWeapons[iFind].sExecutionName);
	}

	return execution;
}

int __fastcall CWeaponAdjuster::CheckExecutionWeaponType(int ptr)
{
	int  v1;
	int  v2;
	int  v3;

	int result = 0;

	v1 = *(int*)(ptr + 340);

	if (v1 == -1) v2 = 0;
	else
		v2 = (*(int*)(*(int *)(*(int *)(ptr + 336) + 8) + 4 * v1));
	result = 0;
	if (v2)
	{

		if ((*(int*)(*(int*)(v2 + 124) + 4) & 0x3001) == 12289)
		{

			v3 = *(int*)(v2 + 428);

			// added 3 - if firearm check
			if ((*(int*)(*(int*)(v3 + 4) + 4)) == 0 || (*(int*)(*(int*)(v3 + 4) + 4)) == 1 || (*(int*)(*(int*)(v3 + 4) + 4)) == 3)
				result = 1;
		}



	}
	return result;
}


signed int __fastcall CWeaponAdjuster::HookSniperRifle(int ptr)
{
	signed int result;

	int weaponID = (*(int*)(*(int*)(ptr + 124) + 356));

	int iFind = 0;
	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].weaponID == weaponID)
		{
			iFind = i;
			break;
		}
	}

	if (vWeapons[iFind].weaponFlag & IS_SNIPER_RIFLE)
		result = 1;
	else
		result = 0;

	return result;
}

int __fastcall CWeaponAdjuster::HookShotgun(int ptr)
{
	int result;

	int weaponID = *(int*)(*(int*)(ptr + 124) + 356);
	int iFind = 0;
	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].weaponID == weaponID)
		{
			iFind = i;
			break;
		}
	}

	if (vWeapons[iFind].weaponFlag & IS_SHOTGUN)
		result = 1;
	else
		result = 0;

	return result;
}

signed int __fastcall CWeaponAdjuster::HookHealthItem(int ptr)
{
	signed int result = 0;
	if (*(int*)0x755E50) result = 0;


	int weaponID = *(int*)(*(int*)(ptr + 124) + 356);
	int iFind = 0;
	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].weaponID == weaponID)
		{
			iFind = i;
			break;
		}
	}

	if (vWeapons[iFind].weaponFlag & IS_HEALTH_ITEM)
		result = 1;

	return result;
}

void   __declspec(naked)  CWeaponAdjuster::HookExplodeHeadF()
{
	_asm {
		mov iExplodeWeapon_esp, esp
			pushad
	}
	iExplodeWeapon_id = (*(int*)(iExplodeWeapon_esp + 216));


	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].weaponID == iExplodeWeapon_id)
		{
			iExplodeWeapon_iFind = i;
			break;
		}
	}


	if (vWeapons[iExplodeWeapon_iFind].weaponFlag & AB_EXPLODE_HEAD_F)
	{
		if (vWeapons[iExplodeWeapon_iFind].weaponFlag & ST_IGNORE_EXP_DIST)
			Memory::VP::Patch<float>(0x49F9C9, ignoreDist);
		_asm
		{
			popad
			jmp iExplodeWeapon_true
		}
	}
	_asm {
		popad
			jmp iExplodeWeapon_false
	}
}

void   __declspec(naked)  CWeaponAdjuster::HookAutoHeadshot()
{
	_asm {
		mov iAutoHeadL_esp, esp
			pushad
	}
	iAutoHeadL_id = (*(int*)(iAutoHeadL_esp + 216));


	for (int i = 0; i < vWeapons.size(); i++)
	{
		if (vWeapons[i].weaponID == iAutoHeadL_id)
		{
			iAutoHeadL_iFind = i;
			break;
		}
	}


	if (vWeapons[iAutoHeadL_iFind].weaponFlag & AB_AUTO_HEADSHOT)
	{
		_asm
		{
			popad
			jmp iAutoHeadL_true
		}
	}
	_asm {
		popad
			jmp iAutoHeadL_false
	}
}
