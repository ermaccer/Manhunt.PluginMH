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

int CInventory::FindItemWithCollectableType(int ptr, int collectable)
{
	return CallMethodAndReturn<int, 0x4929E0, int, int>(ptr, collectable);
}
