#pragma once
#include "..\..\manhunt\Collectable.h"
#include "..\..\manhunt\Shot.h"
#include "..\..\RenderWare.h"

class CCustomProjectile : public CWeaponCollectable {
public:
	void Spawn(RwMatrix* mat);

};

class CCustomProjectileShot : public CProjectileShot {
public:
	void NewDestroy(bool create_weapon);

};
