#include "Scene.h"
#include "core.h"
#include "Anim.h"

bool& CScene::ms_bFreeCam = *(bool*)0x715BB0;
int& CScene::ms_stepMode = *(int*)0x715BA0;
CEntity*& CScene::ms_pPlayer = *(CEntity**)0x715B9C;
CEntity*& CScene::ms_pCamera = *(CEntity**)0x715B94;
int& CScene::ms_pWorld= *(int*)0x715B8C;
void CScene::OpenLevel(const char * level)
{
	Call<0x474330, const char*>(level);
}

CEntity * CScene::FindPlayer()
{
	return *(CEntity**)0x715B9C;
}

void CScene::PlayerFullBodyAnimDone()
{
	int* player = *(int**)0x715B9C;
	if (!player[448] && player[439])
	{
		player[439] = 0;
		player[440] = 0;
	}
	if (!player[448])
		player[440] = 0;
	player[441] = 0;
	//CPedBodyAnimFSM::SetStand(player[190], 854);
}

RpWorld * CScene::GetWorld()
{
	return *(RpWorld **)0x715B8C;
}
