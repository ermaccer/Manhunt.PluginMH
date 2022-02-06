#pragma once
#include "..\..\manhunt\Collectable.h"
#include <vector>

enum eWeaponFlags {
	EXPLODE_HEAD_SHOTGUN = 1,
	EXPLODE_HEAD = 2,
	EXPLODE_HEAD_BODY = 4,
	FIREARM_SILENCED = 8,
	FIREARM_SCOPE = 16,
	FIREARM_LASER = 32
};

struct eWeaponEntry {
	int				  m_iFlags;
	int				  m_nType;
	char			  m_szExecution[32] = {};
};


class CWeaponCollectableEx : public CWeaponCollectable{
public:
	eExecuteAnimClass GetExecuteAnimClassEx();
};

class eWeaponAdjuster {
public:
	static eWeaponEntry m_vWeapons[TOTAL_COLLECTABLES];
	static void	InitHooks();
	static bool ReadFile(const char* path);
	static eWeaponEntry		GetWeapon(int type);
	static eCollectableType GetTypeFromStr(char* string);

	static eExecuteAnimClass		GetExecutionTypeFromString(char* string);

	static int  __fastcall				CCollectable_IsSniperRifle(int ptr);
	static int  __fastcall				CCollectable_IsSniperRifleLaser(int ptr);
	static void							CPed_SetShotDamageStates_ExplodeHead_Melee();
	static void							CPed_SetShotDamageStates_ExplodeHead_Shotgun();
	static void							CPed_SetShotDamageStates_ExplodeHead_Rifle();
	static void							CWeaponCollectable_FireWeapon_Audio();
	static eExecuteAnimClass __fastcall	    CWeaponCollectable_GetExecuteAnimClass(int* ptr);
	static int	__fastcall				CCollectable_GetCollectableType_ExecAudio(int ptr);
	static bool	__fastcall				CPed__HoldingMeleeWeapon_Firearm(int ptr);
};

