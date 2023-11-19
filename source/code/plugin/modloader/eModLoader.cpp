#include "eModLoader.h"
#include "eCustomClumpDict.h"
#include "..\..\core\FileFunctions.h"
#include "..\..\core\eMain.h"
#include "..\..\manhunt\core.h"
#include "..\..\manhunt\String.h"
#include "..\..\manhunt\EntityManager.h"
#include <filesystem>
#include <Windows.h>
#include "..\eLog.h"
#include "..\..\core\eSettingsManager.h"

std::vector<std::string> dffFiles;

std::vector<std::string> eModLoader::ignoredFiles;
std::vector<std::string> eModLoader::files;
std::vector<std::string> eModLoader::modFolders;
std::vector<eModEntry> eModLoader::m_vMods;

void eModLoader::Init()
{
	InjectHook(0x4D4FE8, LoadFile, PATCH_CALL);
	InjectHook(0x4D501E, LoadFile, PATCH_CALL);
	InjectHook(0x4D507E, LoadFile, PATCH_CALL);
	InjectHook(0x4D5326, LoadFile, PATCH_CALL);
	InjectHook(0x5F6B2D, LoadFile, PATCH_CALL);
	InjectHook(0x5FC88E, LoadFile, PATCH_CALL);
}

void eModLoader::InitClumpDicts()
{
	eCustomClumpDictManager::m_vecClumps.clear();
	for (unsigned int i = 0; i < m_vMods.size(); i++)
	{
		for (unsigned int a = 0; a < m_vMods[i].files.size(); a++)
		{

			std::string file = splitString(m_vMods[i].files[a], true);
			std::string extension = getExtension(m_vMods[i].files[a]);

			for (unsigned int i = 0; i < extension.length(); i++)
				extension[i] = tolower(extension.c_str()[i]);

			if (extension == "dff")
			{
				if (!IsFileIgnored(file))
				{
					CClumpDict* dict = new CClumpDict;
					std::string possibleTXD = m_vMods[i].files[a];
					possibleTXD.replace(m_vMods[i].files[a].length() - 4, m_vMods[i].files[a].length(), ".txd");
					if (!std::filesystem::exists(possibleTXD))
						possibleTXD = "/levels/global/pak/GmodelsPC.txd";

					dict->Initialise(possibleTXD.c_str(), m_vMods[i].files[a].c_str());
					eLog::Message(__FUNCTION__, "Initialising custom clump [%x] %s [%s]", dict, m_vMods[i].files[a].c_str(), possibleTXD.c_str());
					dict->CheckDict();
					eCustomClumpDictManager::m_vecClumps.push_back(dict);
				}

			}
		}

	}
}

void eModLoader::Refresh()
{
	m_vMods.clear();
	files.clear();
	modFolders.clear();
	dffFiles.clear();
	std::filesystem::current_path(getExecutablePath());
	ScanFolderForFiles("modloader");
}

void eModLoader::ScanFolderForFiles(const char* folder)
{
	std::filesystem::current_path(getExecutablePath());

	if (!std::filesystem::exists(folder))
	{
		MessageBoxA(0, "Folder does not exist!", folder, MB_ICONERROR);
		return;
	}

	for (const auto & file : std::filesystem::directory_iterator(folder))
	{
		std::string folder = splitString(file.path().string(), true);

		if (std::filesystem::is_directory(file.path().string()))
		{
			modFolders.push_back(folder);
			eModEntry mod;
			mod.name = folder;
			m_vMods.push_back(mod);
		}

	}
	std::vector<std::string> tmp_files;
	std::vector<std::string> tmp_gfiles;
	std::vector<file_entry>  tmp_sfiles;
	for (unsigned int i = 0; i < m_vMods.size(); i++)
	{
		std::filesystem::current_path(getExecutablePath_str());
		std::filesystem::current_path(folder);
		eLog::Message(__FUNCTION__, "Scanning %s for files...", modFolders[i].c_str());
		for (const auto & file : std::filesystem::recursive_directory_iterator(modFolders[i]))
		{
			if (file.path().has_extension())
			{
				std::string tmp = file.path().string();
				tmp = tmp.substr(modFolders[i].length() + 1, file.path().string().length());

				char buffer[MAX_PATH];
				sprintf(buffer, tmp.c_str());

				for (unsigned int i = 0; i < strlen(buffer); i++)
				{
					buffer[i] = tolower(buffer[i]);
				}

				std::string conv(buffer, strlen(buffer));
				tmp = conv;


				tmp_gfiles.push_back(tmp);

				std::string str = folder;
				str += "\\";
				str += file.path().string();

				file_entry f;
				sprintf(f.path, str.c_str());
				tmp_sfiles.push_back(f);
				tmp_files.push_back(str);
			}
		}
		m_vMods[i].files = tmp_files;
		m_vMods[i].files_game = tmp_gfiles;
		m_vMods[i].files_struct = tmp_sfiles;
		tmp_files.clear();
		tmp_gfiles.clear();
		tmp_sfiles.clear();
	}

	// load ignored

	std::filesystem::current_path(getExecutablePath_str());
	std::filesystem::current_path(folder);

	FILE* pIgnoredList = fopen("modloader.ini","rb");
	if (pIgnoredList)
	{
		char szLine[512];

		while (fgets(szLine, sizeof(szLine), pIgnoredList))
		{
			if (szLine[0] == ';' || szLine[0] == '\n' || szLine[0] == '#')
				continue;

			for (unsigned int i = 0; i < strlen(szLine); i++)
				szLine[i] = tolower(szLine[i]);

			std::string name(szLine, strlen(szLine) - sizeof('\n') - 1);
			ignoredFiles.push_back(name);
			
		}
	}
	else
		eLog::Message(__FUNCTION__, "Ignore list is not present!");
	
	
	// scan for conflicts
	
	for (unsigned int i = 0; i < m_vMods.size(); i++)
	{
		eModEntry &thismod = m_vMods[i];
		
		for (unsigned int j = 0; j < thismod.files.size(); j++  )
		{
			std::string file = splitString(thismod.files[j], true);
			if (IsFileIgnored(file))
				thismod.ignored.insert(thismod.files[j]);
		}
		
		for (unsigned int j = 0; j < m_vMods.size(); j++)
		{
			if ( j == i )
				continue;
			
			eModEntry &randommod = m_vMods[j];
			
			for (unsigned int a = 0; a < randommod.files.size(); a++)
			{
				if (_strcmpi(getExtension(randommod.files_game[a]).c_str(), "txt") == 0)
					continue;
				
				for (unsigned int b = 0; b < thismod.files.size(); b++)
				{
					if (_strcmpi(getExtension(thismod.files_game[b]).c_str(), "txt") == 0)
						continue;
			
					if (strcmp(randommod.files_game[a].c_str(), thismod.files_game[b].c_str()) == 0)
						thismod.conficlts.insert(randommod.files[a]);
				}
			}
		}
	}

}

