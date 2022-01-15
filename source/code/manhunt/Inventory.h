#pragma once
#include "Collectable.h"

enum eInventorySlots {
	BACK = 1,
	BELT_RIGHT,
	BELT_LEFT,
	BELT_REAR,
	SPECIAL
};


class CGameInventory {
public:
	static int& ms_inv;
	static int& ms_curRedItem;
	static int& ms_curBlueItem;
	static int& ms_curGreenItem;
	static int& ms_curThrowableItem;

	static int GetCurrentItem();
	static int GetIconTexture(eCollectableType type, bool display);
};

class CInventory {
public:
	int field_0;
	int m_numSlots;
	CCollectable** m_inventory;

	CInventory(int slots);
	CCollectable* FindItemWithCollectableType(int collectable);
	void RemoveItem(CCollectable* item);

	void RemoveAllItems();

	int GetNumItems();
};