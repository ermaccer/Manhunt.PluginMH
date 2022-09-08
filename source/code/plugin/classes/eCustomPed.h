#pragma once
#include "..\..\manhunt\Ped.h"

class CPedEx : public CPed {
public:
	void UseCollectableEx(eCollectableType item, bool createIfDoesntExist);

	void ExplodeHeadEx(CVector* pos, int headSelection);

	void PreUpdateEx();
};
