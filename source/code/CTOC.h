#pragma once

#include "ManhuntSDK.h"

namespace eTOC {
	CFile* __cdecl HookLoadFile(char *name, int *fileBuffer, int *a3, CFile **file, int *fileSize);
	bool   HookLoadTOC(bool isGlobal);
	void  HookSkipLevelToc();
}