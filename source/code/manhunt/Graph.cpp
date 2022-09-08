#include "Graph.h"
#include "core.h"

CGraphManager& TheGraph = *(CGraphManager*)0x682848;


bool CGraph::CheckForLineOfSightObstruction(CVector * a, CVector * b)
{
	return CallAndReturn<bool, 0x4067A0, CVector*, CVector*>(a, b);
}

CGraphEntry* GetGraphEntry(int id)
{
	return &TheGraph.nodes[id];
}
