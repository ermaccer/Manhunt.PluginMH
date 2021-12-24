#include "eLevelsLoader.h"
#include "..\manhunt\core.h"
#include <iostream>

int eLevelsLoader::m_nLevels;
std::unique_ptr<level_name[]> eLevelsLoader::m_levelNames;
std::unique_ptr<level_map[]> eLevelsLoader::m_levelMaps;
void eLevelsLoader::GetLevels()
{
	FILE* pFile = fopen("initscripts/levels/levels.txt", "rb");

	if (pFile)
	{
		char szLine[512] = {};

		while (fgets(szLine, sizeof(szLine), pFile))
		{
			char levels[32] = {};
			char lvlName[64] = {};
			if (sscanf(szLine, "%s",&levels) == 1)
			{
				if (strcmp(levels, "LEVEL") == 0)
				{
					level_map map = {};
					sscanf(szLine, "%s %s %f %f %f %f %f %f %f %f", &levels, &lvlName, &map.coords[0], &map.coords[1], &map.coords[2], &map.coords[3], &map.coords[4],
						&map.coords[5], &map.coords[6], &map.coords[7]);
					level_name lvl;
					sprintf(lvl.name, lvlName);
					m_levelNames[m_nLevels] = lvl;
					m_levelMaps[m_nLevels] = map;
					m_nLevels++;
				}

			}
		}
	}
}

void eLevelsLoader::InitHooks()
{
	InjectHook(0x4D789A, GetLevels, PATCH_CALL);
	Init();
	Patch<char>(0x5FDF40 + 2, m_nLevels);
	Patch<char>(0x4D837E + 2, m_nLevels);
	Patch<char>(0x4D8394 + 2, m_nLevels);


	Patch<int>(0x403361, (int)&m_levelNames[0]);
	Patch<int>(0x4033BF, (int)&m_levelNames[0]);
	Patch<int>(0x4381D6, (int)&m_levelNames[0]);
	Patch<int>(0x438540, (int)&m_levelNames[0]);
	Patch<int>(0x4393F8, (int)&m_levelNames[0]);
	Patch<int>(0x439581, (int)&m_levelNames[0]);
	Patch<int>(0x439B7F, (int)&m_levelNames[0]);
	Patch<int>(0x471E77, (int)&m_levelNames[0]);
	Patch<int>(0x471EEF, (int)&m_levelNames[0]);
	Patch<int>(0x476D61, (int)&m_levelNames[0]);
	Patch<int>(0x47EFF0, (int)&m_levelNames[0]);
	Patch<int>(0x47F077, (int)&m_levelNames[0]);
	Patch<int>(0x47F0AB, (int)&m_levelNames[0]);
	Patch<int>(0x493330, (int)&m_levelNames[0]);
	Patch<int>(0x493357, (int)&m_levelNames[0]);
	Patch<int>(0x49649C, (int)&m_levelNames[0]);
	Patch<int>(0x4C33AD, (int)&m_levelNames[0]);
	Patch<int>(0x4C365E, (int)&m_levelNames[0]);
	Patch<int>(0x4D6315, (int)&m_levelNames[0]);
	Patch<int>(0x5EEAF5, (int)&m_levelNames[0]);
	Patch<int>(0x5FDF1A, (int)&m_levelNames[0]);
	Patch<int>(0x5FDF1F, (int)&m_levelNames[0]);


	Patch<int>(0x4D835D, (int)&m_levelNames[0]);
	Patch<int>(0x4D83A6, (int)&m_levelNames[0]);
	Patch<int>(0x5FDF0D, (int)&m_levelNames[0]);
	Patch<int>(0x5FDF12, (int)&m_levelNames[0]);
	Patch<int>(0x5FDF50, (int)&m_levelNames[0]);

	Patch<int>(0x5E22B4, (int)&m_levelMaps[0]);
	Patch<int>(0x5E234A, (int)&m_levelMaps[0]);
	Patch<int>(0x5FDF55, (int)&m_levelMaps[0]);
	Patch<int>(0x5FE5B2, (int)&m_levelMaps[0]);
	Patch<int>(0x5FE5A0, (int)&m_levelMaps[0]);

}

void eLevelsLoader::Init()
{
	m_nLevels = 0;
	m_levelNames = std::make_unique<level_name[]>(TOTAL_LEVELS);
	m_levelMaps = std::make_unique<level_map[]>(TOTAL_LEVELS);
	GetLevels();
	printf("Levels found: %d\n", m_nLevels);
}
