#pragma once
#include "..\..\manhunt\Script.h"
#include <string>
#include <vector>

enum eNewCommands {
		PushMessage = 1001,
		WriteMemory,
		ReadMemory,
		KeyHit,
		TOTAL_NEW_SCRIPT_COMMANDS
};

class eScriptExtender {
public:
	static void Init();
	static void InitHooks();

	static void HookExtraCommands();

	void ProcessNewCommands(CScriptVM* vm);
};