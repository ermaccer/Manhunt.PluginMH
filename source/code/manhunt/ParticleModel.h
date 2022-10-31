#pragma once
#include "Vector.h"
#include "Entity.h"
#include "Matrix.h"

class CParticleModel {
public:
	CVector m_vTravel;
	int field_C;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	int m_nModelType;
	CEntity* m_pOwner;
	int m_pClump;
	CVector m_vPosition;
	int field_3C;
	int field_40;
	float field_44;
	float field_48;
	float field_4C;
	float field_50;
	float field_54;
	int field_58;

	CParticleModel();
	CParticleModel(int modelType, int ownerContext, int clump, CVector* position, CMatrix* matrix, CVector* physicsTravel, CVector* spin, float radius, float bounce, float a11, float a12, float a13, void(__cdecl* colFunc)(CParticleModel*, void*));
	~CParticleModel();

	static CParticleModel* CreateParticle(int modelType, CEntity* ownerContext, int clump, CVector* position, CMatrix* matrix, CVector* physicsTravel, CVector* spin, float radius, float bounce, float a11, float a12, float a13, void(__cdecl* colFunc)(CParticleModel*, void*));
	static bool RegisterParticle(CParticleModel* particle);
};


