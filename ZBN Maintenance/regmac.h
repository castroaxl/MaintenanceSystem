#pragma once

#include <windows.h>

// Função para criar a janela de cadastro de máquinas
void CreateMachineWindow(HINSTANCE hInstance, HWND hwndParent);

// Procedimento da janela de cadastro de máquinas
LRESULT CALLBACK MachineWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
