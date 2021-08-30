#include "eWeaponAdjuster.h"
#include "..\..\core\eSettingsManager.h"
#include "..\..\manhunt\core.h"
#include "..\..\manhunt\Collectable.h"
#include "..\..\manhunt\Entity.h"
#include <Windows.h>
#include <iostream>
#include <string>

eWeaponEntry  eWeaponAdjuster::m_vWeapons[TOTAL_COLLECTABLES];
void eWeaponAdjuster::InitHooks()
{
	if (ReadFile("data\\weapons.dat"))
	{
		InjectHook(0x470F82, CCollectable_IsSniperRifle, PATCH_CALL);
		InjectHook(0x4710E7, CCollectable_IsSniperRifle, PATCH_CALL);
		InjectHook(0x471344, CCollectable_IsSniperRifle, PATCH_CALL);
		InjectHook(0x487FD8, CCollectable_IsSniperRifleLaser, PATCH_CALL);
	
		Patch<char>(0x49D778 + 7, 0x00);
		Patch<char>(0x49D782 + 7, 0x00);
		Nop(0x49D78C, 8);
		InjectHook(0x49D78C, CPed_SetShotDamageStates_ExplodeHead_Shotgun, PATCH_JUMP);
		Nop(0x49D94D, 8);
		InjectHook(0x49D94D, CPed_SetShotDamageStates_ExplodeHead_Rifle, PATCH_JUMP); 
		Nop(0x49D994, 7);
		InjectHook(0x49D994, CPed_SetShotDamageStates_ExplodeHead_Melee, PATCH_JUMP);
		Nop(0x4C9C70, 5);
		InjectHook(0x4C9C6B, CWeaponCollectable_FireWeapon_Audio, PATCH_JUMP);

		InjectHook(0x4C93B0, CWeaponCollectable_GetExecuteAnimClass, PATCH_JUMP);

		InjectHook(0x46C8F6, CCollectable_GetCollectableType_ExecAudio, PATCH_CALL);
		InjectHook(0x46CB22, CCollectable_GetCollectableType_ExecAudio, PATCH_CALL);
		InjectHook(0x46CB38, CCollectable_GetCollectableType_ExecAudio, PATCH_CALL);

		if (eSettingsManager::bEnableExecutionsWithFirearms)
			InjectHook(0x46C7F2, CPed__HoldingMeleeWeapon_Firearm, PATCH_CALL);
	}
}

bool eWeaponAdjuster::ReadFile(const char * path)
{
	for (int i = 0; i < TOTAL_COLLECTABLES; i++)
	{
		m_vWeapons[i] = { 0,0,0 };
	}

	FILE* pFile = fopen(path, "rb");
	if (!pFile)
	{
		MessageBox(0, "Could not open file!", path, MB_ICONERROR);
		return false;
	}

	char line[1024];
	while (fgets(line, sizeof(line), pFile))
	{
		// check if comment
		if (line[0] == ';' || line[0] == '#' || line[0] == '\n')
			continue;

		char collectableType[128] = {};
		if (sscanf(line, "%s", &collectableType) == 1)
		{
			eWeaponFlags flags;
			char execution[32] = {};
			sscanf(line, "%s %d %s",&collectableType, &flags, &execution);

			eWeaponEntry wep;

			wep.m_iFlags = flags;
			wep.m_nType = GetTypeFromStr(collectableType);
			sprintf(wep.m_szExecution, execution);

			m_vWeapons[GetTypeFromStr(collectableType)] = wep;

			printf("%d %d %s\n", wep.m_nType, wep.m_iFlags, wep.m_szExecution);
		}

	}
	fclose(pFile);
	return true;

}

eWeaponEntry eWeaponAdjuster::GetWeapon(int type)
{
	return m_vWeapons[type];
}

