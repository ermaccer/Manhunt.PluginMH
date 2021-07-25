#include "AI.h"
#include "core.h"




void modAI_Interface::AISCRIPT_EntityAlwaysEnabled(char * instance)
{
	CallMethod<0x53BCF0, int, char*>(0x799B50, instance);
}

void modAI_Interface::AISCRIPT_AddAIEntity(char * entity)
{
	CallMethod<0x538530, int, char*>(0x799B50, entity);
}

void modAI_Interface::AISCRIPT_SetEntityVoiceID(char * entity, int voiceID)
{
	CallMethod<0x53BF20, int, char*, int>(0x799B50, entity, voiceID);
}

void modAI_Interface::AIScript_BuddyFollow(char * entity)
{
	CallMethod<0x53B9D0, int, char*>(0x799B50, entity);
}
