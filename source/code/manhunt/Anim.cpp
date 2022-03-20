#include "Anim.h"
#include "core.h"

int& CAnimManager::ms_nAvailableAnims = *(int*)0x727D40;

bool CAnimManager::LoadAnimations(char * file)
{
	return CallAndReturn<bool,0x4968C0, char*>(file);
}

void CPedBodyAnimFSM::SetRequested(int bodyType, int anim)
{
	CallMethod<0x41D970, CPedBodyAnimFSM*, int, int>(this, bodyType, anim);
}

void CPedBodyAnimFSM::Update(int arg)
{
	CallMethod<0x41F700, CPedBodyAnimFSM*, int>(this, arg);
}

void CPedBodyAnimFSM::SetStand(int anim)
{
	CallMethod<0x41DA10, CPedBodyAnimFSM*, int>(this, anim);
}

int CPedBodyAnimFSM::GetIdleAnimIdFromName(const char * name)
{
	return CallMethodAndReturn<int,0x41D910, CPedBodyAnimFSM*, const char*>(this, name);
}

void CPedBodyAnimFSM::SetUseExecute(eExecuteAnimClass execution, int level)
{
	CallMethod<0x41E480, CPedBodyAnimFSM*, eExecuteAnimClass, int>(this, execution, level);
}

void CPedBodyAnimFSM::SetDieExecute()
{
	CallMethod<0x41DCF0, CPedBodyAnimFSM*>(this);
}

void CPedBodyAnimFSM::SetDamageExecute(eExecuteAnimClass execution, int level)
{
	CallMethod<0x41DCA0, CPedBodyAnimFSM*, eExecuteAnimClass, int>(this, execution, level);
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