eCollectableType eWeaponAdjuster::GetTypeFromStr(char * string)
{
	static const char* weapons[] = {
		"CT_TRIPWIRE","CT_GASOLINE","CT_WATER","CT_LIGHTER",
		"CT_CASH","CT_TORCH","CT_N_VISION","CT_PAINKILLERS","CT_G_FIRST_AID",
		"CT_Y_FIRST_AID","CT_SPEED_BOOST","CT_STRENGTH_BOOST","CT_SHOOTING_BOOST",
		"CT_REFLEXES_BOOST","CT_HEALTH_BOOST","CT_FISTS","CT_K_DUST",
		"CT_KNIFE","CT_SHARD","CT_BROKEN_BOTTLE","CT_JURYBLADES","CT_BOTTLE",
		"CT_PIPE","CT_CLEAVER","CT_WOODEN_BAR","CT_CROWBAR","CT_SICKLE",
		"CT_NIGHTSTICK","CT_CANE","CT_AXE","CT_ICEPICK","CT_MACHETE","CT_SMALL_BAT",
		"CT_BASEBALL_BAT","CT_W_BASEBALL_BAT","CT_FIRE_AXE","CT_HOCKEY_STICK","CT_BASEBALL_BAT_BLADES","CT_6SHOOTER",
		"CT_GLOCK","CT_GLOCK_SILENCED","CT_GLOCK_TORCH","CT_UZI","CT_SHOTGUN","CT_SHOTGUN_TORCH","CT_DESERT_EAGLE",
		"CT_COLT_COMMANDO","CT_SNIPER_RIFLE","CT_TRANQ_RIFLE","CT_SAWNOFF",	"CT_GRENADE","CT_MOLOTOV",
		"CT_EXPMOLOTOV","CT_TEAR_GAS","CT_F_GRENADE","CT_BRICK_HALF","CT_FIREWORK",
		"CT_BAG","CT_RAG","CT_CHLORINE","CT_METHS","CT_HCC","CT_D_BEER_GUY","CT_D_MERC_LEADER","CT_D_SMILEY",
		"CT_D_HUNTLORD","CT_E_L_SIGHT","CT_S_SILENCER","CT_RADIO","CT_BAR_KEY","CT_SYARD_COMB","CT_CAMERA",
		"CT_BODY_P1","CT_BODY_P2","CT_PREC_KEY","CT_PREC_CARD","CT_PREC_DOCS","CT_PHARM_HAND",
		"CT_EST_G_KEY","CT_EST_A_KEY","CT_DOLL","CT_ANTIDOTE","CT_KEY","CT_SWIPE_CARD","null","null","null","CT_CHAINSAW",
		"CT_NAILGUN","CT_WIRE","CT_CAN","CT_WOODEN_SPIKE","null","CT_PIGSY_SHARD","CT_PIGSY_WIRE","CT_PIGSY_SPIKE","CT_HAMMER",
		"CT_DOLL_1","CT_DOLL_2","CT_DOLL_3","CT_HEAD","CT_AMMO_NAILS","CT_AMMO_SHOTGUN","CT_AMMO_PISTOL",
		"CT_AMMO_MGUN",	"CT_AMMO_TRANQ","CT_AMMO_SNIPER","CT_CHAINSAW_PLAYER","CT_DVTAPE","CT_HANDYCAM"
	};

	for (int i = 0; i < TOTAL_COLLECTABLES; i++)
	{
		if (strcmp(string, weapons[i]) == 0)
			return (eCollectableType)(i + 1);
	}
	return (eCollectableType)0;
}

