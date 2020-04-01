#include "CRibStreamFix.h"
#include "ManhuntSDK.h"
#include <Windows.h>

int& pCurrentScriptRibStream = *(int*)0x6C7D4C;
int& iCurrentLevel = *(int*)0x75622C;

// 3 - script audio stream

void __declspec(naked) CRibStreamFix::HookScriptCutsceneEnd()
{
	// don't close porn.rib just yet
	if (!(iCurrentLevel == scrap2))
	CallMethod<0x45AC50, int, int>(0x6C7680, 3);
	static int jmpPoint = 0x54248A;
	_asm {
		mov ds:0x79A93C, 0
		jmp jmpPoint
	}
}

void __declspec(naked) CRibStreamFix::HookWhiteNoiseSetVal()
{
	static int jmpPoint = 0x592191;

	CallMethod<0x45AC50, int, int>(0x6C7680, 3);
	_asm {
		mov ds:0x7A13DC, 1
		jmp jmpPoint
	}
}
