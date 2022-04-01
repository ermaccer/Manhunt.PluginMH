#include "eConsole.h"
#include "..\..\manhunt\Frontend.h"
#include "..\..\manhunt\Input.h"
#include "..\..\manhunt\core.h"
#include "..\..\manhunt\EntityManager.h"
#include "..\..\manhunt\Scene.h"
#include "..\..\manhunt\SpecialFX.h"
#include "..\..\manhunt\Ped.h"
#include "..\..\manhunt\Character.h"
#include "..\MHcommon.h"
#include "..\menu\eMenu.h"
eConsole TheConsole;

using namespace ConsoleCommands;

eConsole::eConsole()
{
	m_consoleActive = false;
	m_currentCommand = 0;
	m_entityID = 0;
}

void eConsole::Process()
{

	std::string message = "> ";
	message += m_currentMessage;

	
	for (unsigned int i = 0; i < m_messages.size(); i++)
	{
		CFrontend::SetDrawRGBA(255, 255, 255, 190);
		CFrontend::Print8(m_messages[i].c_str(), 0.0, 0.85f - (0.025f * i), 0.85f, 0.85f, 0.0f, FONT_TYPE_DEBUG);
	}

	CFrontend::SetDrawRGBA(255, 255, 255, 255);
	CFrontend::Print8(message.c_str(), 0.0, 0.95f, 1.0f, 1.0f, 0.0f, FONT_TYPE_DEBUG);
}

void eConsole::PushCharacter(char chr)
{
	if (chr == 0x60)
		return;

	m_currentMessage += chr;
}

void eConsole::ScrollMessage()
{
	m_currentMessage = m_lastCommand;
}

void eConsole::RemoveLastCharacter()
{
	m_currentMessage = m_currentMessage.substr(0, m_currentMessage.size() - 1);
}

void eConsole::Execute()
{
	if (m_currentMessage.size() == 0)
		return;

	m_commands.push_back(m_currentMessage);

	char* function = "";
	char* args = "";
	char* szLine = "";

	szLine = (char*)m_currentMessage.c_str();

	m_lastCommand = m_currentMessage;

	function = strtok(szLine, " ");
	args = (function + strlen(function) + 1);

	ExecuteCommand(function, args);	
	function[0]= 0;
	args[0] = 0;

	m_currentMessage = "";
	m_currentMessage.clear();  
	m_currentCommand++;

}

void eConsole::ExecuteCommand(char * command, char * args)
{
	char* tmp = command;

	for (int i = 0; i < strlen(tmp); i++)
		tmp[i] = tolower(tmp[i]);

	std::string cmd = tmp;


	if (cmd == "help") help(args);
	else if (cmd == "pos") pos(args);
	else if (cmd == "pvs") pvs(args);
	else if (cmd == "repairpvs") repairPVS(args);
	else if (cmd == "savebsp") saveBSP(args);
	else if (cmd == "cls") cls(args);
	else if (cmd == "farclip") farclip(args);
	else if (cmd == "ambient") ambient(args);
	else if (cmd == "fullbright") fullbright(args);
	else if (cmd == "ini_reload") ini_reload(args);
	else if (cmd == "create") create(args);
	else if (cmd == "give") giveweapon(args);
	else if (cmd == "gv") gv(args);
	else if (cmd == "lp") lp(args);
	else if (cmd == "sp") sp(args);
	else if (cmd == "tp") tp(args);
	else if (cmd == "list") list(args);
	else if (cmd == "kill") kill(args);
	else if (cmd == "anim") anim(args);
	command[0] = 0;
	args[0] = 0;
}


void ConsoleCommands::fullbright(char * args)
{
	Call<0x4BBCF0, char*>(args);
}

void ConsoleCommands::repairPVS(char * args)
{
	Call<0x4BBDA0>();
}

void ConsoleCommands::saveBSP(char * args)
{
	Call<0x4BBDD0>();
}

void ConsoleCommands::farclip(char * args)
{
	Call<0x4BC9B0, char*>(args);
}

void ConsoleCommands::pos(char * args)
{
	Call<0x4BCAA0, char*>(args);
}

void ConsoleCommands::cls(char * args)
{
	TheConsole.m_currentMessage.clear();
	TheConsole.m_messages.clear();
}

void ConsoleCommands::ambient(char * args)
{
	Call<0x4BCA10, char*>(args);
}

void ConsoleCommands::level_load(char * args)
{
	Call<0x4BC070, char*>(args);
}

void ConsoleCommands::fps(char * args)
{
	Call<0x4BCB60, char*>(args);
}

