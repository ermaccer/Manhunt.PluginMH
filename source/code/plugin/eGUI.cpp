#include "eGUI.h"
#include "..\manhunt\Input.h"
#include "..\manhunt\Renderer.h"
#include "..\manhunt\Frontend.h"
#include <iostream>

bool eGUI::IsMouseInArea(float x, float y, float sizeX, float sizeY)
{
	FEMouse mouse = CInputManager::GetFrontendMouse();

	return (mouse.X >= x && mouse.X < x + sizeX && mouse.Y >= y && mouse.Y < y + sizeX);
}

bool eGUI::Button(char * name, float x, float y)
{
	int len = strlen(name);

	float sizeX = len * 0.0080f;
	float sizeY = 0.045f;

	// text shadow
	CFrontend::SetDrawRGBA(0, 0, 0, 255);
	CFrontend::Print8(name, x + 0.002f, y + 0.004f, 0.7f,0.7f, 0.0, FONT_TYPE_DEFAULT);
	// text
	if (IsMouseInArea(x, y, sizeX, sizeY))
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
	else
		CFrontend::SetDrawRGBA(180, 180, 180, 255);
	CFrontend::Print8(name, x, y, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);

	return IsMouseInArea(x, y, sizeX, sizeY) && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb;
}

bool eGUI::Checkbox(char * name, float x, float y, bool * value)
{
	char output[128] = {};

	sprintf(output, "%s - [%s]",name, *value == true ? "x" : " ");

	int len = strlen(output);

	float sizeX = len * 0.0080f;
	float sizeY = 0.045f;

	// text shadow
	CFrontend::SetDrawRGBA(0, 0, 0, 255);
	CFrontend::Print8(output, x + 0.002f, y + 0.004f, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);
	// text
	if (IsMouseInArea(x, y, sizeX, sizeY))
		CFrontend::SetDrawRGBA(255, 255, 255, 255);
	else
		CFrontend::SetDrawRGBA(180, 180, 180, 255);

	CFrontend::Print8(output, x, y, 0.7f, 0.7f, 0.0, FONT_TYPE_DEFAULT);


	if (IsMouseInArea(x, y, sizeX, sizeY) && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb)
		*value ^= 1;



	return IsMouseInArea(x, y, sizeX, sizeY) && CPad::NewMouseControllerState.lmb && !CPad::OldMouseControllerState.lmb;
}
