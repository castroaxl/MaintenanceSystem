#pragma once

#include <windows.h>

// Function to create the machine registration window
void CreateFinOsWindow(HINSTANCE hInstance, HWND hwndParent);

// Window procedure for handling messages for the financial OS window
LRESULT CALLBACK FinOsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function to register the financial OS window class
BOOL RegisterFinOsClass(HINSTANCE hInstance);
