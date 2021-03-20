#include "AI.h"
#include "core.h"




void modAI_Interface::AISCRIPT_EntityAlwaysEnabled(char * instance)
{
	CallMethod<0x53BCF0, int, char*>(0x799B50, instance);
}
