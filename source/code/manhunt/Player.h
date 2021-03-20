#pragma once
#include "Entity.h"

class CPlayer: public CEntity {
public:
	void StartLookAround();
	void ForcePlayAnim(const char* name);
	void ForcePlayFullBodyAnim(const char* name);
};