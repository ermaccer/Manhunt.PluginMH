#include "ColLine.h"
#include "core.h"

void CColLine::Calculate()
{
	CallMethod<0x4044F0, CColLine*>(this);
}

bool CColLine::TestBSP(CContactInfo* contact, float* unk)
{
	return CallMethodAndReturn<bool, 0x4DE800, CColLine*, CContactInfo*, float*>(this, contact, unk);
}