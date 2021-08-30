#pragma once

class eGUI {

public:
	static bool IsMouseInArea(float x, float y, float sizeX, float sizeY);

	static bool Button(char* name, float x, float y);
	static bool Checkbox(char* name, float x, float y, bool* value);
};