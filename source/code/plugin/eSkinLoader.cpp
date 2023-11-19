#include "eSkinLoader.h"
#include "..\manhunt\core.h"
#include "..\core\eSettingsManager.h"
#include <vector>
#include "..\core\FileFunctions.h"
#include "..\manhunt\EntityManager.h"
#include <filesystem>
#include <rwcore.h>
#include <rwplcore.h>
#include <filesystem>
#include "..\manhunt\Misc.h"
#include "eLog.h"
#include "..\..\IniReader.h"
#include "..\manhunt\Clump.h"
#include "..\manhunt\ClumpDict.h"
#include "..\manhunt\Filenames.h"
#include "eNewFrontend.h"
#include <Windows.h>

std::vector<eSkinEntry> eSkinLoader::vSkins;
bool eSkinLoader::ms_bSkinLoaded;
int eSkinLoader::ms_iLastCharacterID;
int eSkinLoader::ms_iCurrentSkin;
int eSkinLoader::ms_iCurrentSkinAdjust;
int eSkinLoader::ms_iCurrentSkinPos;
RpClump* eSkinLoader::ms_pPlayerClump;


void eSkinLoader::InitHooks()
{
	ms_bSkinLoaded = false;
	ms_pPlayerClump = NULL;
	ms_iLastCharacterID = -1;
	ms_iCurrentSkin = 0;
	//ms_iCurrentSkinPos = 0;
	//ms_iCurrentSkinAdjust = 0;
	
	eSkinEntry skin;
	skin.sName = "[default]";
	skin.sModelFile = "";
	skin.sTxdFile = "";
	skin.sRootName = "";
	skin.iShowWeapons = true;
	skin.iFlag = 1;
	vSkins.push_back(skin);
	
	eSkinLoader::ReadFolder("data\\skins");

	InjectHook(0x43825D, eSkinLoader::Hook, PATCH_CALL);
	InjectHook(0x45FD86, SkinLoader_HookWeapon, PATCH_JUMP);
	Nop(0x5D4750, 10);
	InjectHook(0x5D4750, HookRabbitCheat, PATCH_CALL);
	Nop(0x5D47DA, 10);
	InjectHook(0x5D47DA, HookMonkeyCheat, PATCH_CALL);
	Nop(0x5D48E0, 10);
	InjectHook(0x5D48E0, HookPiggsyCheat, PATCH_CALL);	
}

int eSkinLoader::ReadFolder(const char * folder)
{
	std::filesystem::current_path(getExecutablePath());

	if (!std::filesystem::exists(folder))
	{
		MessageBoxA(0, "Folder does not exist!", folder, 0);
	}

	std::vector<std::string> skinFiles;

	for (const auto & file : std::filesystem::recursive_directory_iterator(folder))
	{
		if (file.path().has_extension())
		{
			if (file.path().extension().string() == ".ini")
			{
				skinFiles.push_back(file.path().string());
			}
		}
	}

	for (unsigned int i = 0; i < skinFiles.size(); i++)
		LoadSkin((char*)skinFiles[i].c_str());

	return 1;
}

int eSkinLoader::Hook(int skinID)
{
	if ( ms_iCurrentSkin == 0 )
		return CallAndReturn<int, 0x437FB0, int>(skinID);
	
	char* result;
	char fullDffPath[260];
	char fullTxdPath[260];
	char txdFile[260];
	char dffFile[260];


	sprintf(txdFile, "%s", vSkins[ms_iCurrentSkin].sTxdFile.c_str());
	sprintf(dffFile, "%s", vSkins[ms_iCurrentSkin].sModelFile.c_str());
	strcpy((char*)0x6A94A0, vSkins[ms_iCurrentSkin].sRootName.c_str());
	*(int*)0x7AE94C = vSkins[ms_iCurrentSkin].iFlag;


	sprintf(fullTxdPath, "%s%s", "./", txdFile);
	sprintf(fullDffPath, "%s%s", "./", dffFile);

	// TODO: update with proper functions?


	result = CallMethodAndReturn<char*, 0x4BDDC0, int, char*>(*(int*)0x736DB8, fullTxdPath);

	CallMethod<0x59B3F0, int*, char*, char*>(&(*(int*)0x69BC90), result, fullDffPath);
	return CallMethodAndReturn<int, 0x4BDDE0, int, char*>(*(int*)0x736DB8, result);
}

