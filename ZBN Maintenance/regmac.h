#pragma once

#include <windows.h>

// Function to register the machine window class
BOOL RegisterMachineClass(HINSTANCE hiNSTANCE);

// Function to create the machine registration window
void CreateMachineWindow(HINSTANCE hInstance, HWND hwndParent);

// Window procedure for handling messages for the machine registration window
LRESULT CALLBACK MachineWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
