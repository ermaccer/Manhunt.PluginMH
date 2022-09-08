#pragma once
#include "Entity.h"
#include "Vector.h"
#include "Shot.h"
#include "MaterialManager.h"
#include "String.h"

enum eEntityClass {
	EC_BASIC = 0x1,
	EC_3 = 0x3,
	EC_PED = 0x7,
	EC_F = 0xF,
	EC_HUNTER = 0x1F,
	EC_LEADER = 0x3F,
	EC_7F = 0x7F,
	EC_83 = 0x83,
	EC_183 = 0x183,
	EC_PLAYER = 0x20F,
	EC_ENTITYLIGHT = 0x401,
	EC_COLLECTABLE = 0x1001,
	EC_WEAPON = 0x3001,
	EC_RESPONDER = 0x7001,
	EC_SHOT = 0x8001,
	EC_LIFT = 0x10001,
	EC_DOOR = 0x60001,
	EC_SLIDEDOOR = 0x200001,
	EC_SWITCH = 0xA0001,
	EC_TRIGGER = 0x400001,
	EC_CAMERADATA = 0x20000001,
	EC_SENSOR = 0x800001,
	EC_PEDHEAD = 0x1000001,
	EC_CLIMABLE = 0x120001,
	EC_USEABLE = 0x20001,
	EC_CONVEYOR = 0x2000001,
	EC_MOVER = 0x4000001,

};

enum eCharacterVoiceType {
	VOICE_NONE,
	HOODED_SMALL,
	HOODED_MEDIUM,
	HOODED_BIG,
	INNOCENT_SMALL,
	INNOCENT_MEDIUM,
	INNOCENT_BIG,
	WARDOG_SMALL,
	WARDOG_MEDIUM,
	WARDOG_BIG,
	SMILEY_SMALL,
	SMILEY_MEDIUM,
	SMILEY_BIG,
	SKINZ_SMALL,
	SKINZ_MEDIUM,
	SKINZ_BIG,
	POLICE_SMALL,
	POLICE_MEDIUM,
	POLICE_BIG,
	CERBERUS,
	TRAMP,
	JOURNALIST,
	BUNNY,
	CERBERUS_LEADER,
	PIGGSY,
	RAMIREZ,
	MONKEY,
	DIRECTOR
};



enum eHolsterSlot {
	SLOT_NULL,
	SLOT_BACK,
	SLOT_BELT_RIGHT,
	SLOT_BELT_LEFT,
	SLOT_BELT_REAR,
	SLOT_SPECIAL,
	SLOT_TOTAL_SLOTS
};


class CTypeData {
public:
	void *vTable;
	eEntityClass m_ecEntityClass;
	int m_nEntityFlags;
	char* m_szRecordName;
	__int16 field_10;
	char field_12;
	char field_13;
	char field_14;
	char field_15;
	char field_16;
	char field_17;
	char *m_szModel;
	char field_1C;
	char field_1D;
	char field_1E;
	char field_1F;
	char field_20;
	char field_21;
	char field_22;
	char field_23;
	char *m_szCollisionData;
	char field_28;
	char field_29;
	char field_2A;
	char field_2B;
	char *m_szAnimationBlock;
	char field_30;
	char field_31;
	char field_32;
	char field_33;
	int m_pPhysics;
	int field_38;
	int field_3C;
	int field_40;
	int m_pSounds;
	eMaterialClass m_iMaterialID;
	__declspec(align(4)) char field_4C;
	char field_4D;
	char field_4E;
	char field_4F;
	float m_fLODDistance;
	int field_54;
	int field_58;
	int field_5C;
	int field_60;
	char field_64;
	char field_65;
	char field_66;
	char field_67;
	char field_68;
	char field_69;
	char field_6A;
	char field_6B;
	char field_6C;
	char field_6D;
	char field_6E;
	char field_6F;
	char *field_70;
	char field_74;
	char field_75;
	char field_76;
	char field_77;
	char field_78;
	char field_79;
	char field_7A;
	char field_7B;
	CTypeData *field_7C;
	int field_80;
	char field_84;
	char field_85;
	char field_86;
	char field_87;
	int m_nHitPoints;
	eArmorType m_nArmorType;
	float m_fImpulseLimit;
	int m_iEntityFlags;
	CVector m_vLightAnchor;
	char *m_szSpawnEntity;
	char field_A8;
	char field_A9;
	char field_AA;
	char field_AB;
	char *m_szDamageSpawnEntity;
	char field_B0;
	char field_B1;
	char field_B2;
	char field_B3;
	CVector m_vSpawnPosition;
	CVector m_vSpawnVelocity;
	float BND_SPH_BOOST;
	int m_fxDamage;
	int field_D4;
	int field_D8;
	int field_DC;
	int field_E0;
	int field_E4;
	int field_E8;
	int field_EC;
	bool m_bCameraCollidable;
	char field_F1;
	char field_F2;
	char field_F3;
};

