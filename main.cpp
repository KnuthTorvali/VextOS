#include <windows.h>
#include <tchar.h>
#include <cmath>
#include <string>

/*   CONFIG DATA   */
bool GetDataFromXvirtualMachine__ = true;
bool V86Mode__ = true;
bool LoadOSInstenseFromXvirtualMachine__ = true;
bool AllStartupInterfaceLoaded__ = true;
bool SafeLoad__ = true;
/*   CONFIG DATA   */
bool LoadStartupOS__;

bool isFullscreen = false;
bool isCursorHidden = false;
wchar_t buffer[256];
WINDOWPLACEMENT prevWindowPlacement = { sizeof(WINDOWPLACEMENT) };
DWORD prevWindowStyle;
RECT prevWindowRect;

//Xvirtual
HWND __STARTUP_MSG__;
HWND __ENTERED_MSG__;
HWND __STARTUP_OK__;
HWND __STARTUP_OK2__;
HWND __GetExcuteFiles_xVirtual__;
HWND __LOGO_Xvirtual__;
HWND __VLOGO_Xvirtual__;
HWND __SLOGO_Xvirtual__;
HWND __SELECTLINE1_OS__;
HWND __SELECTLINE2_OS__;
HWND __SELECTLINE3_OS__;
HWND __SELECTLINE4_OS__;
HWND __SELECTLINE5_OS__;
HWND __SELECTOS1_OS__;
HWND __SELECTOS2_OS__;
HWND __SELECTOS3_OS__;
HWND __SELECTCS1_OS__;
HWND __SELECTCS2_OS__;
HWND __SELECTCS3_OS__;
HWND __EMPTY_DISPLAY__;
HWND __EMPTY2_DISPLAY__;
HWND __EMPTY3_DISPLAY__;
HWND __EMPTY_DISPLAY_LOGO__;

HFONT __STARTUP_FONT__;
HFONT __LOGO_FONT_Xvirtual__;
HFONT __SELECT_FONT_Xvirtual__;
//Xvirtual


//Vext CLI
HWND __COMMAND_EDIT__;
HWND __VEXM__;
HWND __VXDEBUG__;
//Vext GUI
bool __InToVext;
HWND __VextBG;
HWND __VextControllBar;
HWND __Window1;
HWND __Window2;
HWND __Window3;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int selectedOSIndex = 0;
HWND selectOSWindows[3];

