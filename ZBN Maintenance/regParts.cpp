#include <windows.h>
#include <commctrl.h>
#include "regparts.h"
#include "main.h"

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

	// Get the dimensions of the main window's client area
	RECT rcMainWindow; 
	GetClientRect(hwndParent, &rcMainWindow);
	
	// Convert the top-left point of the client area to screen coordinates
	POINT ptLeftTop = { 0, 0 };
	ClientToScreen(hwndParent, &ptLeftTop);
	
	// Define the size of the parts window
	int width = 600;
	int height = 400;
	
	// Check if the parts window already exists
	if (hPartsWnd && IsWindow(hPartsWnd)) {
		// If the window already exists, bring it to the front
		SetForegroundWindow(hPartsWnd);
		BringWindowToTop(hPartsWnd);
		return;
	}
	hPartsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"PartsWindowClass",
		L"Cadastro de Peças - ZBN Manutenção",
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
	
	// Check if the window was created successfully
	if (!hPartsWnd) {
		MessageBox(
			NULL,
			L"Falha ao criar a janela de cadastro de peças.",
			L"Erro",
			MB_OK | MB_ICONERROR
		);
	};
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
		hPartsWnd = NULL; // Reset the handle when the window is destroyed
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}