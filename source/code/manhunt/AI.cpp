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

int AISCRIPT_AddLeaderEnemy(char * entity, char * enemy)
{
	return CallMethodAndReturn<int, 0x538A40, int, char*, char*>(0x799B50, entity, enemy);
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
	return CallMethodAndReturn<int, 0x5392A0, int, char*, char*, bool, int>(0x799B50, refName, who, unk, unk2);
}

int AISCRIPT_DefineGoal_BeBuddy(char * goalName, char * entityName, char * whoToBeBuddyWith, char * home, float radius)
{
	return CallMethodAndReturn<int, 0x53A020, int, char*, char*, char*, char*, float>(0x799B50, goalName, entityName, whoToBeBuddyWith, home, radius);
}

int modAI_Audio_RegisterAISound(eAISounds sound, CEntity * entity, int unk, int unk2)
{
	return CallMethodAndReturn<int, 0x520640, int, eAISounds, CEntity*,int,int>(0x7957BC, sound, entity, unk, unk2);

}

void AISENSES_IgnorePlayer()
{
	Call<0x5E4D20>();
}

void AI_MakeHuntersIdle()
{
	Call<0x4EFCD0>();
}
