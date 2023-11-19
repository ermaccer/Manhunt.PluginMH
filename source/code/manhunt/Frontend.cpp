#include "Frontend.h"
#include "core.h"

bool& CFrontend::m_bNewGame = *(bool*)0x7C86F0;
int& CFrontend::ms_devMenu = *(int*)0x7CF088;
int& CFrontend::m_gameIsRunning = *(int*)0x7D2E28;
int& CFrontend::ms_draw2d = *(int*)0x7CF0A0;
int& CFrontend::ms_misc = *(int*)0x7D34F8;
int& CFrontend::ms_menuButton = *(int*)0x7C89D4;
int& CFrontend::ms_currentMenu = *(int*)0x7C86F8;
int& CFrontend::ms_lastMenu = *(int*)0x7C8700;
float& CFrontend::ms_fTextXScale = *(float*)0x7C8720;
float& CFrontend::ms_fTextYScale = *(float*)0x7C8724;
float& CFrontend::ms_fTextAdjust = *(float*)0x7D6064;
float& CFrontend::ms_fMenuPositionY = *(float*)0x7C8728;
float& CFrontend::ms_fMenuPositionX = *(float*)0x7D6410;
int& CFrontend::ms_mouseHoverButton = *(int*)0x7C8FAC;
int& CFrontend::NumStoredHalos = *(int*)0x7D5E30;
int& CFrontend::ms_cnt = *(int*)0x7D5A1C;

CRGBA& CFrontend::ColorSet1 = *(CRGBA*)0x7D4EC8;
CRGBA& CFrontend::ColorSet2 = *(CRGBA*)0x7D4EE8;
CRGBA& CFrontend::ColorSet3 = *(CRGBA*)0x7D4EF8;
CRGBA& CFrontend::ColorSet4 = *(CRGBA*)0x7D4ED8;

CRGBA ColorSets[] = { 
	CFrontend::ColorSet1,
    CFrontend::ColorSet2,
    CFrontend::ColorSet3,
    CFrontend::ColorSet4
};


void CFrontend::SetLevel(int level)
{
	Call<0x5EF7E0, int>(level);
}

void CFrontend::ForceLevel(int level)
{
	Call<0x5EF800, int>(level);
}

void CFrontend::SetCurrentMenu(int menu)
{
	Call<0x5D7A40, int>(menu);
}

void CFrontend::DrawMenuCameraCounter(wchar_t * text)
{
	Call<0x5D5740, wchar_t*>(text);
}

void CFrontend::AddOption(wchar_t * text, float x, float y, float textScaleX, float textScaleY, int menuID)
{
	Call<0x5D55C0, wchar_t*, float, float, float, float, int>(text, x, y, textScaleX, textScaleY, menuID);
	Call<0x5D5B30, wchar_t*, float, float, float, float>(text, x, y, textScaleX, textScaleY);
}

int CFrontend::GetHoveredItem()
{
	return CallAndReturn<int,0x5DAD00>();
}

void CFrontend::SetDrawRGBA(int r, int g, int b, int a)
{
	ColorSet1 = { r,g,b,a };
	ColorSet2 = { r,g,b,a };
	ColorSet3 = { r,g,b,a };
	ColorSet4 = { r,g,b,a };
}

void CFrontend::Print8(const char * text, float x, float y, float sizex, float sizey, float unk, eFontType font)
{
	Call<0x5E55E0, const char*, float, float, float, float, float, eFontType>(text, x, y, sizex, sizey, unk, font);
}

float CFrontend::GetTextWidth8(char *text, float sizex, eFontType font)
{
	return CallAndReturn<float, 0x5E5670, const char *, float, eFontType>(text, sizex, font);
}

float CFrontend::GetFontHeight(eFontType font, float sizey)
{
	return CallAndReturn<float, 0x5FBFC0, eFontType, float>(font, sizey);
}

void CFrontend::SetMenuBackground(char * file)
{
	Call<0x5D7DD0, char*, int>(file, 0x7D38E0);
}

void CFrontend::PrintInfo(wchar_t * button1, wchar_t * button2, wchar_t * button3, wchar_t * button4)
{
	Call<0x5D5BB0, wchar_t*, wchar_t*, wchar_t*, wchar_t*>(button1, button2, button3, button4);
}

int CFrontend::GetInfoBarInput3()
{
	return *(int*)0x7C8F9C;
}

int CFrontend::GetInfoBarInput4()
{
	return *(int*)0x7C8FA0;
}

void CFrontend::PrintDebugInfo(int lineID, char * format, ...)
{
	((void(__cdecl*)(int,char*,...))0x5E5480)(lineID, format);
}

int CFrontend::GetTextureFromTXD(int txd, const char * texture)
{
	return CallAndReturn<int,0x5EA520,int,const char*>(txd, texture);
}

int CFrontend::GetLastPlayedLevel()
{
	return CallAndReturn<int, 0x5D6900>();
}

void CFrontend::ForceAndPlayLevel(int levelID, int unk)
{
	Call<0x5D6720, int, int>(levelID, unk);
}

float CFrontend::CalculateTextLen(wchar_t * text, float charScale, int byteLen)
{
	return CallAndReturn<float, 0x5E56F0, wchar_t*, float, int>(text, charScale, byteLen);
}

float CFrontend::CalculateTextLen8(char* text, float charScale, int byteLen)
{
	return CallAndReturn<float, 0x5E5670, char*, float, int>(text, charScale, byteLen);
}

void CFrontend::DrawDisc2D(CVector* pos, float scale, int red, int green, int blue, float a6)
{
	Call<0x5FB6D0, CVector*, float, int, int, int, float>(pos, scale, red, green, blue, a6);
}

void CFrontend::DrawDisc3D(CVector* pos, float scale, int red, int green, int blue, float a6)
{
	Call<0x5FBBD0, CVector*, float, int, int, int, float>(pos, scale, red, green, blue, a6);
}

void CFrontend::Set_Difficulty(int difficulty)
{
	Call<0x5D94E0, int>(difficulty);
}

RwCamera * CFrontend::GetFrontendCamera()
{
	return *(RwCamera**)0x7CF078;
}

RwCamera* CFrontend::GetSceneCamera()
{
	return *(RwCamera**)0x715B94;
}

float CFrontend::GetAspectRatio()
{
	return (float)(*(int*)0x829584 / *(int*)0x829588);
}

void CFrontend::LaserDraw(CVector* start, CVector* end)
{
	Call<0x5FA7D0, CVector*, CVector*>(start, end);
}