class CCharacterTypeData : public CTypeData
{
public:
	int m_nMaxHealth;
	eCharacterVoiceType m_nVoice;
};

class CPedTypeData : public CCharacterTypeData
{
public:
	CString m_strLowLodModel;
	CString m_strHead;
	int m_nHeadSelection;
	float m_fKnockoutTime;
	float m_fStunTime;
	float m_fSneakWalkSpeed;
	float m_fSneakRunSpeed;
	float m_fWalkSpeed;
	float m_fRunSpeed;
	float m_fSprintSpeed;
	float m_fRunTime;
	float m_fMaxLegDamage;
	float m_fMaxArmDamage;
	float m_fBlockDamage;
	float m_fWalkCycleRightFoot;
	float m_fWalkCycleLeftFoot;
	float field_144;
	char field_148;
	char field_149;
	char field_14A;
	char field_14B;
	char field_14C;
	char field_14D;
	char field_14E;
	char field_14F;
	char field_150;
	char field_151;
	char field_152;
	char field_153;
	char field_154;
	char field_155;
	char field_156;
	char field_157;
	char field_158;
	char field_159;
	char field_15A;
	char field_15B;
	int m_nNumSkins;
};

class CPlayerTypeData : public CPedTypeData
{
public:
	CVector m_vCamPosition;
	float m_fKORecoverySpeed;
	float m_fMoveThresholds[2];
	float m_fMoveTransSpeed;
	float m_fAcceleration[2];
	float m_fStickDeadZone;
	float m_fCrouchForwardSpeed;
	float m_fCrouchBackwardSpeed;
	float m_fCrouchSidewaysSpeed;
	float m_fAimZones[10];
	float m_fAimZonesMonkey[10];
	float m_fAimAxisWidth;
	float m_fMoveAxisWidth;
	float m_fVerticalAimLimit;
	float m_fTurnPause;
	float m_fTurnAcceleration;
	float m_fExtraTurnSpeed;
	float m_fTurnPauseMonkey;
	float m_fTurnAccelerationMonkey;
	float m_fExtraTurnSpeedMonkey;
	float m_fMaxQuickTurnSpeed;
	float m_fStandTurnScaleMonkey;
	float m_fWalkTurnScaleMonkey;
	float m_fRunTurnScaleMonkey;
	float m_fSprintTurnScaleMonkey;
	float m_fLadderUseTime;
	float m_fCamRecentreSpeed;
	float m_fCamStairSpeed;
	float m_fZoomAimScale;
	float m_fZoomAimScaleMoving;
	float m_fZoomLevels[2];
	float m_fZoomSpeed;
	float m_fZoomMoveScales[2];
	float m_fZoomMaxZones[2];
	float m_fCrosshairSizes[3];
	float m_fThrowChargeTime;
	float m_fMinReleaseTime;
	CVector m_fMinThrowVelocity;
	CVector m_fMaxThrowVelocity;
	float m_fSkidTimer;
	float m_fCrouchRecoil;
	float m_fMonkeyTurnAngle;
	float m_fMonkeyMoveAngle;
	float m_fMonkeyWalkAngle;
	float m_fRunThreshold;
	int m_dwInvertStick;
	float m_fAimLockOnAngles[2];
	float m_fAimLockOnDist;
	char field_2A0;
	char field_2A1;
	char field_2A2;
	char field_2A3;
	float m_fStaminaTotalSprintTime;
	float m_fStaminaNoSprintTime;
	float m_fStaminaRecoveryRunning;
	float m_fStaminaRecoveryMoving;
	float m_fStaminaRecoveryStill;
	float m_fStaminaRecoveryPause;
	float m_fWiggleTimeDecay;
	float m_fExecuteStageTimes[2];
};


