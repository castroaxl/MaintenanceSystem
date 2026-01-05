#include <Windows.h>
#include "CommCtrl.h"
#include "regOs.h"
#include "main.h"
#include "Utils.h"

#pragma comment(lib, "comctl32.lib")

// Handle for the OS registration window
static HWND hOsWnd = NULL;

BOOL RegisterOsClass(HINSTANCE hInstance) {

	// Register the OS window class.
	const wchar_t OS_CLASS[] = L"OsWindowClass";
	
	WNDCLASS wcOs = { };
	wcOs.lpfnWndProc = OsWindowProc;
	wcOs.hInstance = hInstance;
	wcOs.lpszClassName = OS_CLASS;
	wcOs.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcOs.hCursor = LoadCursor(NULL, IDC_ARROW);
	
	return RegisterClass(&wcOs);
}

// ====================================================
// FUNCTION: CreateOsWindow
// ====================================================

void CreateOsWindow(HINSTANCE hInstance, HWND hwndParent) {

	HWND existingWnd = FindWindow(L"OsWindowClass", NULL);
	if (existingWnd) {
		SetForegroundWindow(existingWnd);
		return;
	}
	
	HWND hPartsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"OsWindowClass", L"Cadastro de O.S - ZBN Manutenção",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
		hwndParent, NULL, hInstance, NULL
	);

	CenterWindow(hPartsWnd);

}

// ====================================================
// FUNCTION: OsWindowProc
// ====================================================

LRESULT CALLBACK OsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		hOsWnd = NULL; // Reset the handle when the window is destroyed
		return 0;
	
	// Handle other messages here as needed
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}