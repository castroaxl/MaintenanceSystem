#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <commctrl.h>
#include "main.h"
#include "resource.h"
#include "mainWin.h"
#include "login.h"
#include "regMac.h"
#include "regParts.h"
#include "regOs.h"
#include "finOs.h"
#include "conOs.h"
#include "inWeld.h"
#include "finWeld.h"


#pragma comment(lib, "comctl32.lib")

HMENU hMenu;
HINSTANCE g_hInstance;
HWND g_hwndMain;

BOOL ShowLoginDialog(HINSTANCE hInstance)
{
    if (!RegisterLoginClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela de login!", L"Erro", MB_ICONERROR);
        return FALSE;
    }

    HWND hwndLogin = CreateLoginWindow(hInstance, NULL);
    if (hwndLogin == NULL) {
        MessageBox(NULL, L"Falha ao criar janela de login!", L"Erro", MB_ICONERROR);
        return FALSE;
    }

    // Center the login dialog on the screen
    RECT rcLogin, rcDesktop;
    GetWindowRect(hwndLogin, &rcLogin);
    GetWindowRect(GetDesktopWindow(), &rcDesktop);

    int xPos = (rcDesktop.right - rcDesktop.left - (rcLogin.right - rcLogin.left)) / 2;
    int yPos = (rcDesktop.bottom - rcDesktop.top - (rcLogin.bottom - rcLogin.top)) / 2;
    SetWindowPos(hwndLogin, NULL, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

    ShowWindow(hwndLogin, SW_SHOW);
    UpdateWindow(hwndLogin);


    // Message loop for the login dialog
    MSG msg = { 0 };
  
    while (IsWindow(hwndLogin) && GetMessage(&msg, NULL, 0, 0))
    {
        if (!IsDialogMessage(hwndLogin, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    
    extern BOOL g_bLoginSuccessful;
    return g_bLoginSuccessful;
}

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
    if (!RegisterFinOsClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela de Finalização de O.S!", L"Erro", MB_ICONERROR);
        return 0;
    }
    if (!RegisterConOsClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela de Consulta de O.S!", L"Erro", MB_ICONERROR);
        return 0;
	}
    if (!RegisterInWeldClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela de manutenção em máquinas de solda!", L"Erro", MB_ICONERROR);
        return 0;
	}
    if (!RegisterFinWeldClass(hInstance)) {
        MessageBox(NULL, L"Falha ao registrar janela de finalização de manutenção em máquinas de solda!", L"Erro", MB_ICONERROR);
        return 0;
    }

    if (!ShowLoginDialog(hInstance)) {
        MessageBox(NULL, L"Login cancelado ou falhou. A aplicação será encerrada.",
            L"Login", MB_ICONINFORMATION);
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
        DWORD error = GetLastError();
        wchar_t errorMsg[256];
        wsprintf(errorMsg, L"Falha ao criar janela principal! Erro: %d", error);
        MessageBox(NULL, errorMsg, L"Erro", MB_ICONERROR);
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

