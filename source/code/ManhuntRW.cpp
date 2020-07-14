#include "ManhuntRW.h"

void RwRenderStateSet(RwRenderState state, int value)
{

	(*(void(__cdecl **)(RwRenderState, int))((*(int*)0x82279C + 32)))(state, value);
}

void RwRenderStateSetA(RwRenderState state, int value)
{
	(*(void(__cdecl **)(RwRenderState, int))((*(int*)0x82279C + 36)))(state, value);
}
