#include "CNewMenu.h"
#include <Windows.h>
#include  <string>
#include "ManhuntSDK.h"
using namespace ManhuntFunctions;

float& fMenuPositionX = *(float*)0x7D6410;
float& fMenuPositionY = *(float*)0x7D640C;
float& fButtonY = *(float*)0x7C8728;
float& fTextScaleX = *(float*)0x7C8720;
float& fTextScaleY = *(float*)0x7C8724;
float& fHudStretch = *(float*)0x7D3458;

int& iMenuButton = *(int*)0x7C89D4;
int& iActiveCheat = *(int*)0x7C84A8;
int& iCheatsON = *(int*)0x7C84AC;

void CNewMenu::ProcessMainMenuHook()
{
	wchar_t* menuText, *cheatText;
	float    pos = fButtonY, pos_temp;
	int      button = iMenuButton;
	int      iLastCheat = 0;


	// draw menu thing
	Call<0x5D5740, wchar_t*>(FastGetText("MAINM"));

	// draw manhunt logo

	int mhLogo = CallAndReturn<int,0x5EA520,int,const char*>(*(int*)0x7C8704, "logo");
	DrawTexture(*(float*)0x7D6408, *(float*)0x7D6404, fHudStretch * *(float*)0x7D63FC, *(float*)0x7D6400, 180, 180, 180, 255, mhLogo);

	// play game
	menuText = GetText(0x725A38,"PLAY");
	AddMenuEntry(menuText, fMenuPositionX, fMenuPositionY, fTextScaleX, fTextScaleY,button == 0);

	// select scene
	pos += 0.40000001;
	menuText = GetText(0x725A38,"SELSCE");
	AddMenuEntry(menuText, fMenuPositionX, pos, fTextScaleX, fTextScaleY, button == 1);
	// load game
	pos += fButtonY;
	menuText = GetText(0x725A38,"LOADG");
	AddMenuEntry(menuText, fMenuPositionX, pos, fTextScaleX, fTextScaleY, button == 2);
	// settings
	pos += fButtonY;
	menuText = GetText(0x725A38,"SETT");
	AddMenuEntry(menuText, fMenuPositionX, pos, fTextScaleX, fTextScaleY, button == 3);
	// bonus
	pos += fButtonY;
	menuText = GetText(0x725A38,"BONFEA");
	AddMenuEntry(menuText, fMenuPositionX, pos, fTextScaleX, fTextScaleY, button == 4);

	// mods
	pos += fButtonY;
	menuText = L"MODIFICATIONS";
	AddMenuEntry(menuText, fMenuPositionX, pos, fTextScaleX, fTextScaleY, button == 5);

	// quit
	pos += fButtonY;
	menuText = GetText(0x725A38,"QUITPRG");
	AddMenuEntry(menuText, fMenuPositionX, pos, fTextScaleX, fTextScaleY, button == 6);
	
	if (iActiveCheat)
	{
		switch (iActiveCheat)
		{
		case CHEAT_RUNNER:
			cheatText = FastGetText("C_RUN");
			break;
		case CHEAT_SILENCE:
			cheatText = FastGetText("C_SILEN");
			break;
		case CHEAT_REGENERATION:
			cheatText = FastGetText("C_REGEN");
			break;
		case CHEAT_EXPLODE:
			cheatText = FastGetText("C_HELI");
			break;
		case CHEAT_EQUIPPED:
			cheatText = FastGetText("C_FULEQ");
			break;
		case CHEAT_SUPERPUNCH:
			cheatText = FastGetText("C_SUPUN");
			break;
		case CHEAT_RABBIT:
			cheatText = FastGetText("C_RABBI");
			break;
		case CHEAT_MONKEY:
			cheatText = FastGetText("C_MONKE");
			break;
		case CHEAT_INVIS:
			cheatText = FastGetText("C_INVIS");
			break;
		case CHEAT_PIGGSY:
			cheatText = FastGetText("C_PIGGS");
			break;
		case CHEAT_GODMODE:
			cheatText = FastGetText("C_GOD");
			break;
		default:
			break;
		}
	}

	if (iCheatsON)
		Call<0x5D5BB0, const wchar_t*, int*,int*,int*>(cheatText, &*(int*)0x7D6360, &*(int*)0x7D6360, &*(int*)0x7D6360);
}

void CNewMenu::HookExtraButton(wchar_t* text, float posx, float posy, float tsx, float tsy, int button)
{
	int but = iMenuButton;
	//AddMenuEntry(text, fMenuPositionX, posy, fTextScaleX, fTextScaleY, but == 5);

	//float pos = posy + fButtonY;
	AddMenuEntry(text, fMenuPositionX, posy, fTextScaleX, fTextScaleY, but == 5);
}
