#pragma once
#include "core.h"

enum eCheatMasks {
	CHEAT_RUNNER = 0x1,
	CHEAT_SILENCE = 0x2,
	CHEAT_REGENERATION = 0x4,
	CHEAT_EXPLODE = 0x8,
	CHEAT_EQUIPPED = 0x10,
	CHEAT_SUPERPUNCH = 0x20,
	CHEAT_RABBIT = 0x40,
	CHEAT_MONKEY = 0x80,
	CHEAT_INVIS = 0x100,
	CHEAT_PIGGSY = 0x200,
	CHEAT_GODMODE = 0x400,
};

enum eCheats8 {
	runner,
	silence,
	regenerate,
	heliumHunters,
	fullyarmed,
	superPunch,
	rabbit,
	monkey,
	invisiblity,
	piggsy,
	cheatoff,
	TOTAL_8_CHEATS
};

enum eCheats12 {
	godmode,
	TOTAL_12_CHEATS
};

class CCheatHandler {
public:
	static int& m_lastCheat;
	static bool& m_bCheatsActive;
	// cheats
	static int& m_runner;
	static int& m_silence;
	static int& m_regenerate;
	static int& m_heliumHunters;
	static int& m_fullyarmed;
	static int& m_superPunch;
	static int& m_invisibility;
	static int& m_godMode;

	// data
	static int aCheatButtons[8][TOTAL_8_CHEATS];
	static int aCheatButtons12[12][TOTAL_12_CHEATS];
	static int aCheatButtonsConfirms[8][TOTAL_8_CHEATS];
	static int aCheatButtons12Confirms[12][TOTAL_12_CHEATS];
	static void Update();
	static void Reset();
	static void DisableCheatsOnBonusLevels();
	static void SetupForLevel();
};