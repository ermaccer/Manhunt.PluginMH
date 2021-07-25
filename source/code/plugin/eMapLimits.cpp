#include "eMapLimits.h"
#include "..\manhunt\core.h"
#include "..\manhunt\Filenames.h"
#include "..\manhunt\Scene.h"
#include "..\manhunt\MemoryHeap.h"

CNewCollisionMaterialManager gNewCollisionMaterialManager;

void eMapLimits::InitHooks()
{
	Patch<int>(0x43DDDC, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x43E433, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4454EE, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4454F4, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x44657A, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x446A55, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x446A70, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x446AC9, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x446CB7, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x446D77, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x446DAD, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x447F67, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x448098, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x448309, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x44EAA0, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4746D5, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x474B74, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x475A8E, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4832B0, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4832C0, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x48D447, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x491357, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4A57F7, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4A74D1, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4B289B, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DD8B4, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DDAC4, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DDD76, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DDEB6, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DDF54, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DE047, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DE057, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DE099, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DE0A9, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DE110, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DE120, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DE1F9, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DE209, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DF341, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4DF351, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4E7B1B, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4F4531, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4F5468, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x4F580B, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x5223A6, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x56AD95, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x571F2E, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x572050, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x5721EF, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x59ADC7, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x59B2E1, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x5A71D0, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x5A769D, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x5A77F8, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x5C1C29, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x5C1EB5, (int)&gNewCollisionMaterialManager);
	Patch<int>(0x5C8030, (int)&gNewCollisionMaterialManager.m_aMaterialIds[0]);
	Patch<int>(0x5C873A, (int)&gNewCollisionMaterialManager.m_aMaterialIds[0]);
	Patch<int>(0x5A71B3, (int)&gNewCollisionMaterialManager.m_numWorldMaterials);


	Patch<int>(0x5A739B + 2, (int)offsetof(CNewCollisionMaterialManager, m_pMaterialIndices));
	Patch<int>(0x5A7357 + 2, (int)offsetof(CNewCollisionMaterialManager, m_pMaterialIndices));

	Patch<int>(0x5A7343 + 3, (int)offsetof(CNewCollisionMaterialManager, m_numWorldMaterials));
	Patch<int>(0x5A72F3 + 3, (int)offsetof(CNewCollisionMaterialManager, m_numWorldMaterials));
	Patch<int>(0x5A7360 + 3, (int)offsetof(CNewCollisionMaterialManager, m_numMaterials));

	Patch<int>(0x5A7323 + 2, (int)offsetof(CNewCollisionMaterialManager, m_pMaterialIndices));
	Patch<int>(0x5A7333 + 2, (int)offsetof(CNewCollisionMaterialManager, m_pMaterialIndices));


	Patch<int>(0x5A7176 + 3, (int)offsetof(CNewCollisionMaterialManager, m_aMaterialLists));
	Patch<int>(0x5A7180 + 3, ((int)offsetof(CNewCollisionMaterialManager, m_aMaterialLists)) + 4);
	Patch<int>(0x5A718D + 3, ((int)offsetof(CNewCollisionMaterialManager, m_aMaterialLists)) + 4);


	Patch<int>(0x5A736B + 1, (int)CNewCollisionMaterialManager::GetMaterials);

	InjectHook(0x5A706A, &CNewCollisionMaterialManager::ReadMaterials, PATCH_CALL);
}

void CNewCollisionMaterialManager::ReadMaterials()
{
	Call<0x4D4FC0, char*>(CFileNames::ms_MaterialBinary.str);
	int matAmount = *(int*)(*(int*)(0x7392BC));
	int* v3 = (int *)((*(int*)(0x7392BC)) + 4);
	for (int i = 0; i < matAmount; ++v3)
	{
		m_aMaterialLists[i].m_numTextures = *v3;
		int numTextures = m_aMaterialLists[i].m_numTextures;
		if (numTextures)
			m_aMaterialLists[i].m_ppTextureNames = CallMethodAndReturn<char**, 0x401350, int>(0x67D000, 4 * numTextures);
		else
			m_aMaterialLists[i].m_ppTextureNames = 0;
		++i;
	}
	for (int j = 0; j < matAmount; ++j)
	{
		for (int k = 0; k < m_aMaterialLists[j].m_numTextures; v3 += 50)
			m_aMaterialLists[j].m_ppTextureNames[k++] = (char *)v3;
	}
}

int CNewCollisionMaterialManager::CountWorldMaterials_Callback(int a)
{
	++gNewCollisionMaterialManager.m_numMaterials;
	return a;
}

void CNewCollisionMaterialManager::GetMaterials(int* material)
{
	int mat_id; 
	bool mat_found; 
	char* mat_name;

	if (*material)
	{
		mat_name = (char *)(*material + 16);
		mat_id = 0;
		mat_found = 0;
		while (mat_id < TOTAL_MATERIALS_COUNT && !mat_found)
		{
			//printf("Mat: %s\n", mat_name);
			for (int i = 0; i < gNewCollisionMaterialManager.m_aMaterialLists[mat_id].m_numTextures && !mat_found; ++i)
			{
				if (!strcmp(mat_name, gNewCollisionMaterialManager.m_aMaterialLists[mat_id].m_ppTextureNames[i]))
				{
					gNewCollisionMaterialManager.m_pMaterialIndices[gNewCollisionMaterialManager.m_numMaterials] = mat_id;
					mat_found = 1;
					gNewCollisionMaterialManager.m_apMaterials[gNewCollisionMaterialManager.m_numMaterials] = material;
				}
			}
			++mat_id;
		}
		if (mat_found)
		{
			//if (gbTextureID)
			//	RpMaterialSetTexture((int)material, dword_7D3808);
		}
		else
		{
			++gNewCollisionMaterialManager.m_numMissingMaterials;
			gNewCollisionMaterialManager.m_pMaterialIndices[gNewCollisionMaterialManager.m_numMaterials] = 0;
			gNewCollisionMaterialManager.m_apMaterials[gNewCollisionMaterialManager.m_numMaterials] = material;
		}
		++gNewCollisionMaterialManager.m_numMaterials;
	}
	else
	{
		gNewCollisionMaterialManager.m_pMaterialIndices[gNewCollisionMaterialManager.m_numMaterials] = 0;
		gNewCollisionMaterialManager.m_apMaterials[gNewCollisionMaterialManager.m_numMaterials] = material;
		gNewCollisionMaterialManager.m_numMaterials += 1;
	}
}

void CNewCollisionMaterialManager::Free()
{
	for (int i = 0; i < TOTAL_MATERIALS_COUNT; ++i)
	{
		if (m_aMaterialLists[i].m_numTextures)
			Call<0x401010,char**>(m_aMaterialLists[i].m_ppTextureNames);
		m_aMaterialLists[i].m_ppTextureNames = 0;
	}
	Call<0x4D5030>();
}


void CNewCollisionMaterialManager::CountWorldMaterials()
{
	m_numWorldMaterials = 0;
	CallMethod<0x5A72F0, CNewCollisionMaterialManager*>(this);
}
