#pragma once
#include "Vector.h"

struct CGraphNode {
	char pad[32];
	char name[16];
};

struct CGraphEntry {
	int unk;
	CGraphNode* node;
};


struct CGraphManager {
	char pad[12];
	CGraphEntry* nodes;
};


class CGraph {
public:
	static bool CheckForLineOfSightObstruction(CVector* a, CVector* b);
};


CGraphEntry* GetGraphEntry(int id);

extern CGraphManager& TheGraph;