void eSkinLoader::HookRabbitCheat()
{
	CEntityManager::ms_playerCharacterID = 1;
	ReloadPlayerDff(0);
	eNewFrontend::UpdateSkinId();
}

void eSkinLoader::HookMonkeyCheat()
{
	CEntityManager::ms_playerCharacterID = 2;
	ReloadPlayerDff(0);
	eNewFrontend::UpdateSkinId();
}

void eSkinLoader::HookPiggsyCheat()
{
	CEntityManager::ms_playerCharacterID = 3;
	ReloadPlayerDff(0);
	eNewFrontend::UpdateSkinId();
}

void eSkinLoader::LoadSkin(char * file)
{

	std::wstring pth = getExecutablePath();
	pth += L"\\";
	std::filesystem::current_path(pth);

	CIniReader ini(file, true);

	eSkinEntry skin;
	skin.sName = ini.ReadString("Skin", "Name", 0);
	skin.sModelFile = ini.ReadString("Skin", "Model", 0);
	skin.sTxdFile = ini.ReadString("Skin", "TXD", 0);
	skin.sRootName = ini.ReadString("Skin", "RootName", 0);
	skin.iShowWeapons = ini.ReadBoolean("Skin", "DisplayWeapons", false);
	skin.iFlag = ini.ReadBoolean("Skin", "DisplayBlood", false);
	vSkins.push_back(skin);
}

void eSkinLoader::SaveFile(int pos, int adj)
{
	std::string pth = CFileNames::GetMyDocumentsDirectory();
	pth += "\\";
	pth += "PluginMH.ini";

	CIniReader pmh((char*)pth.c_str(), true);
	pmh.WriteInteger("Skins","ms_iCurrentSkin",ms_iCurrentSkin);
	//pmh.WriteInteger("Skins", "ms_iCurrentSkinPos", pos);
	//pmh.WriteInteger("Skins", "ms_iCurrentSkinAdjust", adj);
}

void eSkinLoader::ReadFile()
{
	std::string pth = CFileNames::GetMyDocumentsDirectory();
	pth += "\\";
	pth += "PluginMH.ini";

	if (std::filesystem::exists(pth))
	{

		CIniReader pmh((char*)pth.c_str(), true);
		ms_iCurrentSkin = pmh.ReadInteger("Skins", "ms_iCurrentSkin", 0);
		//ms_iCurrentSkinAdjust = pmh.ReadInteger("Skins", "ms_iCurrentSkinAdjust", 0);
		//ms_iCurrentSkinPos = pmh.ReadInteger("Skins", "ms_iCurrentSkinPos", 0);

		if (ms_iCurrentSkin > vSkins.size() - 1)
		{
			ms_iCurrentSkin = 0;
			//ms_iCurrentSkinAdjust = 0;
			//ms_iCurrentSkinPos = 0;
		}
	}

}

void __declspec(naked) SkinLoader_HookWeapon()
{
	static int jmpTrue  = 0x45FD98;
	static int jmpFalse = 0x45FDA0;

	if ( eSkinLoader::ms_iCurrentSkin != 0 )
	{
		if (eSkinLoader::vSkins[eSkinLoader::ms_iCurrentSkin].iShowWeapons)
			_asm jmp jmpTrue
		else
			_asm jmp jmpFalse
	}
	else
	{
		if ( CEntityManager::ms_playerCharacterID != 3 && CEntityManager::ms_playerCharacterID != 1 )
			_asm jmp jmpTrue
		else
			_asm jmp jmpFalse
	}
}

