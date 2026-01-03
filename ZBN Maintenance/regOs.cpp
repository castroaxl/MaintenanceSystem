#include <Windows.h>
#include "CommCtrl.h"
#include "regOs.h"
#include "main.h"

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

	// Get the dimensions of the main window's client area
	RECT rcMainWindow; 
	GetClientRect(hwndParent, &rcMainWindow);
	
	// Convert the top-left point of the client area to screen coordinates
	POINT ptLeftTop = { 0, 0 };
	ClientToScreen(hwndParent, &ptLeftTop);
	
	// Define the size of the OS window
	int width = 800;
	int height = 600;
	
	// Check if the OS window already exists
	if (hOsWnd && IsWindow(hOsWnd)) {
		// If the window already exists, bring it to the front
		SetForegroundWindow(hOsWnd);
		BringWindowToTop(hOsWnd);
		return;
	}
	hOsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"OsWindowClass",
		L"Abertura de O.S - ZBN Manutenção",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		ptLeftTop.x,
		ptLeftTop.y,
		width,
		height,
		hwndParent,
		NULL,
		hInstance,
		NULL
	);
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