char * eModLoader::FindFile(char * input)
{
	char* result = input;

	if (input[0] == '.')
	{
		char tmpBuff[260] = {};
		strncpy(tmpBuff, input + 2, strlen(input) - 2);
		input = tmpBuff;
	}

	for (unsigned int i = 0; i < strlen(input); i++)
	{
		if (input[i] == '/')
			input[i] = '\\';
	}

	for (unsigned int i = 0; i < strlen(input); i++)
		input[i] = tolower(input[i]);

	// check file
	std::string str(input, strlen(input));
	std::string file = splitString(str, true);
	
	if (IsFileIgnored(file))
		return result;

	for (unsigned int i = 0; i < m_vMods.size(); i++)
	{
		for (unsigned int a = 0; a < m_vMods[i].files.size(); a++)
		{

			if (strcmp(m_vMods[i].files_game[a].c_str(), input) == 0)
			{
				result = (char*)m_vMods[i].files[a].c_str();
			}
		}
	}
	return result;
}

CFile* eModLoader::LoadFile(char * fileName, int * fileBuffer, int * arg3, CFile ** pFile, int * fileSize)
{
	if (CustomFileExists(fileName))
		fileName = FindFile(fileName);
	CFile* result = CallAndReturn<CFile*, 0x4D5090, char*, int*, int*, CFile**, int*>(fileName, fileBuffer, arg3, pFile, fileSize);
	return result;
}

bool eModLoader::CustomFileExists(char * input)
{
	char result[256] = {};
	sprintf(result, input);


	if (result[0] == '.')
	{
		char tmpBuff[260] = {};
		strncpy(tmpBuff, result + 2, strlen(result) - 2);
		sprintf(result, tmpBuff);
	}

	for (unsigned int i = 0; i < strlen(result); i++)
	{
		if (result[i] == '/')
			result[i] = '\\';
	}

	for (unsigned int i = 0; i < strlen(result); i++)
		result[i] = tolower(result[i]);

	// check file
	std::string str(result, strlen(result));
	std::string file = splitString(str, true);

	if (IsFileIgnored(file))
		return false;

	for (unsigned int i = 0; i < m_vMods.size(); i++)
	{
		for (unsigned int a = 0; a < m_vMods[i].files.size(); a++)
		{
			if (strcmp(m_vMods[i].files_game[a].c_str(), result) == 0)
			{
				return true;
			}
		}
	}
	return false;
}


bool eModLoader::IsFileIgnored(std::string & name)
{
	bool result = false;
	for (unsigned int i = 0; i < ignoredFiles.size(); i++)
	{
		if (_strcmpi(name.c_str(), ignoredFiles[i].c_str()) == 0)
		{
			result = true;
			break;
		}
	}
	return result;
}

CClump* eModLoader::GetModloaderClump(const char* name)
{
	CClump* clump = nullptr;

	for (unsigned int i = 0; i < eCustomClumpDictManager::m_vecClumps.size(); i++)
	{
		clump = eCustomClumpDictManager::m_vecClumps[i]->FindClump(name);
		if (clump)
		{
			eLog::Message(__FUNCTION__, "Loaded model %s!", name);
			break;
		}
	}
	return clump;
}
