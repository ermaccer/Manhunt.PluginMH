#pragma once

#define STATS_PER_PAGE 10


enum eStatsNumberIDs {
	STAT_PLR_DEAD, // done
	STAT_PLR_TRQ,// done
	STAT_PLR_KICKS,
	STAT_KILLS,// done
	STAT_EXECS,// done
	STAT_PAINKILLERS,// done
	STAT_HEADS_BOOM,
	STAT_BAG_EXECS,
	STAT_SHARD_EXECS,
	STAT_WIRE_EXECS,
	STAT_SPIKE_EXECS,
	STAT_AXE_EXECS,
	STAT_BLACK_EXECS,
	STAT_CROWBAR_EXECS,
	STAT_HAMMER_EXECS,
	STAT_KNIFE_EXECS,
	STAT_MACHETE_EXECS,
	STAT_CLEAVER_EXECS,
	STAT_ICEPICK_EXECS,
	STAT_SICKLE_EXECS,
	STAT_NIGHTSTICK_EXECS,
	STAT_MBAT_EXECS,
	STAT_WBAT_EXECS,
	STAT_BATBLADES_EXECS,
	STAT_CHAINSAW_EXECS,
	STAT_25,
	STAT_26,
	STAT_27,
	STAT_28,
	STAT_29,
	STAT_30,
	TOTAL_NUM_STATS
};


enum eStatsFloatIDs {
	STAT_RUN,
	TOTAL_FLT_STATS
};

struct eStatsFile {
	int  header;
	int  integerStats[TOTAL_NUM_STATS];
	float m_floatStats[TOTAL_FLT_STATS];
};


class eStatsManager {
private:
	static int    m_numberStats[TOTAL_NUM_STATS];
	static float  m_floatStats[TOTAL_FLT_STATS];
	static char* m_numberStatsNames[TOTAL_NUM_STATS];
	static bool  m_bDangerStatIncreased;
public:
	static void InitHooks();
	static void Initialize();
	static void IncrementStat(int id);
	static char* GetStatName(int id);
	static int   GetStat(int id);
	static void  SaveToFile();
	static void  LoadFromFile();
	static void  SetDefaults();
	static void  StatsWatcher();

	// hooks
	static void  HookKillsStat();
	static void  HookExecutionsStat();
	static void  HookPainkillersStat(int i);
};