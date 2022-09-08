#include "AudioManager.h"
#include "core.h"

cAudioManager& AudioManager = *(cAudioManager*)0x6B53D8;
cDMAudio& DMAudio = *(cDMAudio*)0x6C5244;

void cAudioManager::ResetLevel()
{
	CallMethod<0x455C70, cAudioManager*>(this);
}

void cAudioManager::RequestMiscOneShot(CVector* pos, eSampleIDs sample, int unk, int unk2)
{
	CallMethod<0x5B5810, cAudioManager*, CVector*, eSampleIDs, int, int>(this, pos, sample, unk, unk2);
}

int cAudioManager::ProcessWeapon_Fire(eCollectableType item, int a2, int a3, float* freq, float* a5)
{
	return CallMethodAndReturn<int, 0x44F620, cAudioManager*,eCollectableType, int, int, float*, float*>(this, item, a2, a3, freq, a5);
}

void cDMAudio::PlayFrontEndSound(short sample, float unk)
{
	CallMethod<0x456280,cDMAudio*, short, float>(this, sample, unk);
}
