#include <Windows.h>
#include <commctrl.h>
#include "finOs.h"
#include "main.h"
#include "Utils.h"

#pragma comment(lib, "comctl32.lib")

// Handle for the OS registration window
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

	HWND existingWnd = FindWindow(L"FinOsWindowClass", NULL);
	if (existingWnd) {
		SetForegroundWindow(existingWnd);
		return;
	}

	HWND hPartsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"FinOsWindowClass", L"Finalização de O.S - ZBN Manutenção",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
		hwndParent, NULL, hInstance, NULL
	);

	CenterWindow(hPartsWnd);

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

