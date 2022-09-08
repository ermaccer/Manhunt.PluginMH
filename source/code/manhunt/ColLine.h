#pragma once
#include "Vector.h"
#include "ContactInfo.h"

class CColLine {
public:
	CVector vstart;
	CVector vend;
	CVector vdist;
	CVector vdistnorm;
	int fdist;
	float fdistsqr;


	void Calculate();
	bool TestBSP(CContactInfo* contact, float* unk);
};