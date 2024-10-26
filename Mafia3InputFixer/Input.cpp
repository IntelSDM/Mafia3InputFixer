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
        if(mousepos.x > GameWindowSize.right-5 || mousepos.y > GameWindowSize.bottom-5 || mousepos.y < GameWindowSize.top+5 || mousepos.x < GameWindowSize.left+5)
        {

            return 1; 
           
        }
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
