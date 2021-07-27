#include "eCustomTableOfContents.h"
#include "..\core\eSettingsManager.h"
#include "..\manhunt\Misc.h"
#include "..\manhunt\core.h"
#include <filesystem>

int& iFileStreamSize = *(int*)0x7392C8;
char& byte_7392CC = *(char*)0x7392CC;
char& unk_67D000 = *(char*)0x67D000;

void eCustomTableOfContents::InitHooks()
{
	//InjectHook(0x4D5090, LoadFile, PATCH_JUMP);
	InjectHook(0x4D61B0, GetTOCFileSize, PATCH_JUMP);
}

int eCustomTableOfContents::GetTOCFileSize(char * name)
{
	//printf("File %s\n", name);
	return std::filesystem::file_size(name);
}
