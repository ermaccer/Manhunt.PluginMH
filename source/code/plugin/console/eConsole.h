#pragma once
#include <string>
#include <vector>


class eConsole {
public:
	bool m_consoleActive;
	int  m_currentCommand;
	int  m_entityID;
	std::vector<std::string> m_messages;
	std::vector<std::string> m_commands;
	std::string m_currentMessage;
	std::string m_lastCommand;

	eConsole();

	void Process();
	void PushCharacter(char chr);
	void ScrollMessage();
	void RemoveLastCharacter();
	void Execute();
	void ExecuteCommand(char* command, char* args);

	void RunScript(const char* path);



};

extern eConsole TheConsole;

void __fastcall HookAddLine(int console, char* line);
void __fastcall HookAddAIError(int modai, char* line);
void			HookConsoleInputPause();
void			InitConsoleHooks();


namespace ConsoleCommands {
	void fullbright(char* args);
	void repairPVS(char* args);
	void saveBSP(char* args);
	void farclip(char* args);
	void pos(char* args);
	void cls(char* args);
	void ambient(char* args);
	void level_load(char* args);
	void fps(char* args);
	void pvs(char* args);
	void toggleslowmo(char* args);
	void ini_reload(char* args);
	// custom
	void create(char* args);
	void giveweapon(char* args);
	void gv(char* args);
	void help(char* args);
	void sp(char* args);
	void lp(char* args);
	void tp(char* args);
	void list(char* args);
	void kill(char* args);
	void anim(char* args);
};