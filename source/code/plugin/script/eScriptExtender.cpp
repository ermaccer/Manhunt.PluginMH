#include "eScriptExtender.h"
#include "..\..\manhunt\core.h"
#include <filesystem>

void eScriptExtender::Init()
{
	InitHooks();
}

void eScriptExtender::InitHooks()
{
	InjectHook(0x482062, eScriptExtender::HookExtraCommands, PATCH_JUMP);
}

void __declspec(naked) eScriptExtender::HookExtraCommands()
{
	static int jmpPoint_last  = 0x482073;
	static int jmpPoint_false = 0x482080;
	static int no = TOTAL_NEW_SCRIPT_COMMANDS - 1;
	_asm {
		cmp edx, 773
		jg  next
		mov ecx, ebx
		mov eax, 0x57AE60
		call eax
		jmp jmpPoint_last

		next:
		cmp edx, no
		jg jump
		mov ecx, ebx
		call ProcessNewCommands
		jmp jmpPoint_last

		jump:
		jmp jmpPoint_false
	}
}

void eScriptExtender::ProcessNewCommands(CScriptVM * vm)
{
	printf("executing new\n");
	switch (vm->m_commandID)
	{
	case PushMessage:
		MessageBoxA(0, "command test", 0, 0);
		break;
	case WriteMemory:
		MessageBoxA(0, "command test", 0, 0);
		break;
	case ReadMemory:
		MessageBoxA(0, "command test", 0, 0);
		break;
	case KeyHit:
		MessageBoxA(0, "command test", 0, 0);
		break;
	default:
		return;
	}
}
