#pragma once
#include "Character.h"

namespace modAI_Interface {
	void AISCRIPT_EntityAlwaysEnabled(char* instance);
	void AISCRIPT_AddAIEntity(char* entity);
	void AISCRIPT_SetEntityVoiceID(char* entity, int voiceID);
	void AIScript_BuddyFollow(char* entity);
};

//