eExecutions eWeaponAdjuster::GetExecutionTypeFromString(char * string)
{
	std::string input = string;

	eExecutions exec = EXEC_DEFAULT;
	if (input == "BAG")             exec = EXEC_BAG;
	else if (input == "KNIFE")      exec = EXEC_KNIFE;
	else if (input == "CROWBAR")    exec = EXEC_CROWBAR;
	else if (input == "BAT")        exec = EXEC_BAT;
	else if (input == "SICKLE")     exec = EXEC_SICKLE;
	else if (input == "WIRE")       exec = EXEC_WIRE;
	else if (input == "CLEAVER")    exec = EXEC_CLEAVER;
	else if (input == "AXE")        exec = EXEC_AXE;
	else if (input == "NIGHTSTICK") exec = EXEC_NIGHTSTICK;
	else if (input == "HAMMER")     exec = EXEC_HAMMER;
	else if (input == "CHAINSAW")   exec = EXEC_CHAINSAW;
	else if (input == "PIGSHARD")   exec = EXEC_PIGSHARD;
	else if (input == "PIGWIRE")    exec = EXEC_PIGWIRE;
	else if (input == "PIGSPIK")    exec = EXEC_PIGSPIK;
	else if (input == "RAMIREZ")    exec = EXEC_RAMIREZ;
	else if (input == "DEFAULT")    exec = EXEC_DEFAULT;
	return exec;
}

int __fastcall eWeaponAdjuster::CCollectable_IsSniperRifle(int ptr)
{
	int ID = (*(int*)(*(int*)(ptr + 124) + 356));

	if (m_vWeapons[ID].m_nType > 0 && m_vWeapons[ID].m_iFlags & FIREARM_SCOPE)
		return 1;

	return 0;
}

int __fastcall eWeaponAdjuster::CCollectable_IsSniperRifleLaser(int ptr)
{
	int ID = (*(int*)(*(int*)(ptr + 124) + 356));

	if (m_vWeapons[ID].m_nType > 0 && m_vWeapons[ID].m_iFlags & FIREARM_LASER)
		return 1;

	return 0;
}

void __declspec(naked) eWeaponAdjuster::CPed_SetShotDamageStates_ExplodeHead_Melee()
{
	static int _esp_melee;
	static int id_melee;
	static int jmpTrue_melee = 0x49D9B1;
	static int jmpFalse_melee = 0x49DCF1;

	_asm {
		mov _esp_melee, esp
		pushad
	}
	id_melee = *(int*)(_esp_melee + 216);

	if (m_vWeapons[id_melee].m_nType > 0 && m_vWeapons[id_melee].m_iFlags & EXPLODE_HEAD_BODY)
	{
		_asm {
			popad
			jmp jmpTrue_melee
		}
	}
	else
	{
		_asm {
			popad
			jmp jmpFalse_melee
		}
	}
}

void __declspec(naked) eWeaponAdjuster::CPed_SetShotDamageStates_ExplodeHead_Shotgun()
{
	static int _esp;
	static int id;
	static int jmpTrue = 0x49D79A;
	static int jmpFalse = 0x49D940;

	_asm {
		mov _esp, esp
		pushad
	}
	id = *(int*)(_esp + 216);

	if (m_vWeapons[id].m_nType > 0 && m_vWeapons[id].m_iFlags & EXPLODE_HEAD_SHOTGUN)
	{
		_asm {
			popad 
			jmp jmpTrue
		}
	}
	else
	{
		_asm {
			popad
			jmp jmpFalse
		}
	}



}

void __declspec(naked) eWeaponAdjuster::CPed_SetShotDamageStates_ExplodeHead_Rifle()
{
	static int _esp_rifle;
	static int id_rifle;
	static int jmpTrue_rifle = 0x49D957;
	static int jmpFalse_rifle = 0x49D976;

	_asm {
		mov _esp_rifle, esp
		pushad
	}
	id_rifle = *(int*)(_esp_rifle + 216);

	if (m_vWeapons[id_rifle].m_nType > 0 && m_vWeapons[id_rifle].m_iFlags & EXPLODE_HEAD)
	{
		_asm {
			popad
			jmp jmpTrue_rifle
		}
	}
	else
	{
		_asm {
			popad
			jmp jmpFalse_rifle
		}
	}

}

