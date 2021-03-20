#include "Misc.h"
#include "core.h"

CFile * Rockstar_fopen(int mode, int fMode, char * extraParam)
{
	return CallAndReturn<CFile*, 0x6121A0, int, int, char*>(mode, fMode, extraParam);
}

int ReadFileBytes(CFile * src, int dst, int size)
{
	return CallAndReturn<int, 0x611C80, CFile*, int, int>(src, dst, size);
}
