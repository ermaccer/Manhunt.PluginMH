#pragma once
#include "Vector.h"

struct CParticleEffect
{
	void *vTable;
	int field_4;
	char field_8;
	char field_9;
	char field_A;
	char field_B;
	char field_C;
	char field_D;
	char field_E;
	char field_F;
	int field_10;
	int field_14;
	char field_18;
	char field_19;
	char field_1A;
	char field_1B;
	char field_1C;
	char field_1D;
	char field_1E;
	char field_1F;
	char field_20;
	char field_21;
	char field_22;
	char field_23;
	char field_24;
	char field_25;
	char field_26;
	char field_27;
	char field_28;
	char field_29;
	char field_2A;
	char field_2B;
	int field_2C;
	float field_30;
	char field_34;
	char field_35;
	char field_36;
	char field_37;
	char field_38;
	char field_39;
	char field_3A;
	char field_3B;
	CVector m_nParticlePosition;
	CVector field_48;
	char field_54;
	char field_55;
	char field_56;
	char field_57;
	int field_58;
	int field_5C;
	int field_60;
	char field_64;
	char field_65;
	char field_66;
	char field_67;
	int field_68;
	int field_6C;
	int field_70;
	int field_74;
	int field_78;
	int field_7C;
	char field_80;
	char field_81;
	char field_82;
	char field_83;
	char field_84;
	char field_85;
	char field_86;
	char field_87;
	char field_88;
	char field_89;
	char field_8A;
	char field_8B;
	int field_8C;
	int field_90;
	int field_94;
	char field_98;
	char field_99;
	char field_9A;
	char field_9B;
	char field_9C;
	char field_9D;
	char field_9E;
	char field_9F;
	char field_A0;
	char field_A1;
	char field_A2;
	char field_A3;
	char field_A4;
	char field_A5;
	char field_A6;
	char field_A7;
	char field_A8;
	char field_A9;
	char field_AA;
	char field_AB;
	char field_AC;
	char field_AD;
	char field_AE;
	char field_AF;
	char field_B0;
	char field_B1;
	char field_B2;
	char field_B3;
	char field_B4;
	char field_B5;
	char field_B6;
	char field_B7;
	char field_B8;
	char field_B9;
	char field_BA;
	char field_BB;
	char field_BC;
	char field_BD;
	char field_BE;
	char field_BF;
	int field_C0;
	char field_C4;
	char field_C5;
	char field_C6;
	char field_C7;
	char field_C8;
	char field_C9;
	char field_CA;
	char field_CB;
	char field_CC;
	char field_CD;
	char field_CE;
	char field_CF;
	char field_D0;
	char field_D1;
	char field_D2;
	char field_D3;
	char field_D4;
	char field_D5;
	char field_D6;
	char field_D7;
	int field_D8;
	char field_DC;
	char field_DD;
	char field_DE;
	char field_DF;
	char field_E0;
	char field_E1;
	char field_E2;
	char field_E3;
	char field_E4;
	char field_E5;
	char field_E6;
	char field_E7;
	char field_E8;
	char field_E9;
	char field_EA;
	char field_EB;
	char field_EC;
	char field_ED;
	char field_EE;
	char field_EF;
	char field_F0;
	char field_F1;
	char field_F2;
	char field_F3;
	char field_F4;
	char field_F5;
	char field_F6;
	char field_F7;
	char field_F8;
	char field_F9;
	char field_FA;
	char field_FB;
	char field_FC;
	char field_FD;
	char field_FE;
	char field_FF;
};



class CSFXManager {
public:
	static int GetArchetypeFromName(const char* name);
	static void				SetPosition(CParticleEffect* effect, CVector* position);
	static CParticleEffect* NewSFX(int archetype);
};