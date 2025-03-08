#include <windows.h>
#include <string>
#include <sstream>
#include <iostream>

#define IDC_EDIT_X 1001
#define IDC_EDIT_Y 1002
#define IDC_CALCULATE_BUTTON 1003
#define IDC_RESULT_LABEL 1004

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND editX, editY, calculateButton, resultLabel;
    static std::wstring resultText;
    WCHAR buffer[256];

    switch (msg) {
        case WM_CREATE: {
            CreateWindowW(L"STATIC", L"NANDGAME", WS_VISIBLE | WS_CHILD | SS_CENTER,
                         20, 20, 760, 40, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"STATIC", L"1か0を入力してください", WS_VISIBLE | WS_CHILD,
                         20, 70, 760, 30, hwnd, NULL, NULL, NULL);

            editX = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
                                 20, 110, 100, 30, hwnd, (HMENU)IDC_EDIT_X, NULL, NULL);
            editY = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
                                 140, 110, 100, 30, hwnd, (HMENU)IDC_EDIT_Y, NULL, NULL);

            calculateButton = CreateWindowW(L"BUTTON", L"１か0を入力", WS_VISIBLE | WS_CHILD,
                                           260, 110, 100, 30, hwnd, (HMENU)IDC_CALCULATE_BUTTON, NULL, NULL);

            resultLabel = CreateWindowW(L"STATIC", L"", WS_VISIBLE | WS_CHILD,
                                       20, 150, 760, 260, hwnd, (HMENU)IDC_RESULT_LABEL, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_CALCULATE_BUTTON) {
                GetWindowTextW(editX, buffer, sizeof(buffer) / sizeof(WCHAR));
                int x = _wtoi(buffer);
                GetWindowTextW(editY, buffer, sizeof(buffer) / sizeof(WCHAR));
                int y = _wtoi(buffer);

                std::wostringstream oss;
                oss << L"AND = " << (x * y) << L"です\n"
                    << L"NAND = " << (1 - x * y) << L"です\n"
                    << L"OR = " << (x + y - x * y) << L"です\n"
                    << L"NOR = " << (1 - x - y + x * y) << L"です\n"
                    << L"XOR = " << (x + y - 2 * x * y) << L"です\n"
                    << L"XNOR = " << (1 - x - y + 2 * x * y) << L"です\n";
                resultText = oss.str();
                SetWindowTextW(resultLabel, resultText.c_str());
            }
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"NANDGAME";

    if (!RegisterClassW(&wc)) {
        MessageBoxW(NULL, L"Failed to register window class", L"Error", MB_ICONERROR);
        return 1;
    }

    HWND hwnd = CreateWindowExW(0, L"NANDGAME", L"NANDGAME", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT, 800, 450,
                                NULL, NULL, hInstance, NULL);
    if (!hwnd) {
        MessageBoxW(NULL, L"Failed to create window", L"Error", MB_ICONERROR);
        return 1;
    }

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}