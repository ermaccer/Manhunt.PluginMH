#include "eStatsManager.h"
#include "..\manhunt\core.h"
#include "..\manhunt\Frontend.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "..\manhunt\Filenames.h"
#include "..\manhunt\Scene.h"
#include "..\manhunt\Inventory.h"
#include "..\manhunt\Collectable.h"
#include "eLog.h"
#include "..\core\eSettingsManager.h"
int eStatsManager::m_numberStats[TOTAL_NUM_STATS];
float eStatsManager::m_floatStats[TOTAL_FLT_STATS];
char* eStatsManager::m_numberStatsNames[TOTAL_NUM_STATS];
bool eStatsManager::m_bDangerStatIncreased;

void eStatsManager::InitHooks()
{
	InjectHook(0x4811F6, eStatsManager::HookExecutionsStat, PATCH_CALL);
	InjectHook(0x4ECDE3, eStatsManager::HookKillsStat, PATCH_CALL);
	InjectHook(0x45E688, eStatsManager::HookPainkillersStat, PATCH_CALL);


//	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(eStatsManager::StatsWatcher), nullptr, 0, nullptr);

}

void eStatsManager::Initialize()
{

	SetDefaults();
	LoadFromFile();

	m_numberStatsNames[STAT_PLR_DEAD] = "Times Died";
	m_numberStatsNames[STAT_PLR_TRQ]  =  "Times Stunned";
	m_numberStatsNames[STAT_PLR_KICKS] = "Kicks & Body Attacks";
	m_numberStatsNames[STAT_KILLS]    = "Kills";
	m_numberStatsNames[STAT_EXECS] = "Executions";
	m_numberStatsNames[STAT_PAINKILLERS] = "Painkillers Taken";
	m_numberStatsNames[STAT_HEADS_BOOM] = "Heads Exploded";
	m_numberStatsNames[STAT_BAG_EXECS] = "Plastic Bag Executions";
	m_numberStatsNames[STAT_SHARD_EXECS] = "Glass Shard Executions";
	m_numberStatsNames[STAT_WIRE_EXECS] = "Wire Executions";
	m_numberStatsNames[STAT_SPIKE_EXECS] = "Wooden Spike Executions";
	m_numberStatsNames[STAT_AXE_EXECS] = "Axe Executions";
	m_numberStatsNames[STAT_BLACK_EXECS] = "Blackjack Executions";
	m_numberStatsNames[STAT_CROWBAR_EXECS] = "Crowbar Executions";
	m_numberStatsNames[STAT_HAMMER_EXECS] = "Hammer Executions";
	m_numberStatsNames[STAT_KNIFE_EXECS] = "Knife Executions";
	m_numberStatsNames[STAT_MACHETE_EXECS] = "Machete Executions";
	m_numberStatsNames[STAT_CLEAVER_EXECS] = "Cleaver Executions";
	m_numberStatsNames[STAT_ICEPICK_EXECS] = "Ice Pick Executions";
	m_numberStatsNames[STAT_SICKLE_EXECS] = "Sickle Executions";
	m_numberStatsNames[STAT_NIGHTSTICK_EXECS] = "Nightstick Executions";
	m_numberStatsNames[STAT_MBAT_EXECS] = "Metal Bat Executions";
	m_numberStatsNames[STAT_WBAT_EXECS] = "Wooden Bat Executions";
	m_numberStatsNames[STAT_BATBLADES_EXECS] = "Spiked Bat Executions";
	m_numberStatsNames[STAT_CHAINSAW_EXECS] = "Chainsaw Executions";

}

void eStatsManager::IncrementStat(int id)
{
	m_numberStats[id]++;
}

char * eStatsManager::GetStatName(int id)
{

	if (m_numberStatsNames[id])
		return m_numberStatsNames[id];
	else
		return nullptr;
}

int eStatsManager::GetStat(int id)
{
	return m_numberStats[id];
}

void eStatsManager::SaveToFile()
{
	std::filesystem::current_path(CFileNames::GetMyDocumentsDirectory());
	std::ofstream StatsFile("stats.dat", std::ofstream::binary);

	int header = 'STAT';
	StatsFile.write((char*)&header, sizeof(int));
	
	for (int i = 0; i < TOTAL_NUM_STATS; i++)
		StatsFile.write((char*)&m_numberStats[i], sizeof(int));
	for (int i = 0; i < TOTAL_FLT_STATS; i++)
		StatsFile.write((char*)&m_floatStats[i], sizeof(float));

	StatsFile.close();
;}

