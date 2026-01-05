#include "windows.h"
#include "resource.h"


BOOL RegisterLoginClass(HINSTANCE hInstance);
HWND CreateLoginWindow(HINSTANCE hInstance, HWND hParent);
LRESULT CALLBACK LoginWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL ValidateLogin(LPCWSTR username, LPCWSTR password);

