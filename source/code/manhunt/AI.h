#pragma once
#include "Character.h"

enum AISCRIPT_Actions {
	AISCRIPT_IDLE_MOVEANIMS = 4,
	AISCRIPT_IDLE_STANDANIMS

};


enum AIVOICE_VoiceID {
	Hooded_1_Voice_1,
	Hooded_1_Voice_2,
	Hooded_2_Voice_1,
	Hooded_2_Voice_2,
	Hooded_3_Voice_1,
	Hooded_3_Voice_2,
	Innocent_1_Voice_1,
	Innocent_1_Voice_2,
	Innocent_2_Voice_1,
	Innocent_2_Voice_2,
	Innocent_3_Voice_1,
	Innocent_3_Voice_2,
	Police_1_Voice_1_Swat,
	Police_1_Voice_2_Swat,
	Police_1_Voice_3_Swat,
	Police_2_Voice_1,
	Police_2_Voice_2,
	Police_3_Voice_1,
	Police_3_Voice_2,
	Skinz_1_Voice_1,
	Skinz_1_Voice_2,
	Skinz_2_Voice_1,
	Skinz_2_Voice_2,
	Skinz_3_Voice_1,
	Skinz_3_Voice_2,
	Smiley_1_Voice_1,
	Smiley_1_Voice_2,
	Smiley_2_Voice_1,
	Smiley_2_Voice_2,
	Smiley_3_Voice_1,
	Smiley_3_Voice_2,
	Wardog_1_Voice_1,
	Wardog_1_Voice_2,
	Wardog_2_Voice_1,
	Wardog_2_Voice_2,
	Wardog_3_Voice_1,
	Wardog_3_Voice_2,
	Cerberus_1_Voice_1,
	Cerberus_1_Voice_2,
	Cerberus_2_Voice_1,
	Bunny_1_Voice_1,
	Cerb_Leader_1_Voice_1,
	Director_1_Voice_1,
	Journalist_1_Voice_1,
	Monkey_1_Voice_1,
	Piggsy_1_Voice_1,
	Ramirez_1_Voice_1,
};

enum eAISounds {
	FIRE_BUTTON_TEST,
	SNEAKING,
	WALKING,
	RUNNING,
	SPRINTING,
	FALL_LAND,
	JUMP_LAND,
	GUN_SHOT,
	GUN_SHOT_SILENCED,
	LURE_EXPLOSION,
	LURE_BREAK_WINDOW,
	LURE_SHOOTING_AT_ME,
	ALARM,
	ALERT_OTHERS_VERY_HIGH,
	ALERT_OTHERS_HIGH,
	ALERT_OTHERS_MEDIUM,
	ALERT_OTHERS_LOW,
	ALERT_OTHERS_VERY_LOW,
	ALERT_OTHERS_SILENT,
	LURE_HIGH,
	LURE_MEDIUM,
	LURE_THROWN_MEDIUM,
	LURE_LOW,
	LURE_THROWN_LOW,
	LURE_VERY_LOW,
	EXECUTION_MEDIUM,
	EXECUTION_LOW,
	EXECUTION_VERY_LOW,
	DOOR_BANG,
	MELEE_SWIPE,
	SPEECH,
	VOLUME_DISTANCES,
};

int AISCRIPT_EntityAlwaysEnabled(char* instance);
int AISCRIPT_AddAIEntity(char* entity);
int AISCRIPT_SetAIEntityAsLeader(char* entity);
int AISCRIPT_SetEntityVoiceID(char* entity, int voiceID);
int AIScript_BuddyFollow(char* entity);
int AISCRIPT_CancelIdle(char* entity, int action);
int AISCRIPT_AddHunterToLeaderSubpack(char* leader, char* subpack, char* entity);
int AISCRIPT_DefineGoal_HuntEnemy(char* refName, char* who, bool unk, int unk2);
int modAI_Audio_RegisterAISound(eAISounds sound, CEntity* entity, int unk, int unk2);