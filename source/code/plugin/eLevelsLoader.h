#pragma once
#include <memory>

#define TOTAL_LEVELS 255

struct level_name {
	char name[20];
};

struct level_map {
	int	  unk;
	float coords[8];
};

class eLevelsLoader {
public:
	static int m_nLevels;
	static std::unique_ptr<level_name[]> m_levelNames;
	static std::unique_ptr<level_map[]> m_levelMaps;

	static void GetLevels();
	static void InitHooks();

	static void Init();
};