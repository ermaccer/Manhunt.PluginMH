#include "Input.h"
#include "core.h"

bool& CInputManager::m_bInputEnabled = *(bool*)0x725710;

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

bool CInputManager::FrontendPressedEscape()
{
	return CallAndReturn<bool, 0x5D8C60>();
}

bool CInputManager::FrontendButtonEnter()
{
	return CallAndReturn<bool, 0x5D8B30>();
}
