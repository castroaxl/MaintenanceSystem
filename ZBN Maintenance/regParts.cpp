#include <windows.h>
#include <commctrl.h>
#include "regparts.h"
#include "main.h"
#include "Utils.h"

#pragma comment(lib, "comctl32.lib")

// handle for the parts registration window
static HWND hPartsWnd = NULL;

BOOL RegisterPartsClass(HINSTANCE hInstance) {
	
	// Register the parts window class.
	const wchar_t PARTS_CLASS[] = L"PartsWindowClass";

	WNDCLASS wcParts = { };
	wcParts.lpfnWndProc = PartsWindowProc;
	wcParts.hInstance = hInstance;
	wcParts.lpszClassName = PARTS_CLASS;
	wcParts.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcParts.hCursor = LoadCursor(NULL, IDC_ARROW);

	return RegisterClass(&wcParts);
}


// ====================================================
// FUNCTION: CreatePartsWindow
// ====================================================

void CreatePartsWindow(HINSTANCE hInstance, HWND hwndParent) {
	
	HWND existingWnd = FindWindow(L"PartsWindowClass", NULL);
	if (existingWnd) {
		SetForegroundWindow(existingWnd); 
		return;
	}

	HWND hPartsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"PartsWindowClass", L"Cadastro de Peças - ZBN Manutenção",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, 
		hwndParent, NULL, hInstance, NULL
	);

	CenterWindow(hPartsWnd);
}

// ====================================================
// FUNCTION: PartsWindowProc
// ====================================================

LRESULT CALLBACK PartsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		// Initialize controls and layout for parts registration here
		break;
	case WM_COMMAND:
		// Handle command messages from controls here
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}