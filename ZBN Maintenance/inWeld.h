#pragma once

#include <windows.h>

// Function to create the welding maintenance registration window
void CreateInWeldWindow(HINSTANCE hInstance, HWND hwndParent);

// Window procedure for handling messages for the welding maintenance window
LRESULT CALLBACK InWeldWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function to register the welding maintenance window class
BOOL RegisterInWeldClass(HINSTANCE hInstance);

