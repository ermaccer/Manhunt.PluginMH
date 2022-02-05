#pragma once
#include "Collectable.h"

class cMusicManager {
public:
	void StopStreaming();
	void PreloadExecutionStream(eCollectableType type);
};


extern cMusicManager* MusicManager;