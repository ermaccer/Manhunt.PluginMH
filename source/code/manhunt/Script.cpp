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
