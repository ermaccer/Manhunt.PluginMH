#include "SpecialFX.h"
#include "core.h"

int CSFXManager::GetArchetypeFromName(const char * name)
{
	return CallAndReturn<int, 0x4878E0, const char*>(name);
}

void CSFXManager::SetPosition(CParticleEffect * effect, CVector* position)
{
	float len = CallAndReturn<float, 0x615430, CVector*>(position);
	float mult = 1.0f / len;
	effect->m_nParticlePosition = *position;
	effect->m_nParticlePosition.x *= mult;
	effect->m_nParticlePosition.y *= mult;
	effect->m_nParticlePosition.z *= mult;
	(*((void(__thiscall **)(CParticleEffect *))effect->vTable + 4))(effect);
}

CParticleEffect * CSFXManager::NewSFX(int archetype)
{
	return CallAndReturn<CParticleEffect*, 0x4879A0, int>(archetype);
}
