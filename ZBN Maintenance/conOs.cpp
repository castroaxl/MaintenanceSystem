#include <windows.h>
#include <CommCtrl.h>
#include "conOs.h"
#include "main.h"
#include "Utils.h"

#pragma comment(lib, "comctl32.lib")

// Handle for the consultation OS Window
static HWND hConOsWnd = NULL;

BOOL RegisterConOsClass(HINSTANCE hInstance) {
		
	// Register the consultation OS Window Class.
	const wchar_t CONOS_CLASS[] = L"ConOsWindowClass";

	WNDCLASS wcConOs = {};
	wcConOs.lpfnWndProc = ConOsWindowProc;
	wcConOs.hInstance = hInstance;
	wcConOs.lpszClassName = CONOS_CLASS;
	wcConOs.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcConOs.hCursor = LoadCursor(NULL, IDC_ARROW);

	return RegisterClass(&wcConOs);

}

// ====================================================
// FUNCTION: CreateConOsWindow
// ====================================================
void CreateConOsWindow(HINSTANCE hInstance, HWND hwndParent) {

	HWND existingWnd = FindWindow(L"ConOsWindowClass", NULL);
	if (existingWnd) {
		SetForegroundWindow(existingWnd);
		return;
	}

	HWND hPartsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"ConOsWindowClass", L"Consultar O.S - ZBN Manutenção",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
		hwndParent, NULL, hInstance, NULL
	);

	CenterWindow(hPartsWnd);

}

// ====================================================
// FUNCTION: ConOsWindowProc
// ====================================================

LRESULT CALLBACK ConOsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		hConOsWnd = NULL; // Clear the handle when the window is destroyed
		return 0;
	// Handle other messages as needed
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}