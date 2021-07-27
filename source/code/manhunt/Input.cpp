#include "Input.h"
#include "core.h"

bool& CInputManager::m_bInputEnabled = *(bool*)0x725710;

CKeyState *CInputManager::m_keysPressed = (CKeyState*)0x725698;
CMouseState &CInputManager::m_mouseState = *(CMouseState*)0x72568C;
CMouseControllerState &CPad::NewMouseControllerState = *(CMouseControllerState*)0x7E9100;
CMouseControllerState &CPad::OldMouseControllerState = *(CMouseControllerState*)0x7E9110;



bool CInputManager::FrontendControlsAvailable()
{
	return CallAndReturn<bool, 0x5D87F0>();
}

bool CInputManager::FrontendPressedUp()
{
	return CallAndReturn<bool, 0x5D8A10>();
}

bool CInputManager::FrontendPressedDown()
{
	return CallAndReturn<bool, 0x5D8AA0>();
}

bool CInputManager::FrontedMouseHovered()
{
	return CallAndReturn<bool, 0x5DACC0>();
}

FEMouse CInputManager::GetFrontendMouse()
{
	return *(FEMouse*)0x7C8FC0;
}

bool CInputManager::FrontendPressedEscape()
{
	return CallAndReturn<bool, 0x5D8C60>();
}

bool CInputManager::FrontendButtonEnter()
{
	return CallAndReturn<bool, 0x5D8B30>();
}
