#pragma once

struct CControllerState
{
	short LEFTSTICKX;
	short LEFTSTICKY;
	short RIGHTSTICKX;
	short RIGHTSTICKY;
	short LEFTSHOULDER1;
	short LEFTSHOULDER2;
	short RIGHTSHOULDER1;
	short RIGHTSHOULDER2;
	short DPADUP;
	short DPADDOWN;
	short DPADLEFT;
	short DPADRIGHT;
	short START;
	short SELECT;
	short SQUARE;
	short TRIANGLE;
	short CROSS;
	short CIRCLE;
	short LEFTSHOCK;
	short RIGHTSHOCK;
	short NETWORK_TALK;
};

struct CMouseControllerState
{
	unsigned char lmb;
	unsigned char rmb;
	unsigned char mmb;
	unsigned char wheelUp;
	unsigned char wheelDown;
	unsigned char bmx1;
	unsigned char bmx2;
	float X;
	float Y;
};

struct CKeyboardState
{
	short F[12];
	short VK_KEYS[256];
	short ESC;
	short INS;
	short DEL;
	short HOME;
	short END;
	short PGUP;
	short PGDN;
	short UP;
	short DOWN;
	short LEFT;
	short RIGHT;
	short SCROLLLOCK;
	short PAUSE;
	short NUMLOCK;
	short DIV;
	short MUL;
	short SUB;
	short ADD;
	short ENTER;
	short DECIMAL;
	short NUM1;
	short NUM2;
	short NUM3;
	short NUM4;
	short NUM5;
	short NUM6;
	short NUM7;
	short NUM8;
	short NUM9;
	short NUM0;
	short BACKSP;
	short TAB;
	short CAPSLOCK;
	short EXTENTER;
	short LSHIFT;
	short RSHIFT;
	short SHIFT;
	short LCTRL;
	short RCTRL;
	short LALT;
	short RALT;
	short LWIN;
	short RWIN;
	short APPS;
};

enum RsKeyCodes
{
	rsESC = 1000,

	rsF1 = 1001,
	rsF2 = 1002,
	rsF3 = 1003,
	rsF4 = 1004,
	rsF5 = 1005,
	rsF6 = 1006,
	rsF7 = 1007,
	rsF8 = 1008,
	rsF9 = 1009,
	rsF10 = 1010,
	rsF11 = 1011,
	rsF12 = 1012,

	rsINS = 1013,
	rsDEL = 1014,
	rsHOME = 1015,
	rsEND = 1016,
	rsPGUP = 1017,
	rsPGDN = 1018,

	rsUP = 1019,
	rsDOWN = 1020,
	rsLEFT = 1021,
	rsRIGHT = 1022,

	rsDIVIDE = 1023,
	rsTIMES = 1024,
	rsPLUS = 1025,
	rsMINUS = 1026,
	rsPADDEL = 1027,
	rsPADEND = 1028,
	rsPADDOWN = 1029,
	rsPADPGDN = 1030,
	rsPADLEFT = 1031,
	rsPAD5 = 1032,
	rsNUMLOCK = 1033,
	rsPADRIGHT = 1034,
	rsPADHOME = 1035,
	rsPADUP = 1036,
	rsPADPGUP = 1037,
	rsPADINS = 1038,
	rsPADENTER = 1039,

	rsSCROLL = 1040,
	rsPAUSE = 1041,

	rsBACKSP = 1042,
	rsTAB = 1043,
	rsCAPSLK = 1044,
	rsENTER = 1045,
	rsLSHIFT = 1046,
	rsRSHIFT = 1047,
	rsSHIFT = 1048,
	rsLCTRL = 1049,
	rsRCTRL = 1050,
	rsLALT = 1051,
	rsRALT = 1052,
	rsLWIN = 1053,
	rsRWIN = 1054,
	rsAPPS = 1055,

	rsNULL = 1056,

	rsMOUSELEFTBUTTON = 1,
	rsMOUSMIDDLEBUTTON = 2,
	rsMOUSERIGHTBUTTON = 3,
	rsMOUSEWHEELUPBUTTON = 4,
	rsMOUSEWHEELDOWNBUTTON = 5,
	rsMOUSEX1BUTTON = 6,
	rsMOUSEX2BUTTON = 7,
};

enum
{
	// taken from miss2
	PAD1 = 0,
	PAD2,

	MAX_PADS
};

class CPad
{
public:
	static CMouseControllerState &NewMouseControllerState;
	static CMouseControllerState &OldMouseControllerState;

	static CKeyboardState &NewKeyState;
	static CKeyboardState &OldKeyState;

	static CPad *GetPad(int)
	{
		static CPad pad;
		return &pad;
	}

