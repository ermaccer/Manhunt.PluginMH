#pragma once
#include "Entity.h"
#include "Vector.h"
#include "Shot.h"
#include "MaterialMananger.h"

enum eEntityClass {
	EC_BASIC = 0x1,
	EC_3 = 0x3,
	EC_PED = 0x7,
	EC_F = 0xF,
	EC_HUNTER = 0x1F,
	EC_LEADER = 0x3F,
	EC_7F = 0x7F,
	EC_83 = 0x83,
	EC_183 = 0x183,
	EC_PLAYER = 0x20F,
	EC_ENTITYLIGHT = 0x401,
	EC_COLLECTABLE = 0x1001,
	EC_WEAPON = 0x3001,
	EC_RESPONDER = 0x7001,
	EC_SHOT = 0x8001,
	EC_LIFT = 0x10001,
	EC_DOOR = 0x60001,
	EC_SLIDEDOOR = 0x200001,
	EC_SWITCH = 0xA0001,
	EC_TRIGGER = 0x400001,
	EC_CAMERADATA = 0x20000001,
	EC_SENSOR = 0x800001,
	EC_PEDHEAD = 0x1000001,
	EC_CLIMABLE = 0x120001,
	EC_USEABLE = 0x20001,
	EC_CONVEYOR = 0x2000001,
	EC_MOVER = 0x4000001,

};

class CTypeData {
public:
	void *vTable;
	eEntityClass m_ecEntityClass;
	int m_nEntityFlags;
	int field_C;
	__int16 field_10;
	char field_12;
	char field_13;
	char field_14;
	char field_15;
	char field_16;
	char field_17;
	char *m_szModel;
	char field_1C;
	char field_1D;
	char field_1E;
	char field_1F;
	char field_20;
	char field_21;
	char field_22;
	char field_23;
	char *m_szCollisionData;
	char field_28;
	char field_29;
	char field_2A;
	char field_2B;
	char *m_szAnimationBlock;
	char field_30;
	char field_31;
	char field_32;
	char field_33;
	int m_pPhysics;
	int field_38;
	int field_3C;
	int field_40;
	int m_pSounds;
	eMaterialClass m_iMaterialID;
	__declspec(align(4)) char field_4C;
	char field_4D;
	char field_4E;
	char field_4F;
	float m_fLODDistance;
	int field_54;
	int field_58;
	int field_5C;
	int field_60;
	char field_64;
	char field_65;
	char field_66;
	char field_67;
	char field_68;
	char field_69;
	char field_6A;
	char field_6B;
	char field_6C;
	char field_6D;
	char field_6E;
	char field_6F;
	char *field_70;
	char field_74;
	char field_75;
	char field_76;
	char field_77;
	char field_78;
	char field_79;
	char field_7A;
	char field_7B;
	CTypeData *field_7C;
	int field_80;
	char field_84;
	char field_85;
	char field_86;
	char field_87;
	int m_nHitPoints;
	eArmorType m_nArmorType;
	float m_fImpulseLimit;
	int m_iEntityFlags;
	CVector m_vLightAnchor;
	char *m_szSpawnEntity;
	char field_A8;
	char field_A9;
	char field_AA;
	char field_AB;
	char *m_szDamageSpawnEntity;
	char field_B0;
	char field_B1;
	char field_B2;
	char field_B3;
	CVector m_vSpawnPosition;
	CVector m_vSpawnVelocity;
	float BND_SPH_BOOST;
	int m_fxDamage;
	int field_D4;
	int field_D8;
	int field_DC;
	int field_E0;
	int field_E4;
	int field_E8;
	int field_EC;
	bool m_bCameraCollidable;
	char field_F1;
	char field_F2;
	char field_F3;
};