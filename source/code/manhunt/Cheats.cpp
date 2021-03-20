#include "Cheats.h"

bool&  CCheatHandler::m_bCheatsActive = *(bool*)0x7C84AC;
int& CCheatHandler::m_lastCheat = *(int*)0x7C84A8;
int& CCheatHandler::m_fullyarmed = *(int*)0x7C84C0;
int& CCheatHandler::m_godMode = *(int*)0x7C84CC;
int& CCheatHandler::m_heliumHunters = *(int*)0x7C84BC;
int& CCheatHandler::m_invisibility = *(int*)0x7C84C8;
int& CCheatHandler::m_regenerate = *(int*)0x7C84B8;
int& CCheatHandler::m_runner = *(int*)0x7C84B0;
int& CCheatHandler::m_silence = *(int*)0x7C84B4;
int& CCheatHandler::m_superPunch = *(int*)0x7C84C4;

int CCheatHandler::aCheatButtons[8][TOTAL_8_CHEATS] = {
	'U','R','U','N','F','A','S','T', // runner
	'A','L','L','R','D','E','A','F', // silence
	'H','E','A','L','B','A','C','K', // regenerate
	'T','H','E','Y','B','O','O','M', // helium hunters
	'U','G','O','T','A','R','M','S', // fully armed
	'U','H','I','T','H','A','R','D', // super punch
	'B','U','N','Y','S','U','I','T', // white rabbit skin
	'H','E','L','L','S','U','I','T', // monkey skin
	'E','V','I','L','E','Y','E','S', // invisibility
	'P','I','G','G','S','U','I','T', // piggsy skin
	'C','H','E','A','T','O','F','F', // disable cheats
};

int CCheatHandler::aCheatButtons12[12][TOTAL_12_CHEATS] = {
	'I','M','I','N','V','I','N','C','I','B','L','E', // god mode
};

int CCheatHandler::aCheatButtonsConfirms[8][TOTAL_8_CHEATS] = {};
int CCheatHandler::aCheatButtons12Confirms[12][TOTAL_12_CHEATS] = {};


void CCheatHandler::Update()
{
	_DUMMY
}

void CCheatHandler::Reset()
{
	_DUMMY
}

void CCheatHandler::DisableCheatsOnBonusLevels()
{
	_DUMMY
}

void CCheatHandler::SetupForLevel()
{
	Call<0x5D4AF0>();
}
