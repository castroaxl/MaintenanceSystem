#pragma once

#include <windows.h>

// Function to register the OS window class
BOOL RegisterOsClass(HINSTANCE hInstance);

// Function to create the OS registration window
void CreateOsWindow(HINSTANCE hInstance, HWND hwndParent);

// Window procedure for handling messages for the OS registration window
LRESULT CALLBACK OsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
