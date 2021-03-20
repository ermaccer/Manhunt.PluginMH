#pragma once
#include "Weapon.h"
enum eShotClass {
	SC_BASIC,
	SC_INSTANT,
	SC_INSTANT_MACHINEGUN,
	SC_MELEE,
	SC_MELEE_KICK,
	SC_MELEE_OBSTRUCT,
	SC_PROJECTILE,
	SC_PROJECTILE_WEAPON,
	SC_AREA
};

enum eShotPrimitive {
	SP_LINE,
	SP_SPHERE
};

enum eArmorType {
	ARM_NONE,
	ARM_LIGHT,
	ARM_MEDIUM,
	ARM_HEAVY,
	ARM_INVULNERABLE
};


class CShotTypeData {
public:
	void*          vTable;
	eShotClass     m_nShotClass;
	eShotPrimitive m_nShotPrimitive;
	int            field12;
	int            field16;
	float          m_fSize;
	float          m_fDamage;
	float          m_fPlayerDamage;
	float          m_fSideDamage;
	float          m_fBackDamage;
	eArmorType     m_nArmorType;
	float          m_fAliveTime;
	float          m_fShotForce;
	int            m_nBodiesHit;
	float          m_fTranqTime;
	char*          m_szHardBSPHitFx;
	int            field64;
	char*          m_szSoftBSPHitFx;
	int            field72;
	char*          m_szCharacterHitFx;
	int            field80;
	char*          m_szSmokeBSPHitFx;
	int            field88;
	int            field92;
	int            field96;
	char*          m_szStreakFx;
	int            field104;
	char*          m_szFlashFx;
	int            field112;
	int            m_fxHardHit;
	int            m_fxSoftHit;
	int            m_fxSmokeHit;
	int            m_fxCharacterHit;
	int            m_fxStreak;
	int            m_fxFlash;
};

class CAreaShotTypeData : public CShotTypeData {
public:
	float    m_fInitRadius;
	float    m_fFinalRadius;
	float    m_fExpansionTime;
};





class CShot {
	void* vTable;
	CShotTypeData* m_TypeData;
	CWeapon * m_pWeapon;
};