	bool GetCharJustDown(int c) { return !!(NewKeyState.VK_KEYS[c] && !OldKeyState.VK_KEYS[c]); }
	bool GetFJustDown(int n) { return !!(NewKeyState.F[n] && !OldKeyState.F[n]); }
	bool GetEscapeJustDown() { return !!(NewKeyState.ESC && !OldKeyState.ESC); }
	bool GetInsertJustDown() { return !!(NewKeyState.INS && !OldKeyState.INS); }
	bool GetDeleteJustDown() { return !!(NewKeyState.DEL && !OldKeyState.DEL); }
	bool GetHomeJustDown() { return !!(NewKeyState.HOME && !OldKeyState.HOME); }
	bool GetEndJustDown() { return !!(NewKeyState.END && !OldKeyState.END); }
	bool GetPageUpJustDown() { return !!(NewKeyState.PGUP && !OldKeyState.PGUP); }
	bool GetPageDownJustDown() { return !!(NewKeyState.PGDN && !OldKeyState.PGDN); }
	bool GetUpJustDown() { return !!(NewKeyState.UP && !OldKeyState.UP); }
	bool GetDownJustDown() { return !!(NewKeyState.DOWN && !OldKeyState.DOWN); }
	bool GetLeftJustDown() { return !!(NewKeyState.LEFT && !OldKeyState.LEFT); }
	bool GetRightJustDown() { return !!(NewKeyState.RIGHT && !OldKeyState.RIGHT); }
	bool GetScrollLockJustDown() { return !!(NewKeyState.SCROLLLOCK && !OldKeyState.SCROLLLOCK); }
	bool GetPauseJustDown() { return !!(NewKeyState.PAUSE && !OldKeyState.PAUSE); }
	bool GetNumLockJustDown() { return !!(NewKeyState.NUMLOCK && !OldKeyState.NUMLOCK); }
	bool GetDivideJustDown() { return !!(NewKeyState.DIV && !OldKeyState.DIV); }
	bool GetTimesJustDown() { return !!(NewKeyState.MUL && !OldKeyState.MUL); }
	bool GetMinusJustDown() { return !!(NewKeyState.SUB && !OldKeyState.SUB); }
	bool GetPlusJustDown() { return !!(NewKeyState.ADD && !OldKeyState.ADD); }
	bool GetPadEnterJustDown() { return !!(NewKeyState.ENTER && !OldKeyState.ENTER); }
	bool GetPadDelJustDown() { return !!(NewKeyState.DECIMAL && !OldKeyState.DECIMAL); }
	bool GetPad1JustDown() { return !!(NewKeyState.NUM1 && !OldKeyState.NUM1); }
	bool GetPad2JustDown() { return !!(NewKeyState.NUM2 && !OldKeyState.NUM2); }
	bool GetPad3JustDown() { return !!(NewKeyState.NUM3 && !OldKeyState.NUM3); }
	bool GetPad4JustDown() { return !!(NewKeyState.NUM4 && !OldKeyState.NUM4); }
	bool GetPad5JustDown() { return !!(NewKeyState.NUM5 && !OldKeyState.NUM5); }
	bool GetPad6JustDown() { return !!(NewKeyState.NUM6 && !OldKeyState.NUM6); }
	bool GetPad7JustDown() { return !!(NewKeyState.NUM7 && !OldKeyState.NUM7); }
	bool GetPad8JustDown() { return !!(NewKeyState.NUM8 && !OldKeyState.NUM8); }
	bool GetPad9JustDown() { return !!(NewKeyState.NUM9 && !OldKeyState.NUM9); }
	bool GetPad0JustDown() { return !!(NewKeyState.NUM0 && !OldKeyState.NUM0); }
	bool GetBackspaceJustDown() { return !!(NewKeyState.BACKSP && !OldKeyState.BACKSP); }
	bool GetTabJustDown() { return !!(NewKeyState.TAB && !OldKeyState.TAB); }
	bool GetCapsLockJustDown() { return !!(NewKeyState.CAPSLOCK && !OldKeyState.CAPSLOCK); }
	bool GetReturnJustDown() { return !!(NewKeyState.EXTENTER && !OldKeyState.EXTENTER); }
	bool GetLeftShiftJustDown() { return !!(NewKeyState.LSHIFT && !OldKeyState.LSHIFT); }
	bool GetShiftJustDown() { return !!(NewKeyState.SHIFT && !OldKeyState.SHIFT); }
	bool GetRightShiftJustDown() { return !!(NewKeyState.RSHIFT && !OldKeyState.RSHIFT); }
	bool GetLeftCtrlJustDown() { return !!(NewKeyState.LCTRL && !OldKeyState.LCTRL); }
	bool GetRightCtrlJustDown() { return !!(NewKeyState.RCTRL && !OldKeyState.RCTRL); }
	bool GetLeftAltJustDown() { return !!(NewKeyState.LALT && !OldKeyState.LALT); }
	bool GetRightAltJustDown() { return !!(NewKeyState.RALT && !OldKeyState.RALT); }
	bool GetLeftWinJustDown() { return !!(NewKeyState.LWIN && !OldKeyState.LWIN); }
	bool GetRightWinJustDown() { return !!(NewKeyState.RWIN && !OldKeyState.RWIN); }
	bool GetAppsJustDown() { return !!(NewKeyState.APPS && !OldKeyState.APPS); }
	bool GetEnterJustDown() { return GetPadEnterJustDown() || GetReturnJustDown(); }
	bool GetAltJustDown() { return GetLeftAltJustDown() || GetRightAltJustDown(); }