void ConsoleCommands::pvs(char * args)
{
	Call<0x4BBE70, char*>(args);
}

void ConsoleCommands::toggleslowmo(char * args)
{
	Call<0x4BCD80, char*>(args);
}

void ConsoleCommands::ini_reload(char * args)
{
	Call<0x4BC127, char*>(args);
}

void ConsoleCommands::create(char * args)
{
	float x, y, z;
	char entityName[256];
	int arg = sscanf(args, "%s %f %f %f",&entityName, &x, &y, &z);

	CEntity* plr = CScene::FindPlayer();
	CVector pos;
	pos.x = plr->GetLocation()->x + 1.0f;
	pos.y = plr->GetLocation()->y;
	pos.z = plr->GetLocation()->z;
	if (arg == 4)
		pos = { x,y,z };


	CreateEntity(entityName, &pos);
}

void ConsoleCommands::giveweapon(char * args)
{
	int weaponID;
	char entityName[256];
	int argc = sscanf(args, "%s %d", &entityName, &weaponID);

	if (argc < 2)
	{
		TheConsole.m_messages.push_back("Usage: give <entity> <id>");
		return;
	}

	CEntity* entity = CEntityManager::FindInstance(entityName);

	if (!entity)
	{
		TheConsole.m_messages.push_back("Entity instance does not exist - " + (std::string)entityName);
		return;
	}

	if (entity)
		GiveWeaponToEntity(entity, weaponID);

}

void ConsoleCommands::gv(char * args)
{
	int weaponID;

	int argc = sscanf(args, "%d", &weaponID);
	if (argc < 1)
	{
		TheConsole.m_messages.push_back("Usage: gv <id>");
		return;
	}

	GiveWeaponToPlayer(weaponID);

}



void ConsoleCommands::help(char * args)
{
	cls(args);
	int pageID = 0;
	int argc = sscanf(args, "%d", &pageID);

	if (strlen(args) <= 0)
		TheConsole.m_messages.push_back("Usage: help <1-2>");

	switch (pageID)
	{
	case 1:
		TheConsole.m_messages.push_back("cls - Clears console");
		TheConsole.m_messages.push_back("pos <x> <y> <z> - Displays player position, teleports if params are specified");
		TheConsole.m_messages.push_back("ambient <r> <g> <b> - Changes ambient light, values from 0.0 to 1.0, displays current if no params");
		TheConsole.m_messages.push_back("repairpvs - repairs PVS section of BSP");
		TheConsole.m_messages.push_back("savebsp - saves world bsp to a file");
		TheConsole.m_messages.push_back("fullbright - maximizes ambient light");
		TheConsole.m_messages.push_back("ini_reload - reloads ini files");
		TheConsole.m_messages.push_back("level_load <level> - (broken)");
		break;
	case 2:
		TheConsole.m_messages.push_back("create <entity> <x> <y> <z> - Creates an entity at specified location, if none - close to player");
		TheConsole.m_messages.push_back("give <instance> <id> - Gives an entity instance specified item - item must exist");
		TheConsole.m_messages.push_back("gv <id> - Gives an item to player - item must exist");
		TheConsole.m_messages.push_back("sp - Saves position");
		TheConsole.m_messages.push_back("lp - Loads position");
		TheConsole.m_messages.push_back("tp <entity> <x> <y> <z> - Teleports entity instance to specified location, if none - close to player");
		TheConsole.m_messages.push_back("list <type> <entity> - Does something to selected entity. Type - inv, invr, data");
		TheConsole.m_messages.push_back("kill <entity>");
		TheConsole.m_messages.push_back("anim <entity> <id> - Makes entity play a body animation");
		break;
	default:
		TheConsole.m_messages.push_back("Usage: help <1-2>");
		break;
	}
}

void ConsoleCommands::sp(char * args)
{
	TheMenu.savedPosition = *CScene::FindPlayer()->GetLocation();
	TheConsole.m_messages.push_back("Position saved!");
}

void ConsoleCommands::lp(char * args)
{
	CScene::FindPlayer()->SetLocation(&TheMenu.savedPosition);
	TheConsole.m_messages.push_back("Teleported to saved position!");
}

void ConsoleCommands::tp(char * args)
{
	float x, y, z;
	char entityName[256];
	int argc = sscanf(args, "%s %f %f %f", &entityName, &x, &y, &z);
	CEntity* plr = CScene::FindPlayer();
	CVector* pos = plr->GetLocation();
	pos->x += 1.0f;
	if (argc == 4)
		*pos = { x,y,z };



	CEntity* entity = CEntityManager::FindInstance(entityName);

	if (!entity)
	{
		TheConsole.m_messages.push_back("Entity instance does not exist - " + (std::string)entityName);
		return;
	}

	if (entity)
		entity->SetLocation(pos);
}