void eStatsManager::LoadFromFile()
{

	std::filesystem::current_path(CFileNames::GetMyDocumentsDirectory());
	std::ifstream pFile("stats.dat", std::ifstream::binary);

	if (!pFile)
	{
		SetDefaults();
		eLog::Message(__FUNCTION__, "Failed to load statistics from file");
	}

	eStatsFile file;
	pFile.read((char*)&file, sizeof(eStatsFile));

	if (file.header == 'STAT')
	{
		for (int i = 0; i < TOTAL_NUM_STATS; i++)
			m_numberStats[i] = file.integerStats[i];
		for (int i = 0; i < TOTAL_FLT_STATS; i++)
			m_floatStats[i] = file.m_floatStats[i];
		eLog::Message(__FUNCTION__, "Loaded statistics from file");
	}
}

void eStatsManager::SetDefaults()
{
	if (!eSettingsManager::bEnableStatsManager)
		return;

	for (int i = 0; i < TOTAL_NUM_STATS; i++)
		m_numberStats[i] = 0;
	for (int i = 0; i < TOTAL_FLT_STATS; i++)
		m_floatStats[i] = 0.0f;
}

void eStatsManager::StatsWatcher()
{
	while (true)
	{
		if (!CScene::ms_stepMode && CFrontend::m_gameIsRunning)
		{
			//if (*(int*)0x799F74)
		//	{
		//		eStatsManager::IncrementStat(STAT_PLR_DANG);
			//}
		}

	}
	Sleep(1);

}

void eStatsManager::HookKillsStat()
{

	IncrementStat(STAT_KILLS);
	Call<0x5B63A0>();
}

void eStatsManager::HookExecutionsStat()
{
	IncrementStat(STAT_EXECS);

	switch (CGameInventory::GetCurrentItem())
	{
	case CT_BAG:
		IncrementStat(STAT_BAG_EXECS);
		break;
	case CT_SHARD:
	case CT_PIGSY_SHARD:
		IncrementStat(STAT_SHARD_EXECS);
		break;
	case CT_WIRE:
	case CT_PIGSY_WIRE:
		IncrementStat(STAT_WIRE_EXECS);
		break;
	case CT_WOODEN_SPIKE:
		IncrementStat(STAT_SPIKE_EXECS);
		break;
	case CT_AXE:
		IncrementStat(STAT_AXE_EXECS);
		break;
	case CT_SMALL_BAT:
		IncrementStat(STAT_BLACK_EXECS);
		break;
	case CT_CROWBAR:
		IncrementStat(STAT_CROWBAR_EXECS);
		break;
	case CT_HAMMER:
		IncrementStat(STAT_HAMMER_EXECS);
		break;
	case CT_KNIFE:
		IncrementStat(STAT_KNIFE_EXECS);
		break;
	case CT_MACHETE:
		IncrementStat(STAT_MACHETE_EXECS);
		break;
	case CT_CLEAVER:
		IncrementStat(STAT_CLEAVER_EXECS);
		break;
	case CT_ICEPICK:
		IncrementStat(STAT_ICEPICK_EXECS);
		break;
	case CT_SICKLE:
		IncrementStat(STAT_SICKLE_EXECS);
		break;
	case CT_NIGHTSTICK:
		IncrementStat(STAT_NIGHTSTICK_EXECS);
		break;
	case CT_BASEBALL_BAT:
		IncrementStat(STAT_MBAT_EXECS);
		break;
	case CT_W_BASEBALL_BAT:
		IncrementStat(STAT_WBAT_EXECS);
		break;
	case CT_BASEBALL_BAT_BLADES:
		IncrementStat(STAT_BATBLADES_EXECS);
		break;
	case CT_CHAINSAW:
		IncrementStat(STAT_CHAINSAW_EXECS);
		break;
	}

	Call<0x5B62E0>();
}

void eStatsManager::HookPainkillersStat(int i)
{
	IncrementStat(STAT_PAINKILLERS);
	Call<0x5DFB60, int>(i);
}