struct CCollectableTypeData : public CTypeData
{
	char field_0;
	char field_1;
	char field_2;
	char field_3;
	char field_4;
	char field_5;
	char field_6;
	char field_7;
	char field_8;
	char field_9;
	char field_A;
	char field_B;
	char field_C;
	char field_D;
	char field_E;
	char field_F;
	char field_10;
	char field_11;
	char field_12;
	char field_13;
	char field_14;
	char field_15;
	char field_16;
	char field_17;
	char field_18;
	char field_19;
	char field_1A;
	char field_1B;
	char field_1C;
	char field_1D;
	char field_1E;
	char field_1F;
	char field_20;
	char field_21;
	char field_22;
	char field_23;
	char field_24;
	char field_25;
	char field_26;
	char field_27;
	char field_28;
	char field_29;
	char field_2A;
	char field_2B;
	char field_2C;
	char field_2D;
	char field_2E;
	char field_2F;
	char field_30;
	char field_31;
	char field_32;
	char field_33;
	char field_34;
	char field_35;
	char field_36;
	char field_37;
	char field_38;
	char field_39;
	char field_3A;
	char field_3B;
	char field_3C;
	char field_3D;
	char field_3E;
	char field_3F;
	char field_40;
	char field_41;
	char field_42;
	char field_43;
	char field_44;
	char field_45;
	char field_46;
	char field_47;
	char field_48;
	char field_49;
	char field_4A;
	char field_4B;
	char field_4C;
	char field_4D;
	char field_4E;
	char field_4F;
	int field_50;
	int field_54;
	char field_58;
	char field_59;
	char field_5A;
	char field_5B;
	char field_5C;
	char field_5D;
	char field_5E;
	char field_5F;
	char field_60;
	char field_61;
	char field_62;
	char field_63;
	char field_64;
	char field_65;
	char field_66;
	char field_67;
	char field_68;
	char field_69;
	char field_6A;
	char field_6B;
	char field_6C;
	char field_6D;
	char field_6E;
	char field_6F;
	int m_nCollectableType;
	eHolsterSlot m_nHolsterSlot;
	CString m_szTrapModel;
	CString m_szModelUseAnim;
	CString m_szHandAnim;
	int m_szAttachable;
	float m_fUseDelay;
	float m_fSelectDelay;
	float m_fMaxArmPitch;
	char m_szHolsterAnim;
	char field_A1;
	char field_A2;
	char field_A3;
	__int16 field_A4;
	char field_A6;
	char field_A7;
	float m_qHolsterRotation[4];
	CVector m_vHolsterTranslation;
	float m_qStrapRotation[4];
	CVector m_vStrapTranslation;
	float m_qStrap2Rotation[4];
	CVector m_vStrap2Translation;
	int m_bTorchLight;
	CString m_szHolsterModel;
	CVector m_vTorchLightPos;
	CVector m_vTorchLightOrientation;
	float m_fDisplayScale;
	CString m_szModelDisplayAnim;
};
