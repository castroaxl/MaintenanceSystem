#include <Windows.h>
#include <commctrl.h>
#include "inWeld.h"
#include "main.h"

#pragma comment(lib, "comctl32.lib")

// Handle for the InWeld window
static HWND hInWeldWnd = NULL;

BOOL RegisterInWeldClass(HINSTANCE hInstance) {
	// Register the InWeld window class.
	const wchar_t INWELD_CLASS[] = L"InWeldWindowClass";
	
	WNDCLASS wcInWeld = { };
	wcInWeld.lpfnWndProc = InWeldWindowProc;
	wcInWeld.hInstance = hInstance;
	wcInWeld.lpszClassName = INWELD_CLASS;
	wcInWeld.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcInWeld.hCursor = LoadCursor(NULL, IDC_ARROW);
	return RegisterClass(&wcInWeld);
}

// ====================================================
// FUNCTION: CreateInWeldWindow
// ====================================================
void CreateInWeldWindow(HINSTANCE hInstance, HWND hwndParent) {
	// Get the dimensions of the main window's client area
	RECT rcMainWindow; 
	GetClientRect(hwndParent, &rcMainWindow);
	
	// Convert the top-left point of the client area to screen coordinates
	POINT ptLeftTop = { 0, 0 };
	ClientToScreen(hwndParent, &ptLeftTop);
	
	// Define the size of the InWeld window
	int width = 800;
	int height = 600;
	
	// Check if the InWeld window already exists
	if (hInWeldWnd && IsWindow(hInWeldWnd)) {
		// If the window already exists, bring it to the front
		SetForegroundWindow(hInWeldWnd);
		BringWindowToTop(hInWeldWnd);
		return;
	}
	hInWeldWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"InWeldWindowClass",
		L"Máquina de Solda - ZBN Manutenção",
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
	if (hInWeldWnd == NULL) {
		MessageBox(hwndParent, L"Falha ao criar a janela de manutenção em máquinas de solda.", L"Erro", MB_ICONERROR);
	}

}

// ====================================================
// FUNCTION: InWeldWindowProc
// ====================================================
LRESULT CALLBACK InWeldWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		hInWeldWnd = NULL; // Reset the handle when the window is destroyed
		return 0;
	
	// Handle other messages here as needed
	
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}