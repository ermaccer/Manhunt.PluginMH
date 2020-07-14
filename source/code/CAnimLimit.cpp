#include "CAnimLimit.h"
#include "..\MemoryMgr.h"
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace Memory::VP;

std::vector<anim_entry> AnimationNames;

void CAnimLimit::Init()
{
	char messageBuffer[256];
	FILE* pFile = fopen("data\\animations.dat","rb");

	if (!pFile)
		MessageBoxA(0, "Failed to open animations.dat!", 0, 0);

	if (pFile)
	{
		char szLine[1024];
		int i = 0;
		while (fgets(szLine, sizeof(szLine), pFile))
		{
			if (szLine[0] == ';' || szLine[0] == '\n')
				continue;

			char tempStr[256];
			if (sscanf(szLine, "%s", &tempStr) == 1)
			{
				if (strlen(tempStr) > 48)
					MessageBoxA(0, "ERROR: String too large!\n 48 characters max!", tempStr, 0);
				else
				{
					anim_entry name;
					sprintf(name.name, "%s", tempStr);

					AnimationNames.push_back(name);
				}

			}
		}
		MessageBoxA(0, messageBuffer, 0, 0);
	}
}

void CAnimLimit::MakePatches()
{
	std::unique_ptr<int[]> animations = std::make_unique<int[]>(1000);

	Patch<int>(0x496416 + 1, 999);
	Patch<int>(0x496420 + 3, (int)&animations[0]);
	Patch<int>(0x4965B1 + 3, (int)&animations[0]);
	Patch<int>(0x496768 + 3, (int)&animations[0]);
	Patch<int>(0x496B17 + 3, (int)&animations[0]);
	/*
	Patch<int>(0x41D92B + 2, (int)&AnimationNames[0]);
	Patch<int>(0x41E92A + 1, (int)&AnimationNames[0]);
	Patch<int>(0x41EBC7 + 2, (int)&AnimationNames[0]);
	Patch<int>(0x41EBD3 + 1, (int)&AnimationNames[0]);
	Patch<int>(0x421137 + 2, (int)&AnimationNames[0]);
	Patch<int>(0x421144 + 1, (int)&AnimationNames[0]);
	Patch<int>(0x4211B5 + 2, (int)&AnimationNames[0]);
	Patch<int>(0x4211C2 + 1, (int)&AnimationNames[0]);
	Patch<int>(0x421BF5 + 2, (int)&AnimationNames[0]);
	Patch<int>(0x421C02 + 1, (int)&AnimationNames[0]);
	Patch<int>(0x422614 + 2, (int)&AnimationNames[0]);
	Patch<int>(0x422621 + 1, (int)&AnimationNames[0]);
	Patch<int>(0x422925 + 2, (int)&AnimationNames[0]);
	Patch<int>(0x422932 + 1, (int)&AnimationNames[0]);
	Patch<int>(0x422D54 + 2, (int)&AnimationNames[0]);
	Patch<int>(0x422D61 + 1, (int)&AnimationNames[0]);
	Patch<int>(0x422FC4 + 2, (int)&AnimationNames[0]);
	Patch<int>(0x422FD1 + 1, (int)&AnimationNames[0]);
	*/
}
