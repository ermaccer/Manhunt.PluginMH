#include "CPlayerModelLoader.h"
#include <iostream>
#include <vector>
#include "ManhuntSDK.h"

std::vector<CCustomPlayer> vSkins;

int CPlayerModelLoader::ReadFile(const char * name)
{
	FILE* pFile = fopen(name, "rb");
	if (!pFile)
	{
		printf("CPlayerModelLoader::ReadFile() | ERROR: Could not open %s!\n", name);
		return 0;
	}
	if (pFile)
	{
		printf("CPlayerModelLoader::ReadFile() | Reading %s\n", name);
		char line[1536];
		while (fgets(line, sizeof(line), pFile))
		{
			// check if comment
			if (line[0] == ';' || line[0] == '#' || line[0] == '\n')
				continue;

			int id = 0;
			if (sscanf(line, "%d", &id) == 1)
			{
				char t_dffname[128];
				char t_txdename[128];
				char t_rootname[128];
				int  bDisplayWeapons;
				int  flag;
				 
				sscanf(line, "%d %s %s %s %d %d", &id, &t_txdename, &t_dffname, &t_rootname, &bDisplayWeapons, &flag);

				// convert to strings
				std::string strDff(t_dffname, strlen(t_dffname));
				std::string strTxd(t_txdename, strlen(t_txdename));
				std::string strRoot(t_rootname, strlen(t_rootname));

				if (strRoot.length() > 15)
				{
					printf("ERROR: Skin %d root name too long! (15 max)\n", id);
					return 0;
				}

				// create skin
				CCustomPlayer skin;
				skin.iID = id;
				skin.iShowWeapons = bDisplayWeapons;
				skin.sModelFile = strDff;
				skin.sRootName = strRoot;
				skin.sTxdFile = strTxd;
				skin.iFlag = flag;
				vSkins.push_back(skin);
			}

		}
		printf("CPlayerModelLoader::ReadFile() | Found %d entities!\n", vSkins.size());
		fclose(pFile);
	}
	return 1;
}
int CPlayerModelLoader::Hook(int skinID)
{
	char* result;
	char fullDffPath[260];
	char fullTxdPath[260];
	char txdFile[260];
	char dffFile[260];


	sprintf(txdFile,"%s", vSkins[FindSkin(skinID)].sTxdFile.c_str());
	sprintf(dffFile,"%s", vSkins[FindSkin(skinID)].sModelFile.c_str());
	strcpy((char*)0x6A94A0, vSkins[FindSkin(skinID)].sRootName.c_str()); // root name
	*(int*)0x7AE94C = 0;


	sprintf(fullTxdPath, "%s%s", "./levels", txdFile);
	sprintf(fullDffPath, "%s%s", "./levels", dffFile);

	//printf("CPlayerModelLoader::Hook() | Loading skin %d\n", skinID);

	result = CallMethodAndReturn<char*, 0x4BDDC0, int, char*>(*(int*)0x736DB8, fullTxdPath);
	CallMethod<0x59B3F0, int*, char*, char*>(&(*(int*)0x69BC90), result, fullDffPath);
	return CallMethodAndReturn<int, 0x4BDDE0, int, char*>(*(int*)0x736DB8, result);
	
}

int CPlayerModelLoader::FindSkin(int skinID)
{
	int iFind = 0;

	for (int i = 0; i < vSkins.size(); i++)
	{
		if (vSkins[i].iID == skinID)
		{
			iFind = i;
			break;
		}
	}
	return iFind;
}

void __declspec(naked) CPlayerModelLoader::HookWeapon()
{
	static int tecx;
	static int jmpTrue = 0x45FD98;
	static int jmpFalse = 0x45FDA0;
	_asm {
		mov ecx, ds:0x6A94C0
	    mov tecx,ecx
	}
	if (vSkins[FindSkin(tecx)].iShowWeapons == 1)
	{
		_asm {
			jmp	jmpTrue
		}
	}
	else
		_asm {
		jmp jmpFalse
	}
}