	bool GetLeftJustUp() { return !!(!NewKeyState.LEFT && OldKeyState.LEFT); }
	bool GetRightJustUp() { return !!(!NewKeyState.RIGHT && OldKeyState.RIGHT); }
	bool GetEnterJustUp() { return GetPadEnterJustUp() || GetReturnJustUp(); }
	bool GetReturnJustUp() { return !!(!NewKeyState.EXTENTER && OldKeyState.EXTENTER); }
	bool GetPadEnterJustUp() { return !!(!NewKeyState.ENTER && OldKeyState.ENTER); }

	bool GetChar(int c) { return NewKeyState.VK_KEYS[c]; }
	bool GetF(int n) { return NewKeyState.F[n]; }
	bool GetEscape() { return NewKeyState.ESC; }
	bool GetInsert() { return NewKeyState.INS; }
	bool GetDelete() { return NewKeyState.DEL; }
	bool GetHome() { return NewKeyState.HOME; }
	bool GetEnd() { return NewKeyState.END; }
	bool GetPageUp() { return NewKeyState.PGUP; }
	bool GetPageDown() { return NewKeyState.PGDN; }
	bool GetUp() { return NewKeyState.UP; }
	bool GetDown() { return NewKeyState.DOWN; }
	bool GetLeft() { return NewKeyState.LEFT; }
	bool GetRight() { return NewKeyState.RIGHT; }
	bool GetScrollLock() { return NewKeyState.SCROLLLOCK; }
	bool GetPause() { return NewKeyState.PAUSE; }
	bool GetNumLock() { return NewKeyState.NUMLOCK; }
	bool GetDivide() { return NewKeyState.DIV; }
	bool GetTimes() { return NewKeyState.MUL; }
	bool GetMinus() { return NewKeyState.SUB; }
	bool GetPlus() { return NewKeyState.ADD; }
	bool GetPadEnter() { return NewKeyState.ENTER; } //  GetEnterJustDown
	bool GetPadDel() { return NewKeyState.DECIMAL; }
	bool GetPad1() { return NewKeyState.NUM1; }
	bool GetPad2() { return NewKeyState.NUM2; }
	bool GetPad3() { return NewKeyState.NUM3; }
	bool GetPad4() { return NewKeyState.NUM4; }
	bool GetPad5() { return NewKeyState.NUM5; }
	bool GetPad6() { return NewKeyState.NUM6; }
	bool GetPad7() { return NewKeyState.NUM7; }
	bool GetPad8() { return NewKeyState.NUM8; }
	bool GetPad9() { return NewKeyState.NUM9; }
	bool GetPad0() { return NewKeyState.NUM0; }
	bool GetBackspace() { return NewKeyState.BACKSP; }
	bool GetTab() { return NewKeyState.TAB; }
	bool GetCapsLock() { return NewKeyState.CAPSLOCK; }
	bool GetEnter() { return NewKeyState.EXTENTER; }
	bool GetLeftShift() { return NewKeyState.LSHIFT; }
	bool GetShift() { return NewKeyState.SHIFT; }
	bool GetRightShift() { return NewKeyState.RSHIFT; }
	bool GetLeftCtrl() { return NewKeyState.LCTRL; }
	bool GetRightCtrl() { return NewKeyState.RCTRL; }
	bool GetLeftAlt() { return NewKeyState.LALT; }
	bool GetRightAlt() { return NewKeyState.RALT; }
	bool GetLeftWin() { return NewKeyState.LWIN; }
	bool GetRightWin() { return NewKeyState.RWIN; }
	bool GetApps() { return NewKeyState.APPS; }
};

class CControllerConfigManager
{
public:
	bool GetIsKeyboardKeyDown(RsKeyCodes key);
	bool GetIsKeyboardKeyJustDown(RsKeyCodes key);
};

class CKeyState
{
public:
	unsigned int keyCode;
	unsigned int bDown;
	unsigned int bUp;
};

class CMouseState
{
public:
	float X;
	float Y;
	unsigned int MouseButton;
};


struct FEMouse {
	float X;
	float Y;
};


class CInputManager {
public:
	static bool& m_bInputEnabled;
	static CKeyState *m_keysPressed;
	static CMouseState &m_mouseState;

	static bool FrontendControlsAvailable();
	static bool FrontendPressedUp();
	static bool FrontendPressedDown();
	static bool FrontendPressedEscape();
	static bool FrontendButtonEnter();

	static bool FrontedMouseHovered();

	static FEMouse GetFrontendMouse();
};



