#pragma once

class CInputManager {
public:
	static bool& m_bInputEnabled;


	static bool FrontendControlsAvailable();
	static bool FrontendPressedUp();
	static bool FrontendPressedDown();
	static bool FrontendPressedEscape();
	static bool FrontendButtonEnter();

	static bool FrontedMouseHovered();
};