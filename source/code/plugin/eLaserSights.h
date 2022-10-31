#pragma once
#include "..\manhunt\Vector.h"

class eLaserSights {
public:

	static CVector debugStart, debugEnd;

	static void Initialize();
	static void Draw();

	static void Hook_Draw();
};