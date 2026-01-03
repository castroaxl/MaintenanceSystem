#include <windows.h>
#include <CommCtrl.h>
#include "conOs.h"
#include "main.h"

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
	// Get the dimensions of the main window's client area
	RECT rcMainWindow; 
	GetClientRect(hwndParent, &rcMainWindow);
	
	// Convert the top-left point of the client area to screen coordinates
	POINT ptLeftTop = { 0, 0 };
	ClientToScreen(hwndParent, &ptLeftTop);
	
	// Define the size of the ConOs window
	int width = 800;
	int height = 600;
	
	// Check if the ConOs window already exists
	if (hConOsWnd && IsWindow(hConOsWnd)) {
		// If the window already exists, bring it to the front
		SetForegroundWindow(hConOsWnd);
		BringWindowToTop(hConOsWnd);
		return;
	}
	hConOsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"ConOsWindowClass",
		L"Consultar O.S - ZBN Manutenção",
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
// FUNCTION: ConOsWindowProc
// ====================================================

LRESULT CALLBACK ConOsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		hConOsWnd = NULL; // Clear the handle when the window is destroyed
		PostQuitMessage(0);
		return 0;
	// Handle other messages as needed
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}