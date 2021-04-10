#pragma once


class CMemoryHeap {
public:
	int Malloc(int size);
};

CMemoryHeap* GetMemoryHeap();