void eSkinLoader::LoadDff(const char* dffpath, const char* txdpath)
{
	if (!ms_bSkinLoaded)
	{
		RwStream *stream;
		RwTexDictionary* tex;
		std::wstring pth = getExecutablePath();
		pth += L"\\";
		std::filesystem::current_path(pth);

		stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, dffpath);

		if (!stream)
		{
			MessageBoxA(0, "Failed to open DFF file", dffpath, MB_ICONERROR);
			exit(0);
			return;
		}
		tex = TexDictLoad(txdpath);

		if (!tex)
		{
			MessageBoxA(0, "Failed to open TXD file", txdpath, MB_ICONERROR);
			exit(0);
			return;
		}

		RwTexDictionarySetCurrent(tex);

		if (RwStreamFindChunk(stream, rwID_CLUMP, NULL, NULL))
			ms_pPlayerClump = RpClumpStreamRead(stream);

		if (!tex)
		{
			MessageBoxA(0, "Could not read Clump from DFF", dffpath, MB_ICONERROR);
			exit(0);
			return;
		}
		if (ms_pPlayerClump)
			ms_bSkinLoaded = true;

		RwStreamClose(stream, NULL);
	}
}

void eSkinLoader::LoadPlayerDff()
{
	if ( ms_iCurrentSkin == 0 )
	{
		char dffpath[MAX_PATH];
		char txdpath[MAX_PATH];
		if ( ms_iLastCharacterID != CEntityManager::ms_playerCharacterID )
		{
			ms_bSkinLoaded = false;
			if ( ms_pPlayerClump )
			{
				RpClumpDestroy(ms_pPlayerClump);
				ms_pPlayerClump = NULL;
			}
			ms_iLastCharacterID = CEntityManager::ms_playerCharacterID;
		}
		
		switch ( CEntityManager::ms_playerCharacterID )
		{
			case 0:
				sprintf(dffpath, "%s%s", CFileNames::ms_pathLevels.str, CFileNames::ms_CharPlayerDFFFilename.str);
				sprintf(txdpath, "%s%s", CFileNames::ms_pathLevels.str, CFileNames::ms_CharPlayerTXDFilename.str);
				break;
		
			case 1:
				sprintf(dffpath, "%s%s", CFileNames::ms_pathLevels.str, CFileNames::ms_CharBunDFFFilename.str);
				sprintf(txdpath, "%s%s", CFileNames::ms_pathLevels.str, CFileNames::ms_CharBunTXDFilename.str);
				break;
		
			case 2:
				sprintf(dffpath, "%s%s", CFileNames::ms_pathLevels.str, CFileNames::ms_CharHelDFFFilename.str);
				sprintf(txdpath, "%s%s", CFileNames::ms_pathLevels.str, CFileNames::ms_CharHelTXDFilename.str);
				break;
			
			case 3:
				sprintf(dffpath, "%s%s", CFileNames::ms_pathLevels.str, CFileNames::ms_CharPigDFFFilename.str);
				sprintf(txdpath, "%s%s", CFileNames::ms_pathLevels.str, CFileNames::ms_CharPigTXDFilename.str);
				break;
		}
		
		LoadDff(dffpath, txdpath);
	}
	else
		LoadDff(vSkins[ms_iCurrentSkin].sModelFile.c_str(), vSkins[ms_iCurrentSkin].sTxdFile.c_str());
}

void eSkinLoader::ReloadPlayerDff(int id)
{
	ms_bSkinLoaded = false;
	if (ms_pPlayerClump)
	{
		RpClumpDestroy(ms_pPlayerClump);
		ms_pPlayerClump = NULL;
	}
	ms_iLastCharacterID = -1;
	ms_iCurrentSkin = id;
	LoadPlayerDff();
}

void eSkinLoader::Shutdown()
{
	if (ms_pPlayerClump)
	{
		RpClumpDestroy(ms_pPlayerClump);
		ms_pPlayerClump = NULL;
		ms_bSkinLoaded = false;
		ms_iLastCharacterID = -1;
	}

}
