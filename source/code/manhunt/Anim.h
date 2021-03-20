#pragma once

enum eBodyTypes {
	BT_STAND1,
	BT_STAND2,
	BT_TURN1,
	BT_TURN2,
	BT_TURN_BIG,
	BT_MOVE_START,
	BT_MOVE1,
	BT_MOVE2,
	BT_SKID,
	BT_IDLE1,
	BT_IDLE2,
	BT_IDLELOOP1,
	BT_IDLELOOP2,
	BT_DAMAGE,
	BT_DIE,
	BT_PEEK,
	BT_PICKUP,
	BT_REACT,
	BT_KICK,
	BT_JUMP_LAUNCH,
	BT_JUMP_GLIDE,
	BT_JUMP_LAND,
	BT_CLIMABLE_BASE_MOUNT,
	BT_CLIMABLE_BASE_DISMOUNT,
	BT_CLIMABLE_MOVE,
	BT_CLIMABLE_TOP_MOUNT,
	BT_CLIMABLE_TOP_DISMOUNT,
	BT_COMBAT_STANCE_TRANSITION,
	BT_COMBAT_STANCE,
	BT_COMBAT_STANCE_FIRE1,
	BT_COMBAT_STANCE_FIRE2,
	BT_COMBAT_STANCE_FIRE_CHARGE,
	BT_COMBAT_STANCE_TURN,
	BT_WEAPON_SPECIAL,
	BT_GRAB,
	BT_GRAPPLE_ATTACK1,
	BT_GRAPPLE_ATTACK2,
	BT_GRAPPLE_ATTACK3,
	BT_GRAPPLE_BREAK,
	BT_FALL_LAUNCH,
	BT_FALL_FLAIL,
	BT_FALL_FLAIL_DEATH,
	BT_FALL_LAND,
	BT_FALL_STUN,
	BT_FALL_DAMAGE,
	BT_FALL_DIE,
	BT_FALL_DIE_DAMAGE,
	BT_FALL_GETUP,
	BT_USE,
	BT_WALL_TRANSITION,
	BT_WALL_STAND1,
	BT_WALL_STAND2,
	BT_WALL_MOVE1,
	BT_WALL_MOVE2,
	BT_WALL_PEEK,
	BT_WALL_FIRE,
	BT_DEADCARRY_PICKUP,
	BT_DEADCARRY_STAND,
	BT_DEADCARRY_TURN,
	BT_DEADCARRY_MOVE,
	BT_DEADCARRY_DROP,
	BT_PUSH,


};



class CAnimManager {
public:
	static int& ms_nAvailableAnims;

	static bool LoadAnimations(char* file);
};

class CPedBodyAnimFSM {
public:
	static void SetRequested(int body, int bodyType, int anim);
	static void Update(int body, int arg);
	static void SetStand(int body, int anim);
	static int  GetIdleAnimIdFromName(int body, const char* name);
};

class CPedTorsoAnimFSM {
public:
	static void SetRequested(int body, int bodyType, int anim);
	static void Update(int body, int arg);
	static int  GetIdleAnimIdFromName(int body, const char* name);
};