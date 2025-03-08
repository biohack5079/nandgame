#include <windows.h>  // Windows API functions and definitions
#include <string>     // For std::wstring
#include <sstream>    // For std::wostringstream
#include <iostream>   // Standard I/O streams

// Control IDs for identifying UI elements
#define IDC_EDIT_X 1001           // ID for the first input field (X value)
#define IDC_EDIT_Y 1002           // ID for the second input field (Y value)
#define IDC_CALCULATE_BUTTON 1003 // ID for the calculation button
#define IDC_RESULT_LABEL 1004     // ID for the result display label

/**
 * Window procedure function that handles window messages.
 * 
 * @param hwnd      Handle to the window
 * @param msg       Message identifier
 * @param wParam    Additional message information
 * @param lParam    Additional message information
 * @return          Result of message processing
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // Static variables to store control handles and result text
    static HWND editX, editY, calculateButton, resultLabel;
    static std::wstring resultText;
    WCHAR buffer[256]; // Buffer for storing text from input fields
    
    // Process different message types
    switch (msg) {
        case WM_CREATE: {
            // Common style for static controls
            const DWORD staticStyle = WS_VISIBLE | WS_CHILD;
            
            // Create title label
            CreateWindowW(L"STATIC", L"NANDGAME", staticStyle | SS_CENTER, 
                         20, 20, 760, 40, hwnd, NULL, NULL, NULL);
            
            // Create instruction label
            CreateWindowW(L"STATIC", L"Please enter 1 or 0", staticStyle, 
                         20, 70, 760, 30, hwnd, NULL, NULL, NULL);
            
            // Common style for edit controls
            const DWORD editStyle = WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER;
            
            // Create first input field (X)
            editX = CreateWindowW(L"EDIT", L"", editStyle, 
                                 20, 110, 100, 30, hwnd, (HMENU)IDC_EDIT_X, NULL, NULL);
            
            // Create second input field (Y)
            editY = CreateWindowW(L"EDIT", L"", editStyle, 
                                 140, 110, 100, 30, hwnd, (HMENU)IDC_EDIT_Y, NULL, NULL);
            
            // Create calculation button
            calculateButton = CreateWindowW(L"BUTTON", L"Enter 1 or 0", WS_VISIBLE | WS_CHILD,
                                           260, 110, 100, 30, hwnd, (HMENU)IDC_CALCULATE_BUTTON, NULL, NULL);
            
            // Create result display label
            resultLabel = CreateWindowW(L"STATIC", L"", staticStyle,
                                       20, 150, 760, 260, hwnd, (HMENU)IDC_RESULT_LABEL, NULL, NULL);
            break;
        }
        
        case WM_COMMAND: {
            // Process button click
            if (LOWORD(wParam) == IDC_CALCULATE_BUTTON) {
                // Lambda function to retrieve and convert text from edit controls
                auto getText = [&buffer](HWND ctrl) -> int {
                    GetWindowTextW(ctrl, buffer, sizeof(buffer) / sizeof(WCHAR));
                    return _wtoi(buffer); // Convert text to integer
                };
                
                // Get X and Y values from input fields
                int x = getText(editX);
                int y = getText(editY);
                
                // Create stream for building result text
                std::wostringstream oss;
                
                // Calculate AND result once for reuse
                int andResult = x * y;
                
                // Calculate and format all logical operations
                oss << L"AND = " << andResult << L"\n"                // AND operation
                    << L"NAND = " << (1 - andResult) << L"\n"        // NAND operation (NOT AND)
                    << L"OR = " << (x | y) << L"\n"                  // OR operation using bitwise OR
                    << L"NOR = " << (1 - (x | y)) << L"\n"           // NOR operation (NOT OR)
                    << L"XOR = " << (x ^ y) << L"\n"                 // XOR operation using bitwise XOR
                    << L"XNOR = " << (1 - (x ^ y)) << L"\n";         // XNOR operation (NOT XOR)
                
                // Store result text and update display
                resultText = oss.str();
                SetWindowTextW(resultLabel, resultText.c_str());
            }
            break;
        }
        
        case WM_DESTROY:
            // Post quit message when window is closed
            PostQuitMessage(0);
            break;
            
        default:
            // Let default window procedure handle unprocessed messages
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

/**
 * Application entry point for Windows GUI applications.
 * 
 * @param hInstance      Handle to the current instance of the application
 * @param hPrevInstance  Always NULL (not used)
 * @param lpCmdLine      Command line arguments
 * @param nCmdShow       Controls how the window is shown
 * @return               Exit code
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize window class structure
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;            // Window procedure function
    wc.hInstance = hInstance;            // Application instance handle
    wc.lpszClassName = L"NANDGAME";      // Window class name
    
    // Lambda function for displaying error messages
    auto showError = [](const wchar_t* msg) -> int {
        MessageBoxW(NULL, msg, L"Error", MB_ICONERROR);
        return 1; // Return error code
    };
    
    // Register window class
    if (!RegisterClassW(&wc))
        return showError(L"Failed to register window class");
    
    // Create main window
    HWND hwnd = CreateWindowExW(
        0,                              // Extended window style
        L"NANDGAME",                    // Window class name
        L"NANDGAME",                    // Window title
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Initial position (default)
        800, 450,                       // Window size
        NULL, NULL, hInstance, NULL     // Parent, menu, instance, and creation params
    );
    
    // Check if window creation succeeded
    if (!hwnd)
        return showError(L"Failed to create window");
    
    // Main message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);         // Translate virtual key messages
        DispatchMessage(&msg);          // Dispatch message to window procedure
    }
    
    return 0; // Return success code
}
