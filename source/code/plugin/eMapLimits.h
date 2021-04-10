#pragma once
#include "..\manhunt\MaterialManager.h"
#define AMOUNT_OF_MATERIALS 2500


struct material_struct {
	int m_numTextures;
	char **m_ppTextureNames;
};
class eMapLimits {
public:
	static void InitHooks();
};


class CNewCollisionMaterialManager {
public:
	short m_aMaterialIds[TOTAL_MATERIALS_COUNT];
	int  *m_apMaterials[AMOUNT_OF_MATERIALS];
	material_struct m_aMaterialLists[TOTAL_MATERIALS_COUNT];
	short  *m_pMaterialIndices;
	short m_numWorldMaterials;
	short m_numMaterials;
	short m_numMissingMaterials;
	char m_bTextureAssignOn;

	void ReadMaterials();
	static int  CountWorldMaterials_Callback(int a);
	static void GetMaterials(int* material);
	void Free();
	void CountWorldMaterials();
};

extern CNewCollisionMaterialManager gNewCollisionMaterialManager;