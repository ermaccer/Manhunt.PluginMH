#pragma once

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
};

class CInventory {
private:
	void* vTable;
public:
	static int FindItemWithCollectableType(int ptr, int collectable);
};