#include "MemoryHeap.h"
#include "core.h"
int CMemoryHeap::Malloc(int size)
{
	return CallMethodAndReturn<int, 0x401350, CMemoryHeap*>(this, size);
}

CMemoryHeap * GetMemoryHeap()
{
	return	*(CMemoryHeap**)0x67D000;
}
