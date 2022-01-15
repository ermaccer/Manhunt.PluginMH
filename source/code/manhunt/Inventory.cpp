#include "Inventory.h"
#include "core.h"


int& CGameInventory::ms_inv = *(int*)0x7C9CD0;
int& CGameInventory::ms_curRedItem = *(int*)0x7C9CE8;
int& CGameInventory::ms_curBlueItem = *(int*)0x7C9CEC;
int& CGameInventory::ms_curGreenItem = *(int*)0x7C9CF0;
int& CGameInventory::ms_curThrowableItem = *(int*)0x7C9CF4;

int CGameInventory::GetCurrentItem()
{
	switch (ms_inv)
	{
	case BACK:
		return ms_curRedItem; break;
	case BELT_RIGHT:
		return ms_curBlueItem; break;
	case BELT_LEFT:
		return ms_curGreenItem; break;
	case BELT_REAR:
		return ms_curThrowableItem; break;
	default:
		return -1;
		break;
	}
}

int CGameInventory::GetIconTexture(eCollectableType type, bool display)
{
	return CallAndReturn<int, 0x5DF9A0,eCollectableType, bool>(type, display);
}

CInventory::CInventory(int slots)
{
	CallMethod<0x492740, CInventory*, int>(this, slots);
}

CCollectable* CInventory::FindItemWithCollectableType(int collectable)
{
	return CallMethodAndReturn<CCollectable*, 0x4929E0, CInventory*, int>(this, collectable);
}

void CInventory::RemoveItem(CCollectable * item)
{
	CallMethod<0x492810, CInventory*, CCollectable*>(this, item);
}

void CInventory::RemoveAllItems()
{
	for (int i = 1; i < m_numSlots; i++)
		m_inventory[i] = 0;
}

int CInventory::GetNumItems()
{
	int items = 0;
	for (int i = 1; i < m_numSlots; i++)
		if (m_inventory[i])
			items++;

	return items;
}
