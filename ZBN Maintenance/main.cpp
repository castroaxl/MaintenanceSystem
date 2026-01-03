#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <commctrl.h>
#include "main.h"
#include "resource.h"
#include "mainWin.h"
#include "regMac.h"
#include "regParts.h"
#include "regOs.h"


#pragma comment(lib, "comctl32.lib")

HMENU hMenu;
HINSTANCE g_hInstance;
HWND g_hwndMain;

//Entry point for a Windows application
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    g_hInstance = hInstance;

	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icex);


    if (!RegisterMainClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela principal!", L"Erro", MB_ICONERROR);
        return 0;
    }

    
    if (!RegisterMachineClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela de máquinas!", L"Erro", MB_ICONERROR);
        return 0;
    }

    if (!RegisterPartsClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela de peças!", L"Erro", MB_ICONERROR);
        return 0;
    }

    if (!RegisterOsClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela de O.S!", L"Erro", MB_ICONERROR);
        return 0;
	}


    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        L"MainWindowClass",             // Window class
        L"ZBN Manutenção",              // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }
    g_hwndMain = hwnd;

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

