
#include "App.h"

int& CApp::ms_currLevelNum = *(int*)0x75622C;
int& CApp::ms_mode = *(int*)0x755E4C;
HWND& CApp::ms_window = *(HWND*)0x824444;

void CApp::ShutdownLevel()
{
	Call<0x4D83D0>();
}

void CApp::StartupLevel()
{
	Call<0x4D8500>();
}

void CApp::SetLevel(int level)
{
	Call<0x4D8390, int>(level);
}

void CApp::SetLevel(char * folder)
{
	strcpy((char*)0x756214, folder);
}
