#include "core.h"
#include "ParticleModel.h"
#include "Frontend.h"
#include "Player.h"
#include "Scene.h"
#include "MemoryHeap.h"

CParticleModel::CParticleModel()
{
}

CParticleModel::CParticleModel(int modelType, int ownerContext, int clump, CVector* position, CMatrix* matrix, CVector* physicsTravel, CVector* spin, float radius, float bounce, float a11, float a12, float a13, void(__cdecl* colFunc)(CParticleModel*, void*))
{
	CallMethod<0x59A830, CParticleModel*, int, int, int, CVector*, CMatrix*, CVector*, CVector*, float, float, float, float, float, void(__cdecl*)(CParticleModel*, void*)>(this, modelType, ownerContext, clump, position, matrix, physicsTravel, spin, radius, bounce, a11, a12, a13, colFunc);
}

CParticleModel::~CParticleModel()
{
	CallMethod<0x59AA00, CParticleModel*>(this);
}

CParticleModel* CParticleModel::CreateParticle(int modelType, CEntity* ownerContext, int clump, CVector* position, CMatrix* matrix, CVector* physicsTravel, CVector* spin, float radius, float bounce, float a11, float a12, float a13, void(__cdecl* colFunc)(CParticleModel*, void*))
{
	CParticleModel* particle = (CParticleModel*)GetMemoryHeap()->Malloc(92);

	if (particle)
		CallMethod<0x59A830, CParticleModel*, int, CEntity*, int, CVector*, CMatrix*, CVector*, CVector*, float, float, float, float, float, void(__cdecl*)
			(CParticleModel*, void*)>(particle, modelType, ownerContext, clump, position, matrix, physicsTravel, spin, radius, bounce, a11, a12, a13, colFunc);

	return particle;
}

bool CParticleModel::RegisterParticle(CParticleModel* particle)
{
	return CallAndReturn<bool, 0x487A60, CParticleModel*>(particle);
}
