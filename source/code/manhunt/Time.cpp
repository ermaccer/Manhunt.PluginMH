#include "Time.h"
#include "core.h"

int& CGameTime::ms_startRealTime = *(int*)0x756268;
int& CGameTime::ms_realTimeOffset = *(int*)0x75626C;
int& CGameTime::ms_currGameTime = *(int*)0x756270;
int& CGameTime::ms_currGameTimePaused= *(int*)0x756274;
int& CGameTime::ms_timeStep = *(int*)0x756280;
int& CGameTime::ms_currFrame = *(int*)0x75628C;

void CGameTime::Update()
{
	Call<0x4D87D0>();
}
