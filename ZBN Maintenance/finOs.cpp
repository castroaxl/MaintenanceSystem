#include <Windows.h>
#include <commctrl.h>
#include "finOs.h"
#include "main.h"

#pragma comment(lib, "comctl32.lib")

// // Handle for the OS registration window
static HWND hFinOsWnd = NULL;

BOOL RegisterFinOsClass(HINSTANCE hInstance) {

	// Register the OS window class.
	const wchar_t FINOS_CLASS[] = L"FinOsWindowClass";
	
	WNDCLASS wcFinOs = { };
	wcFinOs.lpfnWndProc = FinOsWindowProc;
	wcFinOs.hInstance = hInstance;
	wcFinOs.lpszClassName = FINOS_CLASS;
	wcFinOs.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcFinOs.hCursor = LoadCursor(NULL, IDC_ARROW);

	return RegisterClass(&wcFinOs);
}

// ====================================================
// FUNCTION: CreateFinOsWindow
// ====================================================

void CreateFinOsWindow(HINSTANCE hInstance, HWND hwndParent) {
	// Get the dimensions of the main window's client area
	RECT rcMainWindow; 
	GetClientRect(hwndParent, &rcMainWindow);
	
	// Convert the top-left point of the client area to screen coordinates
	POINT ptLeftTop = { 0, 0 };
	ClientToScreen(hwndParent, &ptLeftTop);
	
	// Define the size of the FinOs window
	int width = 800;
	int height = 600;
	
	// Check if the FinOs window already exists
	if (hFinOsWnd && IsWindow(hFinOsWnd)) {
		// If the window already exists, bring it to the front
		SetForegroundWindow(hFinOsWnd);
		BringWindowToTop(hFinOsWnd);
		return;
	}
	hFinOsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"FinOsWindowClass",
		L"Finalização de O.S - ZBN Manutenção",
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
// FUNCTION: FinOsWindowProc
// ====================================================

LRESULT CALLBACK FinOsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		hFinOsWnd = NULL;
		return 0;

	// Handle other messages here as needed
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

