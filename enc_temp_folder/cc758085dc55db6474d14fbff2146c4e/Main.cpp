#include <Windows.h>
#include <iostream>
#include "Input.h"
#include <chrono>

void main()
{

	HWND hWnd = FindWindowA(NULL, "Mafia III: Definitive Edition");
	while (hWnd == NULL)
	{
		hWnd = FindWindowA(NULL, "Mafia III: Definitive Edition");
		Sleep(1000);

	}
	printf("Mafia III: Definitive Edition found!\n");
    RECT rect;
    while (true)
    {
        if (GetForegroundWindow() == hWnd)
        {
            if (GetWindowRect(hWnd, &rect))
            {
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;

                if (rect.left >= 0 && rect.top >= 0) // these values are like -32000 when game window isn't fully loaded
                {
                    std::cout << "Window Position: (" << rect.left << ", " << rect.top << ")\n";
                    std::cout << "Window Size: Width = " << width << ", Height = " << height << "\n";
                    break;
                }
				Sleep(1000);
            }
        }
       
    }
	// input loop, this allows us to get the wndproc messages
    MSG msg;
    InstallHooks(hWnd, rect);
    while (true)
    {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                break;
        }
        if (GetAsyncKeyState(VK_F4) & 0x8000)
			break;
        Sleep(0);

    }
    UninstallHooks();

}

