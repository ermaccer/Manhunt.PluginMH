#pragma once
#include "..\..\manhunt\Script.h"
#include <string>
#include <vector>

enum eNewCommands {
	NC_PushMessage = 1001,
	NC_WriteMemory,
	NC_ReadMemory,
	NC_KeyHit,
	NC_SetEntityFlag,
	NC_SetPedHead,
	NC_PedPlayAnim,
	TOTAL_NEW_SCRIPT_COMMANDS
};

class eScriptExtender : public CScriptVM {
public:
	static void Init();
	static void InitHooks();

	static void HookExtraCommands();

	void ProcessNewCommands();
};