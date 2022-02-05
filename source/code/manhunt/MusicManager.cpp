#include "MusicManager.h"
#include "core.h"

cMusicManager* MusicManager = *(cMusicManager**)0x7A9EBC;

void cMusicManager::StopStreaming()
{
	CallMethod<0x5A14A0, cMusicManager*>(this);
}

void cMusicManager::PreloadExecutionStream(eCollectableType type)
{
	CallMethod<0x5A5370, cMusicManager*>(this, type);
}
