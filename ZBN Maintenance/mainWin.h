#pragma once

#include <windows.h>

// Function to register the main window class
BOOL RegisterMainClass(HINSTANCE hInstance);

// Function to create the main application window
void CreateMainWindow(HINSTANCE hInstance, int nCmdShow);

// Window procedure for handling messages for the main application window
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function to add menus to the main window
void AddMenus(HWND hwnd);
