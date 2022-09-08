#pragma once
#include "Vector.h"

enum eDecalTypes {
	DT_TEST,
	DT_BLOOD,
	DT_BLOOD2,
	DT_BLOOD3,
	DT_BLOOD_DEAD,
	DT_MELEE,
	DT_EXPLOSION,
	DT_FLUID,
	DT_TEST_2,
	DT_METAL,
	DT_STONE,
	DT_WOOD,
	DT_METAL_2,
	DT_STONE_2,
	DT_METAL_3,
	DT_GLASS,
	DT_STONE_3,
	DT_METAL_4,
	DT_WOOD_2,
	DT_FABRIC,
	DT_STONE_4,
	DT_FABRIC_2,
	DT_FABRIC_3,
	DT_FABRIC_4,
	DT_FABRIC_5,
	DT_TOTAL_DECALS,
};

struct CDecalEntry {
	eDecalTypes m_nDecalID;
	int m_bIsVisible;
	int m_nAlpha;
	int field_C;
	int m_pPointer;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	int field_24;
};

class CDecal {
public:

	static int DecalSet(CVector* pos, CVector* a2 /* rot?*/, int a3, float size1, float size2, float a6, float a7, int r, int g, int b, int a, float a12, eDecalTypes decal);
};