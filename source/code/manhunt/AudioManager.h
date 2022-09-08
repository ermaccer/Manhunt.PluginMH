#pragma once
#include "Collectable.h"
#include "SampleIDs.h"

class cAudioManager {
public:
	void ResetLevel();
	void RequestMiscOneShot(CVector* pos, eSampleIDs sample, int unk, int unk2);
	int ProcessWeapon_Fire(eCollectableType item, int a2, int a3, float* freq, float* a5);
};


class cDMAudio {
public:
	void PlayFrontEndSound(short sample, float unk);
};

extern cAudioManager& AudioManager;

extern cDMAudio& DMAudio;