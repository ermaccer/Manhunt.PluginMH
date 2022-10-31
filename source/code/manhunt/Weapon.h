#pragma once
#include "Vector.h"


enum eWeaponClass {
	WC_MELEE,
	WC_MELEE_KICK,
	WC_THROWING,
	WC_AMMO,
	WC_EXPLODER
};

class CWeaponTypeData {
public:
	void* vTable;
	eWeaponClass m_eWeaponClass;
	int   field8;
	int   field12;
	char* m_szShotType;
	int   field20;
	char* m_szShotType2;
	int   field28;
	char* m_szSpecialWeaponAnim;
};

struct CWeapon
{
	void* vTable;
	CWeaponTypeData* m_TypeData;
	int m_pOwner;
	int m_pCollectable;
	int field_10;
	int field_14;
	__declspec(align(16)) int field_20;
	int* m_pShots;
	int field_28;
	int field_2C;
	int m_numShots;
	int field_34;
	int field_38;
	int field_3C;
	char field_40;
	char field_41;
	char field_42;
	char field_43;
	char field_44;
	char field_45;
	char field_46;
	char field_47;
	char field_48;
	char field_49;
	char field_4A;
	char field_4B;
	char field_4C;
	char field_4D;
	char field_4E;
	char field_4F;
	char field_50;
	char field_51;
	char field_52;
	char field_53;
	char field_54;
	char field_55;
	char field_56;
	char field_57;
	int field_58;
	int field_5C;
	int field_60;
	int field_64;
	int field_68;
	int field_6C;
	int field_70;
	int field_74;
	CVector m_vFireDirection;
	int field_84;
	int field_88;
	int field_8C;
};

class CWeaponManager {
public:
	static void CreateAndFireAWeapon(const char* name, CVector *pos, CVector *dir);
};