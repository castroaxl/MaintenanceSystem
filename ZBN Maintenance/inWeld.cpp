#include <Windows.h>
#include <commctrl.h>
#include "inWeld.h"
#include "main.h"
#include "Utils.h"

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

	HWND existingWnd = FindWindow(L"InWeldWindowClass", NULL);
	if (existingWnd) {
		SetForegroundWindow(existingWnd);
		return;
	}

	HWND hPartsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"InWeldWindowClass", L"Máquina de Solda - ZBN Manutenção",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
		hwndParent, NULL, hInstance, NULL
	);

	CenterWindow(hPartsWnd);

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