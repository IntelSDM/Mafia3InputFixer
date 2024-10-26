#include <Windows.h>
#include <iostream>
#include <fstream>

HHOOK MouseHook;
HWND GameWindow;
RECT GameWindowSize;



LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(GetForegroundWindow() != GameWindow)
        return CallNextHookEx(MouseHook, nCode, wParam, lParam);  // only check when running the game
 
    if (nCode >= 0)
    {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
		POINT mousepos = pMouseStruct->pt;
        if (mousepos.x < GameWindowSize.left || mousepos.x > GameWindowSize.right || mousepos.y < GameWindowSize.top || mousepos.y > GameWindowSize.bottom)
            return CallNextHookEx(MouseHook, nCode, wParam, lParam); // is in window parameters 
        else
			return 0; // block the input
    }

    return CallNextHookEx(MouseHook, nCode, wParam, lParam);
}

void InstallHooks(HWND hwnd, RECT windowsize)
{

   
	GameWindow = hwnd;
	GameWindowSize = windowsize;
    MouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0);
    if (MouseHook == NULL)
    {
        std::cerr << "Failed to install mouse hook!" << std::endl;
    }
    else
    {
        std::cout << "Mouse hook installed successfully!" << std::endl;
    }
}

void UninstallHooks()
{
   
    if (MouseHook != NULL)
    {
        UnhookWindowsHookEx(MouseHook);
        std::cout << "Mouse hook uninstalled!" << std::endl;
    }
}
