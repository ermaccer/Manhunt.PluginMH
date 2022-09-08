#include "Script.h"
#include "core.h"

int CScriptLoader::LoadScriptFile(const char * file)
{
	return CallAndReturn<int, 0x47F1A0, const char*>(file);
}

int CScriptVM::PopInt()
{
	return CallMethodAndReturn<int, 0x4822A0, CScriptVM*>(this);
}

char* CScriptVM::PopCharStar()
{
	return CallMethodAndReturn<char*, 0x4822E0, CScriptVM*>(this);
}

CEntity* CScriptVM::PopEntity()
{
	return CallMethodAndReturn<CEntity*, 0x482200, CScriptVM*>(this);
}

void ScriptCommands::SetCameraPosition(CVector* pos)
{
	Call<0x5432A0, CVector*>(pos);
}

void ScriptCommands::SetAllVideoEffects(bool status)
{
	Call<0x58DB90, bool>(status);
}
