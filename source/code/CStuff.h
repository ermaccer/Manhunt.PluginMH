#pragma once
#include <iostream>
namespace CStuff {
	void EnableCheatsOnBonusLevels();
	bool KeyHit(unsigned int keyCode);
	int HookDebugEntires();
	void DumpPlayerCoords();
	void HookManTriIcon(float x, float y, float scaleX, float scaleY, int red, int green, int blue, int alpha, int pTexture);
	void HookSkipIntroSeq();
	void DisableExecutionCamera();
}