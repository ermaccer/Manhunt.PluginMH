#pragma once
#include "..\..\manhunt\Script.h"
#include <string>
#include <vector>

enum eNewCommands {
		PushMessage = 1001,
		WriteMemory,
		ReadMemory,
		KeyHit,
		SetEntityFlag,
		SetPedHead,
		PedPlayAnim,
		TOTAL_NEW_SCRIPT_COMMANDS
};

class eScriptExtender : public CScriptVM {
public:
	static void Init();
	static void InitHooks();

	static void HookExtraCommands();

	void ProcessNewCommands();
};