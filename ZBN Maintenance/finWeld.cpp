#include <Windows.h>
#include <commctrl.h>
#include "finWeld.h"
#include "main.h"
#include "Utils.h"

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

	HWND existingWnd = FindWindow(L"FinWeldWindowClass", NULL);
	if (existingWnd) {
		SetForegroundWindow(existingWnd);
		return;
	}

	HWND hPartsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"FinWeldWindowClass", L"Máquina de Solda - ZBN Manutenção",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
		hwndParent, NULL, hInstance, NULL
	);

	CenterWindow(hPartsWnd);

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

