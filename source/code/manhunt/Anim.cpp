#include "Anim.h"
#include "core.h"

int& CAnimManager::ms_nAvailableAnims = *(int*)0x727D40;

bool CAnimManager::LoadAnimations(char * file)
{
	return CallAndReturn<bool,0x4968C0, char*>(file);
}

void CPedBodyAnimFSM::SetRequested(int body, int bodyType, int anim)
{
	CallMethod<0x41D970, int, int, int>(body, bodyType, anim);
}

void CPedBodyAnimFSM::Update(int body, int arg)
{
	CallMethod<0x41F700, int, int>(body, arg);
}

void CPedBodyAnimFSM::SetStand(int body, int anim)
{
	CallMethod<0x41DA10, int, int>(body, anim);
}

int CPedBodyAnimFSM::GetIdleAnimIdFromName(int body, const char * name)
{
	return CallMethodAndReturn<int,0x41D910, int, const char*>(body, name);
}

void CPedTorsoAnimFSM::SetRequested(int body, int bodyType, int anim)
{
	CallMethod<0x41D970, int, int, int>(body, bodyType, anim);
}

void CPedTorsoAnimFSM::Update(int body, int arg)
{
	CallMethod<0x426BD0, int, int>(body, arg);
}


int CPedTorsoAnimFSM::GetIdleAnimIdFromName(int body, const char * name)
{
	return CallMethodAndReturn<int, 0x4255F0, int, const char*>(body, name);
}