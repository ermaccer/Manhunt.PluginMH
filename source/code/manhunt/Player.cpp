#include "Player.h"
#include "core.h"

void CPlayer::StartLookAround()
{
	CallMethod<0x462060, CEntity*>(this);
}

void CPlayer::ForcePlayAnim(const char * name)
{
	CallMethod<0x46E390, CEntity*, const char*>(this, name);
}

void CPlayer::ForcePlayFullBodyAnim(const char * name)
{
	CallMethod<0x46E260, CEntity*, const char*>(this, name);
}

void CPlayer::AccumulateTime()
{
	CallMethod<0x45BB10,CPlayer*>(this);
}

int CPlayer::GetExecuteStage()
{
	return CallMethodAndReturn<int, 0x46CB80, CPlayer*>(this);
}

void CPlayerHelper::SetModel(char* name)
{
}
