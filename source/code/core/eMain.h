#pragma once
#include <Windows.h>


namespace MainHooks {
	LRESULT CALLBACK HookedWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void HookWndProc();
}

bool IsWindowFocused();