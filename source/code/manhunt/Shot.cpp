#include "Shot.h"
#include "core.h"

void CProjectileShot::Destroy(bool create_weapon)
{
	CallMethod<0x4F7730, CProjectileShot*,bool>(this, create_weapon);
}
