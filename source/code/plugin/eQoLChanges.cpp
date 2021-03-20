#include "eQoLChanges.h"
#include "..\manhunt\core.h"

void eQoLChanges::SkipIntro()
{
	// logo
	Patch<int>(0x5E275F + 2, 0);
	Nop(0x5E2652, 5);
	Nop(0x5E26DC, 5);

}


