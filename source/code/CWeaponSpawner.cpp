#pragma once
#include "ManhuntSDK.h"
#include "CWeaponSpawner.h"
#include "CSettingsManager.h"
using namespace ManhuntFunctions;


namespace CWeaponSpawner {
	void Knife() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Hunt_Knife_(CT)"))
			CreateInventoryItem(plr, CT_KNIFE, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Shard() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Shard_(CT)"))
			CreateInventoryItem(plr, CT_SHARD, true);
		else SetHelpMessage(L"Item does not exist here!");
	}


	void Bag() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Bag_(CT)"))
			CreateInventoryItem(plr, CT_BAG, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Wire() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Wire_(CT)"))
			CreateInventoryItem(plr, CT_WIRE, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void WireP() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Wire_Piggsy_(CT)"))
			CreateInventoryItem(plr, CT_PIGSY_WIRE, true);
		else SetHelpMessage(L"Item does not exist here!");
	}


	void Wood() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Wooden_Spike_(CT)"))
			CreateInventoryItem(plr, CT_WOODEN_SPIKE, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void ShardP() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Shard_Piggsy_(CT)"))
			CreateInventoryItem(plr, CT_PIGSY_SHARD, true);
		else SetHelpMessage(L"Item does not exist here!");
	}



	void Cleaver() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Cleaver_(CT)"))
			CreateInventoryItem(plr, CT_CLEAVER, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Crowbar() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Crowbar_(CT)"))
			CreateInventoryItem(plr, CT_CROWBAR, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Machete() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Machete_(CT)"))
			CreateInventoryItem(plr, CT_MACHETE, true);
		else SetHelpMessage(L"Item does not exist here!");
	}
	void Glock() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Glock_(CT)"))
		{
			CreateInventoryItem(plr, CT_GLOCK, true);
			GiveAmmo(150, CT_GLOCK);
		}


		else SetHelpMessage(L"Item does not exist here!");
	}

	void Deagle() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Desert_Eagle_(CT)"))
		{
			CreateInventoryItem(plr, CT_DESERT_EAGLE, true);
			GiveAmmo(150, CT_DESERT_EAGLE);
		}


		else SetHelpMessage(L"Item does not exist here!");
	}

	void Uzi() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Uzi_(CT)"))
		{
			CreateInventoryItem(plr, CT_UZI, true);
			GiveAmmo(150, CT_UZI);
		}