int APIENTRY wWinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
    static wchar_t szAppName[] = L"Xvirtual OS Machine";
    HWND           hWnd;
    MSG            msg;
    WNDCLASS       wndclass = {};

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        return EXIT_FAILURE;
    }

    hWnd = CreateWindowW(
        szAppName,
        L"VextOS",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

void ToggleFullscreen(HWND hwnd) {
    if (isFullscreen) {

        SetWindowLong(hwnd, GWL_STYLE, prevWindowStyle);
        SetWindowPlacement(hwnd, &prevWindowPlacement);
        SetWindowPos(hwnd, NULL, prevWindowRect.left, prevWindowRect.top, prevWindowRect.right - prevWindowRect.left, prevWindowRect.bottom - prevWindowRect.top,
            SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        isFullscreen = false;
    }
    else {

        prevWindowStyle = GetWindowLong(hwnd, GWL_STYLE);
        GetWindowPlacement(hwnd, &prevWindowPlacement);
        GetWindowRect(hwnd, &prevWindowRect);

        SetWindowLong(hwnd, GWL_STYLE, prevWindowStyle & ~WS_OVERLAPPEDWINDOW);
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        SetWindowPos(hwnd, NULL, 0, 0, screenWidth, screenHeight, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        isFullscreen = true;
    }
}

void ShowCursor(bool show) {
    if (show || __InToVext) {
        while (ShowCursor(TRUE) < 0);
        isCursorHidden = false;
    }
    else {
        while (ShowCursor(FALSE) >= 0);
        isCursorHidden = true;
    }
}

void UpdateSelectionDisplay(HDC hDC) {
    for (int i = 0; i < 3; ++i) {
        if (i == selectedOSIndex) {
            SetBkColor(hDC, RGB(100, 100, 100));
            SetWindowText(selectOSWindows[i], L"       VextOS                    Developed by XOS Team              ");
        }
        else {
            SetBkColor(hDC, RGB(50, 50, 50));
            SetWindowText(selectOSWindows[i], L"       VextOS                    Developed by XOS Team              ");
        }
    }
}

void ClearScreen(HWND hWnd) {
    HWND hChild = GetWindow(hWnd, GW_CHILD);
    while (hChild) {
        HWND hNextChild = GetWindow(hChild, GW_HWNDNEXT);
        DestroyWindow(hChild);
        hChild = hNextChild;
    }
}

void DisplayEmptyScreen(HWND hWnd) {
    // Destroy all existing child windows
    DestroyWindow(__STARTUP_MSG__);
    DestroyWindow(__ENTERED_MSG__);
    DestroyWindow(__STARTUP_OK__);
    DestroyWindow(__STARTUP_OK2__);
    DestroyWindow(__GetExcuteFiles_xVirtual__);
    DestroyWindow(__LOGO_Xvirtual__);
    DestroyWindow(__VLOGO_Xvirtual__);
    DestroyWindow(__SLOGO_Xvirtual__);
    DestroyWindow(__SELECTLINE1_OS__);
    DestroyWindow(__SELECTLINE2_OS__);
    DestroyWindow(__SELECTLINE3_OS__);
    DestroyWindow(__SELECTLINE4_OS__);
    DestroyWindow(__SELECTLINE5_OS__);
    DestroyWindow(__SELECTOS1_OS__);
    DestroyWindow(__SELECTOS2_OS__);
    DestroyWindow(__SELECTOS3_OS__);
    DestroyWindow(__SELECTCS1_OS__);
    DestroyWindow(__SELECTCS2_OS__);
    DestroyWindow(__SELECTCS3_OS__);

    // Create the "EMPTY" display

//OS Configs
    __LOGO_Xvirtual__ = CreateWindowEx(
        0,
        L"STATIC",
        L"Vect3",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        900,
        520,
        500,
        100,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __VLOGO_Xvirtual__ = CreateWindowEx(
        0,
        L"STATIC",
        L"Aect3",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        900,
        570,
        500,
        35,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    SendMessage(__LOGO_Xvirtual__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);
    SendMessage(__VLOGO_Xvirtual__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);

    Sleep(1000);

    __EMPTY_DISPLAY__ = CreateWindowEx(
        0,
        L"STATIC",
        L"Get data from VextOS",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        100,
        40,
        800,
        600,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __EMPTY2_DISPLAY__ = CreateWindowEx(
        0,
        L"STATIC",
        L"Change to color mode..",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        100,
        60,
        800,
        600,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __STARTUP_OK__ = CreateWindowEx(
        0,
        L"STATIC",
        L"[ OK ]",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        275,
        40,
        500,
        25,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __STARTUP_OK2__ = CreateWindowEx(
        0,
        L"STATIC",
        L"[ OK ]",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        275,
        60,
        500,
        25,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );
    __STARTUP_MSG__ = CreateWindowEx(
        0,
        L"STATIC",
        L"\n(㉿) Xvirtual™ copyright all reserved.\n\n[LOG]  0x0014:Hello, World!\nLoad Vect3Project...\nGetDatafromXvirtualMachine...\nProgramming by TheVect3Project\n\n\n--Global Sets--\n\n__STARTUP_MSG__ = true\n__GetDataFromXvirtualMachine__ = true\n__V86Mode__ = true\n\n\n--OS Information--\n\nOS Machine : Xvirtual\nOS version : 3.0\nOS Loader : Xvirtual\nOS Booter : Xvirtual\n\n\nGet in to VextOS....\n\n\n Type \"run VextGUI\" to run VextOS GUI",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        100,
        80,
        800,
        600,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __STARTUP_MSG__ = CreateWindowEx(
        0,
        L"STATIC",
        L"The Vect3 project by XOS team",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        880,
        620,
        500,
        100,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __STARTUP_MSG__ = CreateWindowEx(
        0,
        L"STATIC",
        L"Command >",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        100,
        605,
        500,
        100,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __COMMAND_EDIT__ = CreateWindowEx(
        0,
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        175,
        605,
        2000,
        1000,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    SendMessage(__STARTUP_MSG__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
    SendMessage(__EMPTY2_DISPLAY__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
    SendMessage(__EMPTY_DISPLAY__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);

    __InToVext = true;

}

void VextGUI(HWND hWnd, LPARAM lParam, WPARAM wParam) {

    DestroyWindow(__STARTUP_MSG__);
    DestroyWindow(__ENTERED_MSG__);
    DestroyWindow(__STARTUP_OK__);
    DestroyWindow(__STARTUP_OK2__);
    DestroyWindow(__GetExcuteFiles_xVirtual__);
    DestroyWindow(__LOGO_Xvirtual__);
    DestroyWindow(__VLOGO_Xvirtual__);
    DestroyWindow(__SLOGO_Xvirtual__);
    DestroyWindow(__SELECTLINE1_OS__);
    DestroyWindow(__SELECTLINE2_OS__);
    DestroyWindow(__SELECTLINE3_OS__);
    DestroyWindow(__SELECTLINE4_OS__);
    DestroyWindow(__SELECTLINE5_OS__);
    DestroyWindow(__SELECTOS1_OS__);
    DestroyWindow(__SELECTOS2_OS__);
    DestroyWindow(__SELECTOS3_OS__);
    DestroyWindow(__SELECTCS1_OS__);
    DestroyWindow(__SELECTCS2_OS__);
    DestroyWindow(__SELECTCS3_OS__);
    DestroyWindow(__COMMAND_EDIT__);

    __VextBG = CreateWindowEx(
        0,
        L"STATIC",
        L"",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        0,
        0,
        2500,
        1500,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __VextControllBar = CreateWindowEx(
        0,
        L"STATIC",
        L"",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        0,
        0,
        2500,
        30,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    __Window1 = CreateWindowEx(
        0,
        L"STATIC",
        L"                                             Welcome -Shell No. 1                             ● ● ●   \n Shell > sa Welcome.txt & title Welcome\n         Welcome to Vext. Powered by Xvirtual, org.\n  -----------------------------------\n  Disconnecting with shell. Exit code is 0.",
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        1300,
        630,
        500,
        250,
        hWnd,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC         hDC;
    PAINTSTRUCT ps;
    RECT        rect;
    LOGFONT lf = {};
    HWND hwndStatic = (HWND)lParam;

    switch (message)
    {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            ToggleFullscreen(hWnd);
        }
        else if (wParam == VK_DOWN && !__InToVext) {
            selectedOSIndex = (selectedOSIndex + 1) % 3;
            hDC = (HDC)wParam;
            UpdateSelectionDisplay(hDC);
        }
        else if (wParam == VK_UP && !__InToVext) {
            selectedOSIndex = (selectedOSIndex + 2) % 3;
            hDC = (HDC)wParam;
            UpdateSelectionDisplay(hDC);
        }
        else if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && !__InToVext) {
            DisplayEmptyScreen(hWnd);
        }
        else if (wParam == 'Q' && !__InToVext) {
            Sleep(2000);
            DestroyWindow(hWnd);
        } else if (wParam == 'F' && !__InToVext) {
            ClearScreen(hWnd);
            Sleep(20);
            __STARTUP_MSG__ = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0,
                0,
                500,
                1000,
                hWnd,
                NULL,
                GetModuleHandle(NULL),
                NULL
            ); SendMessage(__STARTUP_MSG__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
            __STARTUP_MSG__ = CreateWindowEx(
                0,
                L"STATIC",
                L"Fast boot mode <__FBM 01>\n[ * Warning : You may harm with system. Use FBMode careful. *]\n< Live boot. system >\nShell >set __GDX 01 \n >Loading Xvirtual Data...\nShell >wrun Bootloader fastboot op\n >Loading Boot loader...\nShell >run VextGUI\n >Loading OS...\n[OK]",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0,
                0,
                500,
                1000,
                hWnd,
                NULL,
                GetModuleHandle(NULL),
                NULL
            );
            SendMessage(__STARTUP_MSG__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
            Sleep(3000);
            ShowCursor(true);
            __InToVext=true;
            VextGUI(hWnd, lParam, wParam);
        }

    case WM_MOUSEMOVE:
        if (!isCursorHidden) {
            ShowCursor(false);
        }
        break;

    case WM_CREATE:
        __STARTUP_MSG__ = CreateWindowEx(
            0,
            L"STATIC",
            L"Welcome to Xvirtual OS Machine.",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            10,
            10,
            500,
            25,
            hWnd,
            (HMENU)0,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        __ENTERED_MSG__ = CreateWindowEx(
            0,
            L"STATIC",
            L"Get Data from Xvirtual OS Machine...",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            10,
            40,
            500,
            25,
            hWnd,
            (HMENU)1,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        __GetExcuteFiles_xVirtual__ = CreateWindowEx(
            0,
            L"STATIC",
            L"Excute Xvirtual files and change to color mode...",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            10,
            60,
            500,
            25,
            hWnd,
            (HMENU)2,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        if (!GetDataFromXvirtualMachine__) {
            MessageBox(hWnd, L"Failed to get data from Xvirtual OS Machine.", L"Error", MB_ICONERROR);
            return -1;
        }
        else {
            __STARTUP_OK__ = CreateWindowEx(
                0,
                L"STATIC",
                L"[ OK ]",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                300,
                40,
                500,
                25,
                hWnd,
                (HMENU)10,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
        }

        if (!V86Mode__) {
            MessageBox(hWnd, L"change to color mode (V86 Mode) failed.", L"Error", MB_ICONERROR);
            return -1;
        }
        else {
            __STARTUP_OK2__ = CreateWindowEx(
                0,
                L"STATIC",
                L"[ OK ]",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                300,
                60,
                500,
                25,
                hWnd,
                (HMENU)10,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
        }

        __LOGO_Xvirtual__ = CreateWindowEx(
            0,
            L"STATIC",
            L"Xvirtual",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            900,
            625,
            500,
            100,
            hWnd,
            (HMENU)7,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
        __VLOGO_Xvirtual__ = CreateWindowEx(
            0,
            L"STATIC",
            L"Xvirtual",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            900,
            675,
            500,
            40,
            hWnd,
            (HMENU)8,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        __SELECTLINE1_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"┌────────────┐",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            685,
            300,
            1000,
            50,
            hWnd,
            (HMENU)9,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
        __SELECTLINE2_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"│                              │",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            691,
            350,
            1000,
            50,
            hWnd,
            (HMENU)9,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
        __SELECTLINE3_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"│                              │",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            691,
            400,
            1000,
            50,
            hWnd,
            (HMENU)9,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
        __SELECTLINE4_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"│                              │",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            691,
            450,
            1000,
            50,
            hWnd,
            (HMENU)9,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
        __SELECTLINE5_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"└────────────┘",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            686,
            500,
            1000,
            50,
            hWnd,
            (HMENU)9,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        __SELECTOS1_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"    EMPTY                      For Xvirtual OS Machine                      ",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            750,
            380,
            1000,
            50,
            hWnd,
            (HMENU)11,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        __SELECTOS2_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"    EMPTY                      For Xvirtual OS Machine                      ",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            750,
            430,
            1000,
            50,
            hWnd,
            (HMENU)11,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        __SELECTOS3_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"      EMPTY                      For Xvirtual OS Machine                      ",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            750,
            480,
            1000,
            50,
            hWnd,
            (HMENU)11,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        selectOSWindows[0] = __SELECTOS1_OS__;
        selectOSWindows[1] = __SELECTOS2_OS__;
        selectOSWindows[2] = __SELECTOS3_OS__;
        hDC = (HDC)wParam;
        UpdateSelectionDisplay(hDC);

        if (!LoadOSInstenseFromXvirtualMachine__) {
            MessageBox(hWnd, L"Failed to load OS Instance from Xvirtual OS Machine.", L"Error", MB_ICONERROR);
            return -1;
        }

        __SELECTCS1_OS__ = CreateWindowEx(
            0,
            L"STATIC",
            L"Press \"Arrow key\" to select OS. Press\"ENTER\" Key to get in to booting mode. Press F to fast boot.",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            720,
            750,
            1500,
            50,
            hWnd,
            (HMENU)12,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );

        hwndStatic = (HWND)lParam;

        lf.lfHeight = -MulDiv(10, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72);
        lf.lfWeight = FW_NORMAL;
        __STARTUP_FONT__ = CreateFontIndirect(&lf);

        lf.lfHeight = -MulDiv(50, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72);
        lf.lfWeight = FW_NORMAL;
        __LOGO_FONT_Xvirtual__ = CreateFontIndirect(&lf);

        lf.lfHeight = -MulDiv(15, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72);
        lf.lfWeight = FW_NORMAL;
        __SELECT_FONT_Xvirtual__ = CreateFontIndirect(&lf);

        SendMessage(__STARTUP_MSG__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
        SendMessage(__ENTERED_MSG__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
        SendMessage(__STARTUP_OK__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
        SendMessage(__STARTUP_OK2__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
        SendMessage(__GetExcuteFiles_xVirtual__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
        SendMessage(__GetExcuteFiles_xVirtual__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);
        SendMessage(__SELECTCS1_OS__, WM_SETFONT, (WPARAM)__STARTUP_FONT__, TRUE);

        SendMessage(__LOGO_Xvirtual__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);
        SendMessage(__VLOGO_Xvirtual__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);
        SendMessage(__SELECTLINE1_OS__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);
        SendMessage(__SELECTLINE2_OS__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);
        SendMessage(__SELECTLINE3_OS__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);
        SendMessage(__SELECTLINE4_OS__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);
        SendMessage(__SELECTLINE5_OS__, WM_SETFONT, (WPARAM)__LOGO_FONT_Xvirtual__, TRUE);

        SendMessage(__SELECTOS1_OS__, WM_SETFONT, (WPARAM)__SELECT_FONT_Xvirtual__, TRUE);
        SendMessage(__SELECTOS3_OS__, WM_SETFONT, (WPARAM)__SELECT_FONT_Xvirtual__, TRUE);
        SendMessage(__SELECTOS2_OS__, WM_SETFONT, (WPARAM)__SELECT_FONT_Xvirtual__, TRUE);

        if (!AllStartupInterfaceLoaded__) {
            MessageBox(hWnd, L"Instance configuration failed.", L"Error", MB_ICONERROR);
            return -1;
        }

        if (!SafeLoad__) {
            MessageBox(hWnd, L"Failed to safe loading", L"Error", MB_ICONERROR);
            LoadStartupOS__ = false;
        }
        else {
            LoadStartupOS__ = true;
        }
        /*if (!LoadStartupOS__) {
            MessageBox(hWnd, L"Failed to something of OS loading.", L"Error", MB_ICONERROR);
            return -1;
        }*/

        ToggleFullscreen(hWnd);

        return 0;
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rect);
        Sleep(1000);
        DeleteObject(hDC);
        return 0;

    case WM_CTLCOLORSTATIC:
        hwndStatic = (HWND)lParam;

        if (hwndStatic == __STARTUP_OK2__) {
            hDC = (HDC)wParam;
            SetBkMode(hDC, TRANSPARENT);
            SetTextColor(hDC, RGB(0, 255, 0));
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }
        else if (hwndStatic == __LOGO_Xvirtual__) {
            hDC = (HDC)wParam;
            SetBkMode(hDC, TRANSPARENT);
            SetTextColor(hDC, RGB(180, 180, 180));
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }
        else if (hwndStatic == __VLOGO_Xvirtual__ || hwndStatic == __SELECTLINE1_OS__ || hwndStatic == __SELECTLINE2_OS__ || hwndStatic == __SELECTLINE3_OS__ || hwndStatic == __SELECTLINE4_OS__ || hwndStatic == __SELECTLINE5_OS__) {
            hDC = (HDC)wParam;
            SetBkMode(hDC, TRANSPARENT);
            SetTextColor(hDC, RGB(80, 80, 80));
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }
        else if (hwndStatic == __SELECTOS1_OS__ || hwndStatic == __SELECTOS2_OS__ || hwndStatic == __SELECTOS3_OS__) {
            hDC = (HDC)wParam;
            if (hwndStatic == selectOSWindows[selectedOSIndex]) {
                SetBkColor(hDC, RGB(100, 100, 100));
            }
            else {
                SetBkColor(hDC, RGB(50, 50, 50));
            }
            SetTextColor(hDC, RGB(200, 200, 200));
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }
        else if (hwndStatic == __VextBG) {
            hDC = (HDC)wParam;
            SetBkMode(hDC, TRANSPARENT);
            SetTextColor(hDC, RGB(0, 0, 0));
            return (LRESULT)CreateSolidBrush(RGB(235, 235, 235));
        }
        else if (hwndStatic == __VextControllBar) {
            hDC = (HDC)wParam;
            SetBkMode(hDC, TRANSPARENT);
            SetTextColor(hDC, RGB(0, 0, 0));
            return (LRESULT)CreateSolidBrush(RGB(22, 30, 25));
        }
        else if (hwndStatic == __Window1) {
            hDC = (HDC)wParam;
            SetBkMode(hDC, TRANSPARENT);
            SetTextColor(hDC, RGB(255, 255, 255));
            return (LRESULT)CreateSolidBrush(RGB(22, 30, 25));
        }
        else {
            hDC = (HDC)wParam;
            SetBkMode(hDC, TRANSPARENT);
            SetTextColor(hDC, RGB(255, 255, 255));
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }
        return 0;

    case WM_CTLCOLOREDIT:
        hwndStatic = (HWND)lParam;
        if (hwndStatic == __COMMAND_EDIT__) {
            hDC = (HDC)wParam;
            SetBkColor(hDC, RGB(0, 0, 0));
            SetTextColor(hDC, RGB(0, 255, 0));
            return (LRESULT)GetStockObject(NULL_BRUSH);
        }
        return 0;

    case WM_DESTROY:
        DeleteObject(__STARTUP_FONT__);
        DeleteObject(__LOGO_FONT_Xvirtual__);
        DeleteObject(__SELECT_FONT_Xvirtual__);
        PostQuitMessage(0);
        return 0;

    case WM_SIZE:
        if (isFullscreen) {
            // Ensure the window stays in fullscreen mode when resized
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            SetWindowPos(hWnd, NULL, 0, 0, screenWidth, screenHeight, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
        break;
    case WM_COMMAND:
        GetWindowText(__COMMAND_EDIT__, buffer, 256);

        if (wcscmp(buffer, L"run VextGUI") == 0)
        {
            SetWindowText(__STARTUP_MSG__, L"Command >\nCommand >Now loading...");
            Sleep(2000);
            SetWindowText(__STARTUP_MSG__, L"Command >\nCommand >Now loading...\n[OK]");
            Sleep(500);
            ClearScreen(hWnd);
            if (!__InToVext) {
                MessageBox(hWnd, L"Failed to get in to VextGUI. Please edit __IVT (00) to (01).", L"Error", MB_ICONERROR);
                return -1;
            }
            else {
                ShowCursor(true);
                VextGUI(hWnd, lParam, wParam);
            }
        }
        else if (wcscmp(buffer, L"set __ITV 00") == 0) {
            __InToVext = false;

            __VEXM__ = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0,
                0,
                0,
                0,
                hWnd,
                NULL,
                GetModuleHandle(NULL),
                NULL
            ); CloseWindow(__VEXM__); SetWindowText(__VEXM__, L"< __ITV : 00 >"); SetWindowText(__COMMAND_EDIT__, L"");
        }
        else if (wcscmp(buffer, L"set __ITV 01") == 0) {
            SetWindowText(__COMMAND_EDIT__, L"");
            DestroyWindow(__VEXM__);
            __InToVext = true;
        }
        else if (wcscmp(buffer, L"debug 01") == 0) {

            __VXDEBUG__ = CreateWindowEx(
                0,
                L"STATIC",
                L"",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                0,
                0,
                0,
                0,
                hWnd,
                NULL,
                GetModuleHandle(NULL),
                NULL
            ); DestroyWindow(__STARTUP_MSG__);
            __STARTUP_MSG__ = CreateWindowEx(
                0,
                L"STATIC",
                L"Debug >",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                100,
                605,
                500,
                100,
                hWnd,
                NULL,
                GetModuleHandle(NULL),
                NULL
            );  CloseWindow(__VXDEBUG__); SetWindowText(__VXDEBUG__, L"< Debug mode >"); SetWindowText(__COMMAND_EDIT__, L"");
        }
        else if (wcscmp(buffer, L"debug 00") == 0) {
            DestroyWindow(__STARTUP_MSG__);
            __STARTUP_MSG__ = CreateWindowEx(
                0,
                L"STATIC",
                L"Command >",
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                100,
                605,
                500,
                100,
                hWnd,
                NULL,
                GetModuleHandle(NULL),
                NULL
            );
            SetWindowText(__COMMAND_EDIT__, L"");
            DestroyWindow(__VXDEBUG__);
        }
        break;

    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
