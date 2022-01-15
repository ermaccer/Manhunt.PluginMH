#pragma once
#include "Entity.h"
#include "Collectable.h"
#include "Weapon.h"
#include "Inventory.h"
#include "TypeData.h"



class CCharacter : public CEntity {
public:
	int field_0;
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	CInventory *m_pInventory;
	int m_nCurrentSlot;
	int field_1C;
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
	float field_30;
	int field_34;
	int field_38;
	int field_3C;
	int field_40;
	int field_44;
	int field_48;
	int field_4C;
	char field_50;
	char field_51;
	char field_52;
	char field_53;
	int field_54;
	int field_58;
	int field_5C;
	int field_60;
	int field_64;
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

	void CreateInventoryItem(int collectable, bool settoactive);
	void UseInventoryCollectable(int unk, int slot);
	CWeapon* GetCurrentWeapon();
};