#include "Decal.h"
#include "core.h"

int CDecal::DecalSet(CVector* pos, CVector* a2, int a3, float size1, float size2, float a6, float a7, int a8, int a9, int a10, int a11, float a12, eDecalTypes decal)
{
	return CallAndReturn<int,0x4829B0, CVector*, CVector*, int, float, float, float, float, int, int, int, int, float, eDecalTypes>(pos, a2, a3, size1, size2, a6, a7, a8, a9, a10, a11, a12, decal);
}