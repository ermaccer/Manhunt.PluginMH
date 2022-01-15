#pragma once
#include "Entity.h"
#include <rwcore.h>

enum eCollectableType {
	CT_TRIPWIRE = 1,
	CT_GASOLINE,
	CT_WATER,
	CT_LIGHTER,
	CT_CASH,
	CT_TORCH,
	CT_N_VISION,
	CT_PAINKILLERS,
	CT_G_FIRST_AID,
	CT_Y_FIRST_AID,
	CT_SPEED_BOOST,
	CT_STRENGTH_BOOST,
	CT_SHOOTING_BOOST,
	CT_REFLEXES_BOOST,
	CT_HEALTH_BOOST,
	CT_FISTS,
	CT_K_DUST,
	CT_KNIFE,
	CT_SHARD,
	CT_BROKEN_BOTTLE,
	CT_JURYBLADES,
	CT_BOTTLE,
	CT_PIPE,
	CT_CLEAVER,
	CT_WOODEN_BAR,
	CT_CROWBAR,
	CT_SICKLE,
	CT_NIGHTSTICK,
	CT_CANE,
	CT_AXE,
	CT_ICEPICK,
	CT_MACHETE,
	CT_SMALL_BAT,
	CT_BASEBALL_BAT,
	CT_W_BASEBALL_BAT,
	CT_FIRE_AXE,
	CT_HOCKEY_STICK,
	CT_BASEBALL_BAT_BLADES,
	CT_6SHOOTER,
	CT_GLOCK,
	CT_GLOCK_SILENCED,
	CT_GLOCK_TORCH,
	CT_UZI,
	CT_SHOTGUN,
	CT_SHOTGUN_TORCH,
	CT_DESERT_EAGLE,
	CT_COLT_COMMANDO,
	CT_SNIPER_RIFLE,
	CT_TRANQ_RIFLE,
	CT_SAWNOFF,
	CT_GRENADE,
	CT_MOLOTOV,
	CT_EXPMOLOTOV,
	CT_TEAR_GAS,
	CT_F_GRENADE,
	CT_BRICK_HALF,
	CT_FIREWORK,
	CT_BAG,
	CT_RAG,
	CT_CHLORINE,
	CT_METHS,
	CT_HCC,
	CT_D_BEER_GUY,
	CT_D_MERC_LEADER,
	CT_D_SMILEY,
	CT_D_HUNTLORD,
	CT_E_L_SIGHT,
	CT_S_SILENCER,
	CT_RADIO,
	CT_BAR_KEY,
	CT_SYARD_COMB,
	CT_CAMERA,
	CT_BODY_P1,
	CT_BODY_P2,
	CT_PREC_KEY,
	CT_PREC_CARD,
	CT_PREC_DOCS,
	CT_PHARM_HAND,
	CT_EST_G_KEY,
	CT_EST_A_KEY,
	CT_DOLL,
	CT_ANTIDOTE,
	CT_KEY,
	CT_SWIPE_CARD,
	CT_CHAINSAW = 88,
	CT_NAILGUN,
	CT_WIRE,
	CT_CAN,
	CT_WOODEN_SPIKE,
	CT_PIGSY_SHARD = 94,
	CT_PIGSY_WIRE,
	CT_PIGSY_SPIKE,
	CT_HAMMER,
	CT_DOLL_1,
	CT_DOLL_2,
	CT_DOLL_3,
	CT_HEAD,
	CT_AMMO_NAILS,
	CT_AMMO_SHOTGUN,
	CT_AMMO_PISTOL,
	CT_AMMO_MGUN,
	CT_AMMO_TRANQ,
	CT_AMMO_SNIPER,
	CT_CHAINSAW_PLAYER,
	CT_DVTAPE,
	CT_HANDYCAM,
	TOTAL_COLLECTABLES
};

enum eExecutions {
	EXEC_BAG,
	EXEC_KNIFE,
	EXEC_CROWBAR,
	EXEC_BAT,
	EXEC_SICKLE,
	EXEC_WIRE,
	EXEC_CLEAVER,
	EXEC_AXE,
	EXEC_NIGHTSTICK,
	EXEC_HAMMER,
	EXEC_CHAINSAW,
	EXEC_PIGSHARD,
	EXEC_PIGWIRE,
	EXEC_PIGSPIK,
	EXEC_RAMIREZ,
	EXEC_DEFAULT
};


class CCollectable: public CEntity {
public:
	int m_collectableFlags;
	CEntity *pOwner;
	int field_8;
	int field_C;
	int field_10;
	CVector m_collectablePos;
	float field_20;
	float m_fTimeToDelete;
	int field_28;
	int field_2C;
	int field_30;
	int *field_34;
	int field_38;
	int field_3C;
	int field_40;
	int field_44;
	int field_48;
	int field_4C;
	int field_50;
	int field_54;
	int field_58;
	int m_pAnimBlendAssociation;
	int field_60;
	int field_64;
	int field_68;

	static wchar_t* GetNameKey16(int id);
	static void     GetNameStringFromType(int weaponID, char *dest);
	static char*    FastGetNameStringFromType(int weaponID);
	static eCollectableType     GetTypeFromNameString(char* string);

	void	 Drop();
	eCollectableType GetCollectableType();
};

class CWeaponCollectable : public CCollectable {
public:
	void Spawn(RwMatrix* mat);
	void Drop();
};