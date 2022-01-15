#include "Ped.h"
#include "core.h"

void CPed::ChangePedHead(const char * newHead)
{
	CallMethod<0x49CC70, CPed*, const char*>(this,newHead);
}

void CPed::ExplodeHead(CVector* pos, int headSelect)
{
	CallMethod<0x49CCB0, CPed*, CVector*, int>(this, pos, headSelect);
}

void CPed::SeverHead(CVector * pos)
{
	CallMethod<0x49CE60, CPed*, CVector*>(this, pos);
}

void CPed::SetHeading(float heading, bool unk)
{
	CallMethod<0x4A32C0, CPed*,float, bool>(this, heading ,unk);
}

void CPed::SelectInventoryItem(eHolsterSlot slot, int unk)
{
	CallMethod<0x4ABE70, CPed*, eHolsterSlot, int>(this,slot, unk);
}
