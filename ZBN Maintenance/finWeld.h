#pragma once

#include <windows.h>

// Function to finish the welding maintenance window
void CreateFinWeldWindow(HINSTANCE hInstance, HWND hwndParent);

// Window procedure for handling messages for the welding maintenance window
LRESULT CALLBACK FinWeldWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function to register the welding maintenance window class
BOOL RegisterFinWeldClass(HINSTANCE hInstance);
