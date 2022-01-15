#include "Graph.h"
#include "core.h"

bool CGraph::CheckForLineOfSightObstruction(CVector * a, CVector * b)
{
	return CallAndReturn<bool, 0x4067A0, CVector*, CVector*>(a, b);
}
