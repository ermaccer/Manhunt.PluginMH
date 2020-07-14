#include "CTOC.h"
#include <filesystem>
using namespace ManhuntFileFunctions;

int& iFileStreamSize = *(int*)0x7392C8;
char& byte_7392CC = *(char*)0x7392CC;
char& unk_67D000 = *(char*)0x67D000;

CFile *__cdecl eTOC::HookLoadFile(char * name, int * fileBuffer, int * a3, CFile ** file, int * fileSize)
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

	iFileStreamSize = 25 * 1024 * 1024;
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

bool eTOC::HookLoadTOC(bool isGlobal)
{

	CFile* gToc;
	int srcBuffer;

	gToc = Rockstar_fopen(2, 1, "levels//global//toc.txt");

	if (!gToc)
		return 0;

	//v16 = (char *)sub_401350(unk_67D000, 4160);
	//a1 = (char *)((unsigned int)(v16 + 64) & 0xFFFFFFC0);

	srcBuffer = CallMethodAndReturn<int, 0x401350, int, int>(0x67D000, 4160);

	CallMethod<0x401B00, int, int>(0x67D000, srcBuffer);
	return true;
}

void __declspec(naked) eTOC::HookSkipLevelToc()
{
	static int jumpPoint = 0x474382;
	_asm jmp jumpPoint
}