		else SetHelpMessage(L"Item does not exist here!");
	}


	void SawnOff() {
		CEntity* plr = FindPlayer();
		if (GetEntity("SawnOff_Shotgun_(CT)"))
		{
			CreateInventoryItem(plr, CT_SAWNOFF, true);
			GiveAmmo(150, CT_SAWNOFF);
		}


		else SetHelpMessage(L"Item does not exist here!");
	}


	void Colt() {
		CEntity* plr = FindPlayer();
		if (GetEntity("C_Commando_(CT)"))
		{
			CreateInventoryItem(plr, CT_COLT_COMMANDO, true);
			GiveAmmo(150, CT_COLT_COMMANDO);

		}


		else SetHelpMessage(L"Item does not exist here!");
	}

	void Sniper() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Sniper_Rifle_(CT)"))
		{
			CreateInventoryItem(plr, CT_SNIPER_RIFLE, true);
			GiveAmmo(150, CT_SNIPER_RIFLE);
		}


		else SetHelpMessage(L"Item does not exist here!");
	}
	void Tranq() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Tranq_Rifle_(CT)"))
		{
			CreateInventoryItem(plr, CT_TRANQ_RIFLE, true);
			GiveAmmo(150, CT_TRANQ_RIFLE);
		}


		else SetHelpMessage(L"Item does not exist here!");
	}


	void Revolver() {
		CEntity* plr = FindPlayer();
		if (GetEntity("6Shooter_(CT)"))
		{
			CreateInventoryItem(plr, CT_6SHOOTER, true);
			GiveAmmo(150, CT_6SHOOTER);
		}

		else SetHelpMessage(L"Item does not exist here!");
	}

	void Shotgun() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Shotgun_(CT)"))
		{
			CreateInventoryItem(plr, CT_SHOTGUN, true);
			GiveAmmo(150, CT_SHOTGUN);

		}

		else SetHelpMessage(L"Item does not exist here!");
	}

	void ShotgunT() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Shotgun_Torch_(CT)"))
		{
			CreateInventoryItem(plr, CT_SHOTGUN_TORCH, true);
			GiveAmmo(150, CT_SHOTGUN_TORCH);
		}

		else SetHelpMessage(L"Item does not exist here!");
	}

	void NailGun() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Nail_Gun_(CT)"))
		{
			CreateInventoryItem(plr, 89, true);
			GiveAmmo(150, CT_NAILGUN);
		}

		else SetHelpMessage(L"Item does not exist here!");
	}

	void SpikedBat() {
		CEntity* plr = FindPlayer();
		if (GetEntity("W_B_Bat_Nails_(CT)"))
			CreateInventoryItem(plr, CT_BASEBALL_BAT_BLADES, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void WBat() {
		CEntity* plr = FindPlayer();
		if (GetEntity("W_B_Bat_(CT)"))
			CreateInventoryItem(plr, CT_W_BASEBALL_BAT, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Bat() {
		CEntity* plr = FindPlayer();
		if (GetEntity("M_B_Bat_(CT)"))
			CreateInventoryItem(plr, CT_BASEBALL_BAT, true);
		else SetHelpMessage(L"Item does not exist here!");
	}
	void SmallBat() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Small_Bat_(CT)"))
			CreateInventoryItem(plr, CT_SMALL_BAT, true);
		else SetHelpMessage(L"Item does not exist here!");
	}
	void Sickle() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Sickle_(CT)"))
			CreateInventoryItem(plr, CT_SICKLE, true);
		else SetHelpMessage(L"Item does not exist here!");
	}
	void NightStick() {
		CEntity* plr = FindPlayer();
		if (GetEntity("NightStick_(CT)"))
			CreateInventoryItem(plr, CT_NIGHTSTICK, true);
		else SetHelpMessage(L"Item does not exist here!");
	}
	void Axe() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Axe_(CT)"))
			CreateInventoryItem(plr, CT_AXE, true);
		else SetHelpMessage(L"Item does not exist here!");
	}
	void IcePick() {
		CEntity* plr = FindPlayer();
		if (GetEntity("IcePick_(CT)"))
			CreateInventoryItem(plr, CT_ICEPICK, true);
		else SetHelpMessage(L"Item does not exist here!");
	}
	void Hammer() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Hammer_(CT)"))
			CreateInventoryItem(plr, 97, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Chainsaw() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Chainsaw_Player_(CT)"))
			CreateInventoryItem(plr, 108, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Brick() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Half_Brick_(CT)"))
			CreateInventoryItem(plr, CT_BRICK_HALF, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Bottle() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Bottle_(CT)"))
			CreateInventoryItem(plr, CT_BOTTLE, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Can() {
		CEntity* plr = FindPlayer();
		if (GetEntity("Can_(CT)"))
			CreateInventoryItem(plr, CT_CAN, true);
		else SetHelpMessage(L"Item does not exist here!");
	}

	void Custom1()
	{
		CEntity* plr = FindPlayer();
		if (GetEntity(SettingsMgr->szCustomWeapon[0]))
		{
			CreateInventoryItem(plr, SettingsMgr->iCustomWeapon[0], true);
			GiveAmmo(150, SettingsMgr->iCustomWeapon[0]);
		}

		else SetHelpMessage(L"Item does not exist here!");
	}

	void Custom2()
	{
		CEntity* plr = FindPlayer();
		if (GetEntity(SettingsMgr->szCustomWeapon[1]))
		{
			CreateInventoryItem(plr, SettingsMgr->iCustomWeapon[1], true);
			GiveAmmo(150, SettingsMgr->iCustomWeapon[1]);
		}

		else SetHelpMessage(L"Item does not exist here!");
	}

	void Custom3()
	{
		CEntity* plr = FindPlayer();
		if (GetEntity(SettingsMgr->szCustomWeapon[2]))
		{
			CreateInventoryItem(plr, SettingsMgr->iCustomWeapon[2], true);
			GiveAmmo(150, SettingsMgr->iCustomWeapon[2]);
		}

		else SetHelpMessage(L"Item does not exist here!");
	}

}
