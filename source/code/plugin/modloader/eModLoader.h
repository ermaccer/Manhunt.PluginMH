#pragma once
#include <vector>
#include <Windows.h>
#include <string>
#include <unordered_set>
#include "eCustomClumpDict.h"

#include "..\..\manhunt\Misc.h"

#define EXTRATYPEDATA_EXTENSION ".eini"

struct file_entry {
	char path[MAX_PATH];
};

struct eModEntry {
	std::string name;
	std::vector<std::string> files;
	std::vector<file_entry> files_struct;
	std::vector<std::string> files_game;
	
	std::unordered_set<std::string> ignored;
	std::unordered_set<std::string> conficlts;
};

class eModLoader {
public:
	static std::vector<std::string> files;
	static std::vector<std::string> modFolders;
	static std::vector<eModEntry> m_vMods;
	static std::vector<std::string> ignoredFiles;
	static void Init();

	static void InitClumpDicts();
	static void Refresh();
	static void ScanFolderForFiles(const char* folder);
	static char* FindFile(char* input);
	static CFile* LoadFile(char* fileName, int* fileBuffer, int* arg3, CFile** pFile, int* fileSize);
	static bool  CustomFileExists(char* input);
	static bool  IsFileIgnored(std::string& name);

	static CClump* GetModloaderClump(const char* name);

};