void ConsoleCommands::list(char * args)
{
	char entityName[256] = {};
	char type[5] = {};
	int argc = sscanf(args, "%s %s", &type, &entityName);

	printf("%s %s\n", entityName, type);
	CEntity* entity = CEntityManager::FindInstance(entityName);

	if (!entity)
	{
		TheConsole.m_messages.push_back("Entity instance does not exist - " + (std::string)entityName);
		return;
	}

	if (strcmp(type, "inv") == 0)
	{
		printf("listing inv\n");
		CCharacter* chr = (CCharacter*)entity;

		CFrontend::PrintDebugInfo(1,"~cyan~INVENTORY[%s]", entityName);

		for (int i = 0; i < chr->m_pInventory->m_numSlots; i++)
		{
			CCollectable* item = chr->m_pInventory->m_inventory[i];
			if (item)
				CFrontend::PrintDebugInfo(2 + i, "Slot %d - %d", i, item->GetCollectableType());
		}
	}

	if (strcmp(type, "invr") == 0)
	{
		CPed * chr = (CPed*)entity;

		chr->SelectInventoryItem(SLOT_NULL, 0);

		if (chr->m_nCurrentSlot == SLOT_NULL)
		{
			CFrontend::PrintDebugInfo(1, "~red~REMOVED INVENTORY [%s]", entityName);

			for (int i = 1; i < chr->m_pInventory->m_numSlots; i++)
			{
				CCollectable* item = chr->m_pInventory->m_inventory[i];
				if (item)
					chr->m_pInventory->RemoveItem(item);
			}

		}
		else
			CFrontend::PrintDebugInfo(1, "~orange~UNEQUIPED WEAPONS[%s] - RUN AGAIN TO REMOVE", entityName);

	}

	if (strcmp(type, "data") == 0)
	{
		CPed * chr = (CPed*)entity;
		CFrontend::PrintDebugInfo(1, "~cyan~DATA[%s]", entityName);
		CFrontend::PrintDebugInfo(2, "Record = %s", entity->m_pTypeData->m_szRecordName);
		CFrontend::PrintDebugInfo(3, "Class = %d", entity->m_pTypeData->m_ecEntityClass);
		CFrontend::PrintDebugInfo(4, "Health = %f", entity->m_fHealth);
		CFrontend::PrintDebugInfo(5, "Position = X:%.3f Y:%.3f Z:%.3f", entity->GetLocation()->x, entity->GetLocation()->y, entity->GetLocation()->z);
		CFrontend::PrintDebugInfo(6, "Flags = 0x%x", entity->m_iEntityFlags);
	}
}

void ConsoleCommands::kill(char * args)
{
	char entityName[256] = {};
	int argc = sscanf(args, "%s", &entityName);

	CEntity* entity = CEntityManager::FindInstance(entityName);

	if (!entity)
	{
		TheConsole.m_messages.push_back("Entity instance does not exist - " + (std::string)entityName);
		return;
	}

	entity->Kill();
}

void ConsoleCommands::anim(char* args)
{
	char entityName[256] = {};
	int id = 0;

	int argc = sscanf(args, "%s %d", &entityName, &id);
	CEntity* entity = CEntityManager::FindInstance(entityName);

	if (!entity)
	{
		TheConsole.m_messages.push_back("Entity instance does not exist - " + (std::string)entityName);
		return;
	}

	if (entity)
	{
		CPed* ped = (CPed*)entity;
		CPedBodyAnimFSM* body = ped->m_pPedBodyAnimFSM;
		body->SetRequested(BT_IDLE1, id);
		body->Update(0);
	}

}

void __fastcall HookAddLine(int console, char * line)
{
	TheConsole.m_messages.push_back(line);
}

void __fastcall HookAddAIError(int modai, char * line)
{
	TheConsole.m_messages.push_back(line);
}

void __declspec(naked) HookConsoleInputPause()
{
	static int input_jump = 0x590E9F;

	if (TheConsole.m_consoleActive || TheMenu.m_active)
		CInputManager::m_bInputEnabled = 0;
	else
		CInputManager::m_bInputEnabled = 1;

	_asm jmp input_jump;

}

void InitConsoleHooks()
{
	InjectHook(0x4BCEA3, HookAddLine, PATCH_CALL);
	InjectHook(0x590E95, HookConsoleInputPause, PATCH_JUMP);
}
