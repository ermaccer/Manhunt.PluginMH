#include "CDebugMenuLimit.h"
#include "..\MemoryMgr.h"
#include <memory>
using namespace Memory::VP;

#define FE_DEV_MENU_ITEMS_MAX 170

char szDevMenuNames[FE_DEV_MENU_ITEMS_MAX * 32];

int jmpHookOne = 0x5F1EC9;

void CDebugMenuLimit::Init()
{
	Patch<int>(0x5E9AAB + 2, (int)szDevMenuNames);
	Patch<int>(0x5F22C9 + 2, 0);
}

void __declspec(naked) CDebugMenuLimit::HookOne()
{
	_asm {
		lea eax, szDevMenuNames
		mov ebx, eax
		jmp jmpHookOne
	}
}
