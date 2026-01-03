#include <Windows.h>
#include <commctrl.h>
#include "finWeld.h"
#include "main.h"

#pragma comment(lib, "comctl32.lib")

// Handle for the FinWeld window
static HWND hFinWeldWnd = NULL;

BOOL RegisterFinWeldClass(HINSTANCE hInstance) {
	// Register the FinWeld window class.
	const wchar_t FINWELD_CLASS[] = L"FinWeldWindowClass";
	
	WNDCLASS wcFinWeld = { };
	wcFinWeld.lpfnWndProc = FinWeldWindowProc;
	wcFinWeld.hInstance = hInstance;
	wcFinWeld.lpszClassName = FINWELD_CLASS;
	wcFinWeld.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcFinWeld.hCursor = LoadCursor(NULL, IDC_ARROW);
	return RegisterClass(&wcFinWeld);
}

// ====================================================
// FUNCTION: CreateFinWeldWindow
// ====================================================
void CreateFinWeldWindow(HINSTANCE hInstance, HWND hwndParent) {
	// Get the dimensions of the main window's client area
	RECT rcMainWindow; 
	GetClientRect(hwndParent, &rcMainWindow);
	
	// Convert the top-left point of the client area to screen coordinates
	POINT ptLeftTop = { 0, 0 };
	ClientToScreen(hwndParent, &ptLeftTop);
	
	// Define the size of the FinWeld window
	int width = 800;
	int height = 600;
	
	// Check if the FinWeld window already exists
	if (hFinWeldWnd && IsWindow(hFinWeldWnd)) {
		// If the window already exists, bring it to the front
		SetForegroundWindow(hFinWeldWnd);
		BringWindowToTop(hFinWeldWnd);
		return;
	}
	hFinWeldWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"FinWeldWindowClass",
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
	if (hFinWeldWnd == NULL) {
		MessageBox(hwndParent, L"Falha ao criar a janela de manutenção em máquinas de solda.", L"Erro", MB_OK | MB_ICONERROR);
	}
}

// ====================================================
// FUNCTION: FinWeldWindowProc
// ====================================================
LRESULT CALLBACK FinWeldWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		hFinWeldWnd = NULL;
		return 0;
	
	// Handle other messages here as needed
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

