#include "eQoLChanges.h"
#include "..\manhunt\core.h"
#include "..\manhunt\Player.h"
#include "..\manhunt\Hunter.h"
#include "..\manhunt\TypeData.h"
#include "..\manhunt\Scene.h"
#include "..\core\eSettingsManager.h"
#include "classes/eCustomPed.h"

void eQoLChanges::Init()
{
	if (eSettingsManager::bSkipIntroSequence)SkipIntro();

//	InjectHook(0x5A53A7, FixCerberusExecutionAudio, PATCH_JUMP);
}

void eQoLChanges::SkipIntro()
{
	// logo
	Patch<int>(0x5E275F + 2, 0);
	Nop(0x5E2652, 5);
	Nop(0x5E26DC, 5);

	// movie
	Nop(0x4C17AF, 5);

}

void __declspec(naked) eQoLChanges::FixCerberusExecutionAudio()
{
	// todo: unload somehow
	static int cerberus_set_true = 0x5A53BD;
	static int cerberus_set_false = 0x5A53C7;

	_asm {
		pushad
	}

	static CPlayer* plr;
	static CHunter* enemy;
	static CCharacterTypeData* typedata;

	plr = (CPlayer*)CScene::FindPlayer();

	enemy = plr->m_pExecuteHunter;

	if (enemy)
	{
		typedata = (CCharacterTypeData*)enemy->m_pTypeData;

		if (typedata->m_nVoice == CERBERUS || typedata->m_nVoice == CERBERUS_LEADER)
		{
			printf("CERB EXEC\n");
			_asm {
				popad
				jmp cerberus_set_true
			}
		}
		else
		{
			_asm {
				popad
				jmp cerberus_set_false
			}
		}
	}
	else
	{
		_asm {
			popad
			jmp cerberus_set_false
		}
	}

}

void eQoLChanges::FixDecappedHeadsExploding()
{

}


