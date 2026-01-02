#include <windows.h>
#include <commctrl.h>
#include "RegMac.h"
#include "main.h"

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

	// Get the dimensions of the main window's client area
	RECT rcMainWindow; 
	GetClientRect(hwndParent, &rcMainWindow);

	// Convert the top-left point of the client area to screen coordinates
	POINT ptLeftTop = { 0, 0 };
	ClientToScreen(hwndParent, &ptLeftTop);

	// Define the size of the machine window
	int width = 600;
	int height = 400;

	// Check if the machine window already exists
	if (hMachineWnd && IsWindow(hMachineWnd)) {
		// If the window already exists, bring it to the front
		SetForegroundWindow(hMachineWnd);
		BringWindowToTop(hMachineWnd);
		return;
	}

	hMachineWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"MachineWindowClass",
		L"Cadastro de Máquinas - ZBN Manutenção",
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
	if (!hMachineWnd) {
		MessageBox(
			NULL,
			L"Falha ao criar a janela de cadastro de máquinas.",
			L"Erro",
			MB_OK | MB_ICONERROR
		);
	};

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


	
