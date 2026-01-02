#pragma once

#include <windows.h>

// Function to register the parts window class
BOOL RegisterPartsClass(HINSTANCE hInstance);

// Function to create the machine registration window
void CreatePartsWindow(HINSTANCE hInstance, HWND hwndParent);

// Window procedure for handling messages for the parts registration window
LRESULT CALLBACK PartsWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);