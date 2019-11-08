#pragma once
// calling
template <unsigned int address, typename... Args>
static void Call(Args... args) {
	reinterpret_cast<void(__cdecl *)(Args...)>(address)(args...);
}

template <typename Ret, unsigned int address, typename... Args>
static Ret CallAndReturn(Args... args) {
	return reinterpret_cast<Ret(__cdecl *)(Args...)>(address)(args...);
}

template <unsigned int address, typename C, typename... Args>
static void CallMethod(C _this, Args... args) {
	reinterpret_cast<void(__thiscall *)(C, Args...)>(address)(_this, args...);
}

template <typename Ret, unsigned int address, typename C, typename... Args>
static Ret CallMethodAndReturn(C _this, Args... args) {
	return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(address)(_this, args...);
}



// enums

enum eLevels {
	jury_turf, // Born Again
	derelict, // Doorway Into Hell
	der2, // Road To Ruin
	scrap, // White Trash
	scrap2, // Fuelled By Hate
	zoo, // Grounds For Assault
	zoo2, // Strapped for Cash
	mall, // View of Innocence
	church2, // Drunk Driving
	pharm_wks, // Graveyard Shift
	asylum, // Mouth of Madness
	cellblock, // Doing Time
	prison, // Kill The Rabbit
	ramirez, // Divided They Fall
	journo_streets, // Press Coverage
	subway, // Wrong Side of the Tracks
	trainyard, // Trained To Kill
	estate_ext, // Border Patrol
	mansion_int, // Key Personnel
	attic, // Deliverance
	bonus1, // Hard as Nails
	bonus2, // Monkey See, Monkey Die
	bonus3, // Brawl Game
	weasel, // Time 2 Die
};


enum eWeaponSlots {
	BACK,
	BELT_RIGHT,
	BELT_LEFT,
};

enum eItemTypes {
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
	CT_SWIPE_CARD, // did not have ct_ entry
	dummy = 87,
	CT_CHAINSAW,
	CT_NAILGUN,
	CT_WIRE,
	CT_CAN,
	CT_WOODEN_SPIKE,
	dummy2,
	CT_PIGSY_SHARD,
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
	CT_HANDYCAM

};


enum eWeatherTypes {
	CLOUDY,
	WINDY,
	RAINY,
	THUNDER,
	FOGGY,
	CLEAR,
	FREE = -1
};



enum eMenuTypes {
	MENU_EMPTY,
	MENU_CHANGE_LANGUAGE,
	MENU_EMPTY_2,
	MENU_DIFFICULTY_SELECT,
	MENU_START_LOAD_GAME,
	MENU_LOAD_GAME,
	MENU_SAVE_GAME,
	MENU_FRONTEND,
	MENU_PAUSE,
	MENU_LEVEL_SELECT,
	MENU_SETTINGS,
	MENU_AUDIO_SETTINGS,
	MENU_HEADSET_SETTINGS, // most likely
	MENU_VIDEO_SETTINGS,
	MENU_BONUS_FEATURES,
	MENU_BONUS_PREVIEW,
	MENU_GAME_COMPLETED,
	MENU_GAMMA_SETTINGS,
	MENU_CONTROL_SETTINGS,
	MENU_RESTORE_DEFAULTS,
	MENU_19,
	MENU_CREDITS,
	// pc exclusive
	MENU_REMAP_CONTROLS,
	MENU_QUIT
};

enum eCheats {
	CHEAT_RUNNER = 1,
	CHEAT_SILENCE = 2,
	CHEAT_REGENERATION = 4,
	CHEAT_EXPLODE = 8,
	CHEAT_EQUIPPED = 16,
	CHEAT_SUPERPUNCH = 32,
	CHEAT_RABBIT = 64,
	CHEAT_MONKEY = 128,
	CHEAT_INVIS = 256,
	CHEAT_PIGGSY = 512,
	CHEAT_GODMODE = 1024
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

// structs

struct CVector {
	float x, y, z;
};



struct CEntity {
	// todo: all
	char pad[20];
	float fHealth;

};

// functions

namespace ManhuntFunctions {
	void            FlashScreen(int red, int green, int blue);
	CEntity*        FindPlayer();
	void            SetHelpMessage(wchar_t* msg);
	void            CreateInventoryItem(CEntity* ent, int item, bool b1);
	void            AddAmmoToInventoryWeapon(CEntity* ent, int amount, int item);
	CVector*        GetEntityPosition(CEntity* ent);
	void            SetHealth(CEntity* ent, float health);
	void            UnlockBonusLevels();
	void            UnlockBonusFeatures();
	void            HUDToggleFlashFlags(int elem, bool state);
	int             GetLevelStars(int level);
	void            CompleteLevel();
	int             LoadTexture(int txd, const char* name);
	wchar_t*        GetText(int gxt, const char* entry);
	void            GiveAmmo(int amount, int item);
	CEntity*        GetEntity(const char* name);



	template<typename ...Args>
	void WriteDebug(int line, const char * msg, Args ...args)
	{
		Call<0x5E5480, int, const char*, Args...>(line, msg, args...);
	}
};

namespace ManhuntDebugMenu {
	void    EditVariableInt(const char* name, int* variable);
	void    EnableItemIfTrue(int* variable);
    int    CallFunction(const char* name, void* function);
};


