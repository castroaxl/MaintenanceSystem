#include "Windows.h"
#include <CommCtrl.h>
#include "login.h"
#include "main.h"

#pragma comment(lib, "Comctl32.lib")

static HWND g_hwndLogin = NULL;
BOOL g_bLoginSuccessful = FALSE;
extern HINSTANCE g_hInstance;  

BOOL RegisterLoginClass(HINSTANCE hInstance)
{
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = LoginWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"LoginWindowClass";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClass(&wc);
}

HWND CreateLoginWindow(HINSTANCE hInstance, HWND hParent)
{
    g_hwndLogin = CreateWindowEx(
        WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE,
        L"LoginWindowClass",
        L"Login - ZBN Manutenção",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        345, 300,
        hParent,
        NULL,
        hInstance,
        NULL
    );
    return g_hwndLogin;
}

BOOL ValidateLogin(LPCWSTR username, LPCWSTR password)
{
    // Para testes: usuário "admin" e senha "123"
    if (wcscmp(username, L"admin") == 0 && wcscmp(password, L"123") == 0)
    {
        return TRUE;
    }
    return FALSE;
}

LRESULT CALLBACK LoginWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hEditUser, hEditPass, hStatus;
    static HFONT hFont;

    switch (uMsg)
    {
    case WM_KEYDOWN:
        if (wParam == VK_RETURN)
        {
            SendMessage(hWnd, WM_COMMAND,
                MAKEWPARAM(IDC_LOGIN_BTN, BN_CLICKED),
                (LPARAM)GetDlgItem(hWnd, IDC_LOGIN_BTN));
            return 0;
        }
        else if (wParam == VK_ESCAPE)
        {
            SendMessage(hWnd, WM_COMMAND,
                MAKEWPARAM(IDC_CANCEL_BTN, BN_CLICKED),
                (LPARAM)GetDlgItem(hWnd, IDC_CANCEL_BTN));
            return 0;
        }
        break;

    case WM_CREATE:
    {
        hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
            L"Segoe UI");

        // Título
        HWND hTitle = CreateWindow(L"STATIC", L"ZBN Manutenção",
            WS_VISIBLE | WS_CHILD | SS_CENTER,
            10, 20, 310, 30, hWnd, NULL, g_hInstance, NULL);
        SendMessage(hTitle, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Usuário
        CreateWindow(L"STATIC", L"Usuário:",
            WS_CHILD | WS_VISIBLE,
            50, 70, 100, 25, hWnd, NULL, g_hInstance, NULL);

        hEditUser = CreateWindow(L"EDIT", L"admin",  // Pre-carregado para teste
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
            150, 70, 150, 25, hWnd, (HMENU)IDC_USERNAME, g_hInstance, NULL);
        SendMessage(hEditUser, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Senha
        CreateWindow(L"STATIC", L"Senha:",
            WS_CHILD | WS_VISIBLE,
            50, 110, 100, 25, hWnd, NULL, g_hInstance, NULL);

        hEditPass = CreateWindow(L"EDIT", L"123",  // Pre-carregado para teste
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
            150, 110, 150, 25, hWnd, (HMENU)IDC_PASSWORD, g_hInstance, NULL);
        SendMessage(hEditPass, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Botões
        CreateWindow(L"BUTTON", L"Login",
            WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
            70, 160, 100, 30, hWnd, (HMENU)IDC_LOGIN_BTN, g_hInstance, NULL);

        CreateWindow(L"BUTTON", L"Cancelar",
            WS_CHILD | WS_VISIBLE,
            180, 160, 100, 30, hWnd, (HMENU)IDC_CANCEL_BTN, g_hInstance, NULL);

        // Status
        hStatus = CreateWindow(L"STATIC", L"Digite usuário e senha",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            10, 200, 310, 25, hWnd, (HMENU)IDC_STATUS_TEXT, g_hInstance, NULL);
        SendMessage(hStatus, WM_SETFONT, (WPARAM)hFont, TRUE);

        SetFocus(hEditUser);
        return 0;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        if (wmId == IDC_LOGIN_BTN)
        {
            wchar_t username[256] = { 0 };
            wchar_t password[256] = { 0 };

            GetWindowText(GetDlgItem(hWnd, IDC_USERNAME), username, 255);
            GetWindowText(GetDlgItem(hWnd, IDC_PASSWORD), password, 255);

            if (ValidateLogin(username, password))
            {
                SetWindowText(hStatus, L"Login bem-sucedido! Redirecionando...");
                g_bLoginSuccessful = TRUE;
                DestroyWindow(hWnd);
            }
            else
            {
                SetWindowText(hStatus, L"Usuário ou senha inválidos!");
                // Limpar senha e focar no usuário
                SetWindowText(GetDlgItem(hWnd, IDC_PASSWORD), L"");
                SetFocus(GetDlgItem(hWnd, IDC_USERNAME));
            }
        }
        else if (wmId == IDC_CANCEL_BTN)
        {
            g_bLoginSuccessful = FALSE;
            DestroyWindow(hWnd);
        }
        return 0;
    }

    case WM_CLOSE:
        g_bLoginSuccessful = FALSE;
        DestroyWindow(hWnd);
        return 0;

    case WM_DESTROY:
        if (hFont)
            DeleteObject(hFont);
        return 0;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    
    return 0;
}