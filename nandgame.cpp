#include <windows.h>  // Windows API の基本的なヘッダーをインクルード
#include <string>     // std::wstring を使用するためのヘッダー
#include <sstream>    // std::wostringstream を使用するためのヘッダー
#include <iostream>   // 標準入出力ストリーム用のヘッダー

// 各 UI コントロールの ID を定義
#define IDC_EDIT_X 1001           // X の入力フィールド ID
#define IDC_EDIT_Y 1002           // Y の入力フィールド ID
#define IDC_CALCULATE_BUTTON 1003 // 計算ボタンの ID
#define IDC_RESULT_LABEL 1004     // 結果表示ラベルの ID

// ウィンドウプロシージャ関数: メインのウィンドウメッセージ処理
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND editX, editY, calculateButton, resultLabel; // UI コントロールのハンドル
    static std::wstring resultText;  // 結果表示用の文字列
    WCHAR buffer[256];  // 入力値を格納するバッファ

    switch (msg) {
        case WM_CREATE: { // ウィンドウ作成時の処理
            // タイトルラベルを作成
            CreateWindowW(L"STATIC", L"NANDGAME", WS_VISIBLE | WS_CHILD | SS_CENTER,
                         20, 20, 760, 40, hwnd, NULL, NULL, NULL);
            // 説明ラベルを作成
            CreateWindowW(L"STATIC", L"1か0を入力してください", WS_VISIBLE | WS_CHILD,
                         20, 70, 760, 30, hwnd, NULL, NULL, NULL);
            
            // X の入力フィールドを作成
            editX = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
                                 20, 110, 100, 30, hwnd, (HMENU)IDC_EDIT_X, NULL, NULL);
            // Y の入力フィールドを作成
            editY = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
                                 140, 110, 100, 30, hwnd, (HMENU)IDC_EDIT_Y, NULL, NULL);
            
            // 計算ボタンを作成
            calculateButton = CreateWindowW(L"BUTTON", L"１か0を入力", WS_VISIBLE | WS_CHILD,
                                           260, 110, 100, 30, hwnd, (HMENU)IDC_CALCULATE_BUTTON, NULL, NULL);
            
            // 結果表示用のラベルを作成
            resultLabel = CreateWindowW(L"STATIC", L"", WS_VISIBLE | WS_CHILD,
                                       20, 150, 760, 260, hwnd, (HMENU)IDC_RESULT_LABEL, NULL, NULL);
            break;
        }
        
        case WM_COMMAND: { // UI イベント処理
            if (LOWORD(wParam) == IDC_CALCULATE_BUTTON) { // 計算ボタンが押された場合
                // X の値を取得
                GetWindowTextW(editX, buffer, sizeof(buffer) / sizeof(WCHAR));
                int x = _wtoi(buffer); // 文字列を整数に変換
                // Y の値を取得
                GetWindowTextW(editY, buffer, sizeof(buffer) / sizeof(WCHAR));
                int y = _wtoi(buffer);

                // 結果を計算し、出力用の文字列を作成
                std::wostringstream oss;
                oss << L"AND = " << (x * y) << L"です\n"
                    << L"NAND = " << (1 - x * y) << L"です\n"
                    << L"OR = " << (x + y - x * y) << L"です\n"
                    << L"NOR = " << (1 - x - y + x * y) << L"です\n"
                    << L"XOR = " << (x + y - 2 * x * y) << L"です\n"
                    << L"XNOR = " << (1 - x - y + 2 * x * y) << L"です\n";
                
                resultText = oss.str(); // 計算結果を保存
                SetWindowTextW(resultLabel, resultText.c_str()); // 結果を UI に反映
            }
            break;
        }
        
        case WM_DESTROY: // ウィンドウが閉じられたときの処理
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam); // デフォルト処理
    }
    return 0;
}

// アプリケーションのエントリポイント（WinMain）
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ウィンドウクラスの登録
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"NANDGAME";

    if (!RegisterClassW(&wc)) { // クラス登録に失敗した場合
        MessageBoxW(NULL, L"Failed to register window class", L"Error", MB_ICONERROR);
        return 1;
    }

    // メインウィンドウの作成
    HWND hwnd = CreateWindowExW(0, L"NANDGAME", L"NANDGAME", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT, 800, 450,
                                NULL, NULL, hInstance, NULL);
    if (!hwnd) { // ウィンドウ作成に失敗した場合
        MessageBoxW(NULL, L"Failed to create window", L"Error", MB_ICONERROR);
        return 1;
    }

    // メインメッセージループ（ウィンドウイベントの処理）
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0; // アプリケーション終了
}
