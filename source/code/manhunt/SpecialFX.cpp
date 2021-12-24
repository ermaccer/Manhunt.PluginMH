#include "SpecialFX.h"
#include "core.h"
#include "String.h"

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

int FXSystem_Play(const char * name, CVector * pos, RwMatrix * matrix, bool once)
{
	int bp = CallMethodAndReturn<int, 0x5BC540, int, const char*>(0x7B8BF0, name);
	int system = 0;
	if (bp)
	{
		system = CallMethodAndReturn<int, 0x5BC320, int, int, CVector*, RwMatrix*, int>(0x7B8BF0, bp, pos, matrix, 0);
		if (system)
		{
			if (once)
				CallMethod<0x5BE660, int>(system);
			else
				CallMethod<0x5BE5D0, int>(system);
		}
	}
	return system;
}
