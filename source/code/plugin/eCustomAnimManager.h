#pragma once
#include <memory>

#define CUSTOM_ANIMMANAGER_TOTAL_ANIMS 2500

class CCustomAnimManager {
public:
	static std::unique_ptr<int[]> ptrNewAnimationsArray;
	static void InitHooks();
	static bool Initialise();
};