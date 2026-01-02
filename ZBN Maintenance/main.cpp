#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <commctrl.h>
#include "main.h"
#include "Resource.h"
#include "regmac.h"

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

    // Register the window class.
    const wchar_t INIT_CLASS[] = L"InitWindowClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = INIT_CLASS;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);


    // Register the machine window class.
    const wchar_t MACHINE_CLASS[] = L"MachineWindowClass";

    WNDCLASS wcMachine = { };
    wcMachine.lpfnWndProc = MachineWindowProc;
    wcMachine.hInstance = hInstance;
    wcMachine.lpszClassName = MACHINE_CLASS;
	wcMachine.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcMachine.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClass(&wcMachine);


    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        L"InitWindowClass",             // Window class
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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        AddMenus(hwnd);
        break;

        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int wmEvent = HIWORD(wParam);

            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                MessageBeep(MB_OK);
                MessageBox(hwnd, L"ZBN Manutenção\nVersão 1.0\nDesenvolvido por BelgaSOFT",
                    L"Sobre",
                    MB_OK | MB_ICONINFORMATION);
                break;

            case IDM_REGMAC:
                CreateMachineWindow(g_hInstance, hwnd);
                break;

            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    default:

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


void AddMenus(HWND hwnd)
{
	hMenu = CreateMenu();
    HMENU hRegisterMenu = CreateMenu();
	HMENU hOrderMenu = CreateMenu();
	HMENU hWeldMenu = CreateMenu();
	HMENU hKpiMenu = CreateMenu();

	//Register Menu Items
	AppendMenuW(hRegisterMenu, MF_STRING, IDM_REGMAC, L"Máquinas");
    AppendMenuW(hRegisterMenu, MF_STRING, IDM_REGPARTS, L"Peças");

	//Order Menu Items
	AppendMenuW(hOrderMenu, MF_STRING, IDM_OPORDER, L"Abrir O.S");
	AppendMenuW(hOrderMenu, MF_STRING, IDM_CLORDER, L"Fechar O.S");
	AppendMenuW(hOrderMenu, MF_STRING, IDM_STORDER, L"Consultar O.S");

	//Weld Menu Items
	AppendMenuW(hWeldMenu, MF_STRING, IDM_REGWELD, L"Abrir Manutenção");
	AppendMenuW(hWeldMenu, MF_STRING, IDM_REGPARTS, L"Fechar Manutenção");

	//Main Menu Items
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hRegisterMenu, L"Cadastro");
	AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hOrderMenu, L"O.S");
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hWeldMenu, L"Solda");
	AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hKpiMenu, L"KPI");
	AppendMenuW(hMenu, MF_STRING, IDM_ABOUT, L"Sobre");

    SetMenu(hwnd, hMenu);
}