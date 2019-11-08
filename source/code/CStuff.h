#pragma once

namespace CStuff {
	void EnableCheatsOnBonusLevels();
	bool KeyHit(unsigned int keyCode);
	int HookDebugEntires();
	void DisplayVariousData();
	void DumpPlayerCoords();
	void LoadSkins(char* line);
	void DisplayWeaponsHook();
	void HookManTriIcon(float x, float y, float scaleX, float scaleY, int red, int green, int blue, int alpha, int pTexture);
}