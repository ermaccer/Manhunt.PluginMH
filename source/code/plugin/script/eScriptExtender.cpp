#include "eScriptExtender.h"
#include "..\..\manhunt\core.h"
#include <filesystem>
#include "..\eLog.h"
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
		cmp edx, 1005
		jg jump
		mov ecx, ebx
		call ProcessNewCommands
		jmp jmpPoint_last

		jump:
		jmp jmpPoint_false
	}
}

void eScriptExtender::ProcessNewCommands()
{
	int value, size, addr, retn;
	switch (m_commandID)
	{
	case PushMessage:
		PopInt();
		printf("%s\n", PopCharStar());
		break;
	case WriteMemory:
		value =PopInt();
		size = PopInt();
		addr = PopInt();
		switch (size)
		{
		case 1:
			Memory::VP::Patch<char>(addr, value);
			break;
		case 2:
			Memory::VP::Patch<short>(addr, value);
			break;
		case 4:
			Memory::VP::Patch<int>(addr, value);
			break;
		default:
			eLog::Message(__FUNCTION__, "Command %d | Invalid size (%d)! ", WriteMemory, size);
			break;
		}
		break;
	case ReadMemory:
		size = PopInt();
		addr = PopInt();

		switch (size)
		{
		case 1:
			retn = *(char*)(addr);
			break;
		case 2:
			retn = *(short*)(addr);
			break;
		case 4:
			retn = *(int*)(addr);
			break;
		default:
			eLog::Message(__FUNCTION__, "Command %d | Invalid size (%d)!  Returning 0", ReadMemory, size);
			retn = 0;
			break;
		}
		m_returnValue = retn;
		break;
	case KeyHit:
		int key;
		key = PopInt();
		m_returnValue = GetAsyncKeyState(key);
		break;
	case SetEntityFlag:
		CEntity* ent;
		int flag, status;

		status = PopInt();
		flag = PopInt();
		ent = PopEntity();

		if (ent)
			ent->SetFlag(flag, status);
		else
			eLog::Message(__FUNCTION__, "Command %d | Invalid entity!", SetEntityFlag);

		break;
	default:
		return;
	}
}
