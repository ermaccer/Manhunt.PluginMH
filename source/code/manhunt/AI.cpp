#include "AI.h"
#include "core.h"




int AISCRIPT_EntityAlwaysEnabled(char * instance)
{
	return CallMethodAndReturn<int, 0x53BCF0, int, char*>(0x799B50, instance);
}

int AISCRIPT_AddAIEntity(char * entity)
{
	return CallMethodAndReturn<int, 0x538530, int, char*>(0x799B50, entity);
}

int AISCRIPT_SetAIEntityAsLeader(char * entity)
{
	return CallMethodAndReturn<int, 0x538680, int, char*>(0x799B50, entity);
}

int AISCRIPT_SetEntityVoiceID(char * entity, int voiceID)
{
	return CallMethodAndReturn<int,0x53BF20, int, char*, int>(0x799B50, entity, voiceID);
}

int AIScript_BuddyFollow(char * entity)
{
	return CallMethodAndReturn<int, 0x53B9D0, int, char*>(0x799B50, entity);
}

int AISCRIPT_CancelIdle(char * entity, int action)
{
	return CallMethodAndReturn<int, 0x53C430, int, char*, int>(0x799B50, entity, action);
}

int AISCRIPT_AddHunterToLeaderSubpack(char * leader, char * subpack, char * entity)
{
	return CallMethodAndReturn<int, 0x538870, int, char*, char*, char*>(0x799B50, leader, subpack, entity);
}

int AISCRIPT_DefineGoal_HuntEnemy(char * refName, char * who, bool unk, int unk2)
{
	return CallMethodAndReturn<int, 0x53C430, int, char*, char*, bool, int>(0x799B50, refName, who, unk, unk2);
}

int modAI_Audio_RegisterAISound(eAISounds sound, CEntity * entity, int unk, int unk2)
{
	return CallMethodAndReturn<int, 0x520640, int, eAISounds, CEntity*,int,int>(0x7957BC, sound, entity, unk, unk2);

}
