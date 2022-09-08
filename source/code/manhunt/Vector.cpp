#include "Vector.h"
CVector CrossProduct(const CVector& v1, const CVector& v2)
{
	return CVector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}