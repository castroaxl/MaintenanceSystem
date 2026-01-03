#include <windows.h>
#include <commctrl.h>
#include "main.h"
#include "mainWin.h"
#include "regMac.h"
#include "regParts.h"
#include "regOs.h"


#pragma comment(lib, "comctl32.lib")

static HWND hWinWnd = NULL;

BOOL RegisterMainClass(HINSTANCE hInstance) {

	// Register the main window class.
	const wchar_t MAIN_CLASS[] = L"MainWindowClass";

	WNDCLASS wcMain = { };
	wcMain.lpfnWndProc = MainWindowProc;
	wcMain.hInstance = hInstance;
	wcMain.lpszClassName = MAIN_CLASS;
	wcMain.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcMain.hCursor = LoadCursor(NULL, IDC_ARROW);

	return RegisterClass(&wcMain);
}

LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
			case IDM_REGPARTS:
				CreatePartsWindow(g_hInstance, hwnd);
				break;
			case IDM_OPORDER:
				CreateOsWindow(g_hInstance, hwnd);
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