#include <windows.h>  // Windows API の関数と定義を含む
#include <string>     // std::wstring 用
#include <sstream>    // std::wostringstream 用
#include <iostream>   // 標準入出力ストリーム

// UI 要素を識別するためのコントロール ID
#define IDC_EDIT_X 1001           // 1つ目の入力フィールド（X 値）の ID
#define IDC_EDIT_Y 1002           // 2つ目の入力フィールド（Y 値）の ID
#define IDC_CALCULATE_BUTTON 1003 // 計算ボタンの ID
#define IDC_RESULT_LABEL 1004     // 結果表示ラベルの ID

/**
 * ウィンドウプロシージャ関数: ウィンドウメッセージを処理する
 * 
 * @param hwnd      ウィンドウハンドル
 * @param msg       メッセージ識別子
 * @param wParam    追加のメッセージ情報
 * @param lParam    追加のメッセージ情報
 * @return          メッセージ処理の結果
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // UI コントロールのハンドルと結果テキストを保持する静的変数
    static HWND editX, editY, calculateButton, resultLabel;
    static std::wstring resultText;
    WCHAR buffer[256]; // 入力フィールドのテキストを格納するバッファ
    
    // メッセージの種類ごとに処理
    switch (msg) {
        case WM_CREATE: {
            // STATIC コントロールの共通スタイル
            const DWORD staticStyle = WS_VISIBLE | WS_CHILD;
            
            // タイトルラベルを作成
            CreateWindowW(L"STATIC", L"NANDGAME", staticStyle | SS_CENTER, 
                         20, 20, 760, 40, hwnd, NULL, NULL, NULL);
            
            // 説明ラベルを作成
            CreateWindowW(L"STATIC", L"1か0を入力してください", staticStyle, 
                         20, 70, 760, 30, hwnd, NULL, NULL, NULL);
            
            // EDIT コントロールの共通スタイル
            const DWORD editStyle = WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER;
            
            // 1つ目の入力フィールド（X）を作成
            editX = CreateWindowW(L"EDIT", L"", editStyle, 
                                 20, 110, 100, 30, hwnd, (HMENU)IDC_EDIT_X, NULL, NULL);
            
            // 2つ目の入力フィールド（Y）を作成
            editY = CreateWindowW(L"EDIT", L"", editStyle, 
                                 140, 110, 100, 30, hwnd, (HMENU)IDC_EDIT_Y, NULL, NULL);
            
            // 計算ボタンを作成
            calculateButton = CreateWindowW(L"BUTTON", L"１か０を入力", WS_VISIBLE | WS_CHILD,
                                           260, 110, 100, 30, hwnd, (HMENU)IDC_CALCULATE_BUTTON, NULL, NULL);
            
            // 結果表示用のラベルを作成
            resultLabel = CreateWindowW(L"STATIC", L"", staticStyle,
                                       20, 150, 760, 260, hwnd, (HMENU)IDC_RESULT_LABEL, NULL, NULL);
            break;
        }
        
        case WM_COMMAND: {
            // ボタンクリックの処理
            if (LOWORD(wParam) == IDC_CALCULATE_BUTTON) {
                // 入力フィールドのテキストを取得し、整数に変換するラムダ関数
                auto getText = [&buffer](HWND ctrl) -> int {
                    GetWindowTextW(ctrl, buffer, sizeof(buffer) / sizeof(WCHAR));
                    return _wtoi(buffer); // 文字列を整数に変換
                };
                
                // X と Y の値を取得
                int x = getText(editX);
                int y = getText(editY);
                
                // 結果テキストを作成するためのストリーム
                std::wostringstream oss;
                
                // AND の結果（後の計算で再利用）
                int andResult = x * y;
                
                // 各論理演算の計算とフォーマット
                oss << L"AND = " << andResult << L"です\n"                // AND 演算
                    << L"NAND = " << (1 - andResult) << L"です\n"        // NAND 演算 (NOT AND)
                    << L"OR = " << (x | y) << L"です\n"                  // OR 演算 (ビット OR)
                    << L"NOR = " << (1 - (x | y)) << L"です\n"           // NOR 演算 (NOT OR)
                    << L"XOR = " << (x ^ y) << L"です\n"                 // XOR 演算 (ビット XOR)
                    << L"XNOR = " << (1 - (x ^ y)) << L"です\n";         // XNOR 演算 (NOT XOR)
                
                // 結果テキストを更新し、ラベルに表示
                resultText = oss.str();
                SetWindowTextW(resultLabel, resultText.c_str());
            }
            break;
        }
        
        case WM_DESTROY:
            // ウィンドウが閉じられたときに終了メッセージを送信
            PostQuitMessage(0);
            break;
            
        default:
            // 既定のウィンドウプロシージャに処理を委ねる
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

/**
 * Windows GUI アプリケーションのエントリポイント
 * 
 * @param hInstance      現在のアプリケーションインスタンスのハンドル
 * @param hPrevInstance  以前のインスタンス（常に NULL）
 * @param lpCmdLine      コマンドライン引数
 * @param nCmdShow       ウィンドウの表示方法を制御
 * @return               終了コード
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ウィンドウクラスの初期化
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;            // ウィンドウプロシージャ関数
    wc.hInstance = hInstance;            // アプリケーションのインスタンスハンドル
    wc.lpszClassName = L"NANDGAME";      // ウィンドウクラス名
    
    // エラーメッセージを表示するラムダ関数
    auto showError = [](const wchar_t* msg) -> int {
        MessageBoxW(NULL, msg, L"Error", MB_ICONERROR);
        return 1; // エラーコードを返す
    };
    
    // ウィンドウクラスを登録
    if (!RegisterClassW(&wc))
        return showError(L"ウィンドウクラスの登録に失敗しました");
    
    // メインウィンドウを作成
    HWND hwnd = CreateWindowExW(
        0,                              // 拡張ウィンドウスタイル
        L"NANDGAME",                    // ウィンドウクラス名
        L"NANDGAME",                    // ウィンドウタイトル
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // ウィンドウスタイル
        CW_USEDEFAULT, CW_USEDEFAULT,   // 初期位置（デフォルト）
        800, 450,                       // ウィンドウサイズ
        NULL, NULL, hInstance, NULL     // 親、メニュー、インスタンス、作成パラメータ
    );
    
    // ウィンドウの作成に失敗した場合
    if (!hwnd)
        return showError(L"ウィンドウの作成に失敗しました");
    
    // メインメッセージループ
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);         // 仮想キーのメッセージを変換
        DispatchMessage(&msg);          // ウィンドウプロシージャへメッセージを送信
    }
    
    return 0; // 正常終了
}
