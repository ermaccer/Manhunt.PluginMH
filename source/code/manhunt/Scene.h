#pragma once
#include "Entity.h"
#include <rwcore.h>
#include <rwplcore.h>
#include <rpworld.h>

class CScene {
public:
	static bool& ms_bFreeCam;
	// also known as freeze world
	static int&  ms_stepMode;
	static CEntity*& ms_pPlayer;
	static CEntity*& ms_pCamera;
	static int&  ms_pWorld;
	static void OpenLevel(const char* level);
	static CEntity* FindPlayer();
	static void PlayerFullBodyAnimDone();

	static RpWorld* GetWorld();
};