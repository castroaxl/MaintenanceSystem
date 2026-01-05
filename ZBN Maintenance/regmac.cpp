#include <windows.h>
#include <commctrl.h>
#include "RegMac.h"
#include "main.h"
#include "Utils.h"

#pragma comment(lib, "comctl32.lib")

//handle for the machine registration window
static HWND hMachineWnd = NULL;

BOOL RegisterMachineClass(HINSTANCE hInstance) {
	
	// Register the machine window class.
	const wchar_t MACHINE_CLASS[] = L"MachineWindowClass";

	WNDCLASS wcMachine = { };
	wcMachine.lpfnWndProc = MachineWindowProc;
	wcMachine.hInstance = hInstance;
	wcMachine.lpszClassName = MACHINE_CLASS;
	wcMachine.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcMachine.hCursor = LoadCursor(NULL, IDC_ARROW);

	return RegisterClass(&wcMachine);
}



// ====================================================
// FUNCTION: CreateMachineWindow
// ====================================================
void CreateMachineWindow(HINSTANCE hInstance, HWND hwndParent) {

	HWND existingWnd = FindWindow(L"MachineWindowClass", NULL);
	if (existingWnd) {
		SetForegroundWindow(existingWnd);
		return;
	}

	HWND hPartsWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, L"MachineWindowClass", L"Cadastro de Máquinas - ZBN Manutenção",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
		hwndParent, NULL, hInstance, NULL
	);

	CenterWindow(hPartsWnd);

}
 

// ====================================================
// FUNCTION: MachineWindowProc
// ====================================================
LRESULT CALLBACK MachineWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		hMachineWnd = NULL;
		break;

	default:

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

return 0;
}


	
