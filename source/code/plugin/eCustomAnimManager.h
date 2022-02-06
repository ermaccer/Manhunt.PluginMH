#pragma once
#include <memory>

#define CUSTOM_ANIMMANAGER_TOTAL_ANIMS 2500

struct eAnimationEntry {
	char name[48] = {};
};

class CCustomAnimManager {
public:
	static std::unique_ptr<int[]> ptrNewAnimationsArray;
	static std::unique_ptr<eAnimationEntry[]> ptrNewAnimationsNamesArray;
	static void InitHooks();
	static void LoadAnimations();
	static bool Initialise();

	static bool IsAnimAvailable(int id);
};