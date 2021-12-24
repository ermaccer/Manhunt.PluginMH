#include "Throwable.h"
#include "core.h"

CEntity * CThrowable::GetEntity()
{
	return nullptr;
}

void CThrowable::OnPhysicsInactive()
{
	CallMethod<0x443F80, CThrowable*>(this);
}
