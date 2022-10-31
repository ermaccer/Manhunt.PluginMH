#pragma once
#include "Weapon.h"
#include "Vector.h"

class CAmmoWeaponTypeData : public CWeaponTypeData {
public:
	int   field36;
	int   field40;
	char* sz_ModelReloadAnim;
	int   field48;
	char* sz_ModelReloadCockAnim;
	int   field56;
	char* sz_ModelReloadZoomCockAnim;
	int   field64;
	char* sz_ModelReloadEmptyAnim;
	int   field72;
	char* sz_ModelFireEmptyAnim;
	int   field80;
	float m_fMinRange;
	float m_fMaxRange;
	float m_fMaxRangeHitProbability;
	int   field96;
	float m_fLockOnTargetRanges;
	int   m_nMaxClips;
	int   m_nClipAmmo;
	int   m_nMaxShots;
	float m_fShellReloadTime;
	float m_fShellReloadTime2;
	CVector2D m_vecRecoilDist;
	float m_fRecoilTime;
	float m_fRecoilVertAccumulator;
	float m_fMaxRecoilVertDistance;
	float m_fRecoilReturnAccuracy;
	float m_fShotSpread;
	int   m_nDroppedAmmo;
	float m_fFireCycleTime;
	char* m_szSmokeShellFX;
	int   field164;
	int   m_bHasReloadLoop;
	CVector2D m_vecReloadLoop;
	int   m_nNumHeadShots;
	float  m_fTorsoDamageMultipiler;
	float  m_fArmDamageMultipiler;
	float  m_fLegDamageMultipiler;
	float  m_fMaxPlayerShotgunDamage;
	int   field196;
	int   m_fxSmokeShell;

};

class CAmmoWeapon : public CWeapon {
public:
	int* m_pAmmoShots;
	int m_nMaxAmmoShots;
	int m_nReserveAmmo;
	char field_9C;
	char field_9D;
	char field_9E;
	char field_9F;
	int m_nClipAmmo;
	int field_A4;
	int field_A8;
	float m_fShellReloadTime;
	int field_B0;
	int field_B4;
	int field_B8;
	int field_BC;
	char field_C0;
	char field_C1;
	char field_C2;
	char field_C3;
	int field_C4;
	float m_fShotgunDamage;
	int m_pSniperDotFX;
	int field_D0;
	int field_D4;
	int field_D8;
	int field_DC;
	int field_E0;

	void Reload(int flag);
	void SetAmmo(unsigned int amount);
	void GetFiringDirection(CVector* dest, float unk, int unk2, int unk3);
	void GetFiringPoint(CVector* dest, int unk);
	void UpdateFiringDirection(float unk);
	static bool& ms_bHeadShot;

	
};