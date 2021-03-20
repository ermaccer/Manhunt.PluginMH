#pragma once
#include "..\manhunt\Misc.h"

namespace eCustomTableOfContents {
	void InitHooks();
	CFile* __cdecl LoadFile(char* name, int* fileBuffer, int* a3, CFile** file, int* fileSize);
	int  GetTOCFileSize(char* name);
}

