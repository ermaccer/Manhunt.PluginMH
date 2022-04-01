#include "eCustomPed.h"
#include "..\..\manhunt\core.h"

void CPedEx::UseCollectableEx(eCollectableType item, bool createIfDoesntExist)
{
	UseCollectable(CT_NIGHTSTICK, createIfDoesntExist);
}

void CPedEx::ExplodeHeadEx(CVector* pos, int headSelection)
{
	if (m_pPedHead->m_bIsHidden)
		return;

	ExplodeHead(pos, headSelection);
}
