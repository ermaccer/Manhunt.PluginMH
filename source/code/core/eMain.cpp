#include "eMain.h"
#include "..\manhunt\core.h"
#include "..\manhunt\App.h"
#include "..\manhunt\Frontend.h"
#include "..\manhunt\Scene.h"
#include "..\manhunt\Filenames.h"
#include "..\manhunt\Input.h"
#include "..\plugin\eStatsManager.h"
#include "..\plugin\menu\eMenu.h"
#include "..\plugin\console\eConsole.h"
#include "..\plugin\modloader\eModLoader.h"
#include "eSettingsManager.h"

WNDPROC wOriginalWndProc = nullptr;
static bool	bWindowInFocus = true;

LRESULT CALLBACK MainHooks::HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == eSettingsManager::keyToggleDebugMenu)
			CFrontend::ms_devMenu ^= 1;
	
		if (CFrontend::m_gameIsRunning)
		{
			if (wParam == VK_OEM_3)
				TheConsole.m_consoleActive ^= 1;
			
			if (wParam == eSettingsManager::keyToggleScreenshotMode)
			{
				CFrontend::ms_draw2d ^= 1;
				CScene::ms_stepMode ^= 1;
				CScene::ms_bFreeCam ^= 1;
			}
			
			if (wParam == eSettingsManager::keyToggleHUD)
				CFrontend::ms_draw2d ^= 1;


			if (wParam == TheMenu.KeyEnableMenu)
				TheMenu.OnKeyToggle();

			if (TheMenu.m_active)
			{
				if (wParam == TheMenu.KeyMenuItemDOWN)
					TheMenu.OnKeyDown();

				if (wParam == TheMenu.KeyMenuItemUP)
					TheMenu.OnKeyUp();

				if (wParam == TheMenu.KeyMenuItemLEFT)
					TheMenu.OnKeyLeft();

				if (wParam == TheMenu.KeyMenuItemRIGHT)
					TheMenu.OnKeyRight();

				if (wParam == TheMenu.KeyMenuExecute)
					TheMenu.OnKeyExecute();

				if (wParam == TheMenu.KeyMenuGoBack)
					TheMenu.OnKeyGoBack();
			}
			
		}
		break;
	case WM_CHAR:
		if (CFrontend::m_gameIsRunning)
		{
			if (TheConsole.m_consoleActive)
			{
				if (wParam == VK_BACK)
					TheConsole.RemoveLastCharacter();
				else if (wParam == VK_RETURN)
					TheConsole.Execute();
				else
					TheConsole.PushCharacter(wParam);
				
			}
		}
	break;
	case WM_KILLFOCUS:
		bWindowInFocus = false;
		break;
	case WM_SETFOCUS:
		bWindowInFocus = true;
		break;
	default:
		break;
	}

	return CallWindowProc(wOriginalWndProc, hWnd, uMsg, wParam, lParam);
}

void MainHooks::HookWndProc()
{
	wOriginalWndProc = (WNDPROC)SetWindowLongPtr(CApp::ms_window, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);
}

bool IsWindowFocused()
{
	return bWindowInFocus;
}
