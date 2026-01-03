#pragma once

#include <windows.h>

// Function to create the consultation OS Window
void CreateConOsWindow(HINSTANCE hInstance, HWND hwndParent);

// Window procedure for handling messages for the consultation OS Window
LRESULT CALLBACK ConOsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function to register the consultation OS Window class
BOOL RegisterConOsClass(HINSTANCE hInstance);