void __declspec(naked) eWeaponAdjuster::CWeaponCollectable_FireWeapon_Audio()
{
	static int _ecx_audio;
	static int id_audio;
	static int jmpTrue_audio = 0x4C9C75;
	static int jmpFalse_audio = 0x4C9C83;

	_asm {
		mov _ecx_audio, ecx
		pushad
	}
	id_audio = _ecx_audio;

	if (m_vWeapons[id_audio].m_nType > 0 && m_vWeapons[id_audio].m_iFlags & FIREARM_SILENCED)
	{
		_asm {
			popad
			jmp jmpTrue_audio
		}
	}
	else
	{
		_asm {
			popad
			jmp jmpFalse_audio
		}
	}
}

eExecutions __fastcall eWeaponAdjuster::CWeaponCollectable_GetExecuteAnimClass(int* ptr)
{
	eExecutions execution;

	if (*(int*)(ptr + 80) && (*(int*)(*(int*)(ptr + 80) + 2228)) != 0 && ((int(__thiscall*)(int*))0x4B2F40)(ptr))
	{
		execution = EXEC_RAMIREZ;
	}
	else
	{
		int weaponID = (*(int*)(*(int*)(ptr + 31) + 356));
		
		execution = GetExecutionTypeFromString(m_vWeapons[weaponID].m_szExecution);
	}

	return execution;
}

int __fastcall eWeaponAdjuster::CCollectable_GetCollectableType_ExecAudio(int ptr)
{
	int ID = (*(int*)(*(int*)(ptr + 124) + 356));
	eExecutions exec = GetExecutionTypeFromString(m_vWeapons[ID].m_szExecution);

	switch (exec)
	{
	case EXEC_BAG:
		ID = CT_BAG;
		break;
	case EXEC_KNIFE:
		ID = CT_KNIFE;
		break;
	case EXEC_CROWBAR:
		ID = CT_CROWBAR;
		break;
	case EXEC_BAT:
		ID = CT_BASEBALL_BAT;
		break;
	case EXEC_SICKLE:
		ID = CT_SICKLE;
		break;
	case EXEC_WIRE:
		ID = CT_WIRE;
		break;
	case EXEC_CLEAVER:
		ID = CT_CLEAVER;
		break;
	case EXEC_AXE:
		ID = CT_AXE;
		break;
	case EXEC_NIGHTSTICK:
		ID = CT_NIGHTSTICK;
		break;
	case EXEC_HAMMER:
		ID = CT_HAMMER;
		break;
	case EXEC_CHAINSAW:
		ID = CT_CHAINSAW;
		break;
	case EXEC_PIGSHARD:
		ID = CT_PIGSY_SHARD;
		break;
	case EXEC_PIGWIRE:
		ID = CT_PIGSY_WIRE;
		break;
	case EXEC_PIGSPIK:
		ID = CT_PIGSY_SPIKE;
		break;
	default:
		break;
	}
	return ID;
}

bool __fastcall eWeaponAdjuster::CPed__HoldingMeleeWeapon_Firearm(int ptr)
{
	int  v1;
	int  v2;
	int  v3;

	int result = 0;

	v1 = *(int*)(ptr + 340);

	if (v1 == -1) v2 = 0;
	else
		v2 = (*(int*)(*(int *)(*(int *)(ptr + 336) + 8) + 4 * v1));
	result = 0;
	if (v2)
	{
		
		if ((*(int*)(*(int*)(v2 + 124) + 4) & 0x3001) == EC_WEAPON)
		{

			v3 = *(int*)(v2 + 428);

			// added 3 - if firearm check
			if ((*(int*)(*(int*)(v3 + 4) + 4)) == WC_MELEE || (*(int*)(*(int*)(v3 + 4) + 4)) == WC_MELEE_KICK || (*(int*)(*(int*)(v3 + 4) + 4)) == WC_AMMO)
				return true;
		}



	}
	return result;
}
