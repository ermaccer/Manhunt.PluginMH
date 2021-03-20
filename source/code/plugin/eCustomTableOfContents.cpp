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


CFile * eCustomTableOfContents::LoadFile(char * name, int * fileBuffer, int * a3, CFile ** file, int * fileSize)
{
	int srcBuffer;
	int readBytes;
	int tmpFileSize;
	int buffer;
	unsigned int totalSize;

	*fileSize = 0;
	*file = Rockstar_fopen(2, 1, name);
	if (!*file)
		return 0;

	//iFileStreamSize = CallAndReturn<int, 0x4D61B0, char*>(name);

	iFileStreamSize = std::filesystem::file_size(name);
	totalSize = iFileStreamSize;


	if (byte_7392CC) //always 0 anyway
		srcBuffer = CallMethodAndReturn<int, 0x4012D0, int, int>(unk_67D000, iFileStreamSize + 64);
	else
		srcBuffer = CallMethodAndReturn<int, 0x401350, int, int>(0x67D000, totalSize + 64);

	*fileBuffer = srcBuffer;
	buffer = (*fileBuffer + 64) & 0xFFFFFFC0;
	*a3 = buffer;
	readBytes = ReadFileBytes(*file, buffer, totalSize);

	tmpFileSize = readBytes;

	*fileSize = tmpFileSize;
	return Rockstar_fopen(3, 1, (char*)&buffer);
}

int eCustomTableOfContents::GetTOCFileSize(char * name)
{
	//printf("File %s\n", name);
	return std::filesystem::file_size(name);
}
