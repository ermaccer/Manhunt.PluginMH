#include "eCustomPed.h"
#include "..\..\manhunt\core.h"

void CPedEx::UseCollectableEx(eCollectableType item, bool createIfDoesntExist)
{
	UseCollectable(CT_NIGHTSTICK, createIfDoesntExist);
}
