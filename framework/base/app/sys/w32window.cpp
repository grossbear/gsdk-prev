////////////////////////////////////////////////////////////////////////////////
// win32api application window class definition
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "w32window.h"
#include "base/app/appbase.h"
#include "base/utils/strutils.h"

#define WIN_CLASS_NAME "AppWindowClass"
#define WIN_CLASS_SUFFIX "Class"


#define WIN_REG_FAILED_STR  "Window class registration failed!"
#define WIN_ERROR_STR "Error!"
#define WIN_CREATE_FAILED_STR "Window creation failed!"

class WinParams
{
public:
    bool active; // Window active flag
    bool fullscreen; // Window fullscreen flag
    bool blockScreensaver;
    bool blockMonitorPowerSave;

    bool closeOnEsc; // Close window on escape key
};

WinParams gWinParams;

////////////////////////////////////////////////////////////////////////////////
AppWindow::AppWindow(int posx , int posy, int width, int height, int flags,
const char * wname):
hWnd(NULL) 
{
    gWinParams.active = false;
    gWinParams.fullscreen = false;
    gWinParams.blockScreensaver = false;
    gWinParams.blockMonitorPowerSave = false;
    gWinParams.closeOnEsc = true;

    memset(winName, 0, WIN_NAME_SIZE*sizeof(char));
    memset(winClassName, 0, WIN_NAME_SIZE*sizeof(char));

    strutils::copy(winName, wname, WIN_NAME_SIZE*sizeof(char));
    strutils::append(winClassName, WIN_CLASS_SUFFIX, sizeof(WIN_CLASS_SUFFIX));

    Create(posx, posy, width, height, flags);
}

////////////////////////////////////////////////////////////////////////////////
AppWindow::~AppWindow()
{
    Destroy();
}

////////////////////////////////////////////////////////////////////////////////
bool AppWindow::WindowAvailable() const
{
    return hWnd != NULL;
}

////////////////////////////////////////////////////////////////////////////////
void AppWindow::ProcessEvents()
{
    MSG msg;

    // Is there a message waiting?
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        //printf("Process Events\n");
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

////////////////////////////////////////////////////////////////////////////////
void AppWindow::SetTitle(const char * title)
{
    SetWindowText(hWnd, title);
}

////////////////////////////////////////////////////////////////////////////////
bool AppWindow::Create(int x, int y, int width, int height, int flags)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    if (!RegisterWndClass(hInstance))
    {
        UINT msgFlags = MB_ICONEXCLAMATION | MB_OK;
        MessageBox(NULL, WIN_REG_FAILED_STR, WIN_ERROR_STR, msgFlags);
        return false;
    }

    DWORD dwStyle = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
        winClassName,
        winName,
        dwStyle,
        x, //CW_USEDEFAULT
        y, //CW_USEDEFAULT
        width,
        height,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hWnd == NULL)
    {
        UINT msgFlags = MB_ICONEXCLAMATION | MB_OK;
        MessageBox(NULL, WIN_CREATE_FAILED_STR, WIN_ERROR_STR, msgFlags);
        return false;
    }

    // Setting Window Params
    ShowWindow(hWnd, SW_SHOW);
    SetForegroundWindow(hWnd);
    SetFocus(hWnd);
    gWinParams.active = true;

    return true;
}

////////////////////////////////////////////////////////////////////////////////
bool AppWindow::Destroy()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    if(hWnd)
    {
        DestroyWindow(hWnd);
        UnregisterClass(winClassName, hInstance);
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
bool AppWindow::RegisterWndClass(HINSTANCE hInstance)
{
    WNDCLASSEX wc; // A properties struct of our window
    // Zero out the struct and set the stuff we want to modify  
    memset(&wc,0,sizeof(wc));

    wc.cbSize       = sizeof(WNDCLASSEX);
    wc.style        = CS_OWNDC | CS_DBLCLKS;
    // This is where we will send messages to
    wc.lpfnWndProc  = AppWindow::WndProc;
    wc.hInstance    = hInstance;
    wc.hbrBackground= (HBRUSH)(COLOR_WINDOW+1);
                       //(HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszClassName= winClassName;
    wc.hCursor      = LoadCursor(NULL, IDC_ARROW);
    // Load a standard icon
    wc.hIcon        = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm      = LoadIcon(NULL, IDI_APPLICATION);

    return RegisterClassEx(&wc);;
}

////////////////////////////////////////////////////////////////////////////////
// hwnd - Handle for this window
// message - Message for this Window
// wParam - Additional message information
// lParam - Additional message information
LRESULT CALLBACK AppWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    ApplicationBase * app = ApplicationBase::GetSingleton();

    // Check for windows messages
    switch(message)
    {
        // Watch for window activate message
        case WM_ACTIVATE:
        {
            // Get minimization state
            gWinParams.active = (bool)!HIWORD(wParam);
            app->WindowActiveChanged(gWinParams.active);
            return 0;       
        }
        break;

        // Draw message 
        /*
        case WM_PAINT:
        {
            app->Draw();
        }
        break;
        */

        // Intercept System Commands
        case WM_SYSCOMMAND:                         
        {
            // Check System Calls
            switch (wParam)                         
            {
                // Screensaver Trying To Start?
                case SC_SCREENSAVE:
                    if(gWinParams.blockScreensaver)
                        return 0; // Prevent From Happening
                // Monitor Trying To Enter Powersave?           
                case SC_MONITORPOWER:
                    if(gWinParams.blockMonitorPowerSave)
                        return 0; // Prevent From Happening
            }
        }
        break;

        case WM_QUIT:
            printf("quit\n");
            //PostQuitMessage(0);
            //app->CloseWindow();
            return 0;

        case WM_CREATE:
            printf("create\n");
            return 0;

        case WM_SIZE:
        {
            int width = (int)LOWORD(lParam);
            int height = (int)HIWORD(lParam);
            app->WindowSizeChanged(width, height);
            return 0;
        }

        case WM_DESTROY:
            printf("destroy\n");
            return 0;

        // Did We Receive A Close Message?
        case WM_CLOSE:
            printf("close\n");
            app->WindowClosed();
            return 0;

        // Is A Key Being Held Down?
        case WM_KEYDOWN:
        {
            if(wParam == VK_ESCAPE && gWinParams.closeOnEsc)
            {
                printf("escape\n");
                PostQuitMessage(0);
                return 0;
            }

            unsigned char key = (unsigned char) wParam;
            app->KeyDown(key);
            return 0;
        }
        break;

        // Has A Key Been Released?
        case WM_KEYUP:
        {
            unsigned char key = (unsigned char) wParam;
            app->KeyUp(key);
            return 0;
        }
        break;

        // Left button operations
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_LBUTTONDBLCLK:
        {
            ButtonType btype = BTYPE_LBUTTON;
            int x = (int) LOWORD(lParam);
            int y = (int) HIWORD(lParam);
            if(message == WM_LBUTTONDOWN)
                app->MouseButtonDown(btype, x, y);
            else if(message == WM_LBUTTONUP)
                app->MouseButtonUp(btype, x, y);
            else
                app->MouseButtonDblClk(btype, x, y);
            return 0;
        }
        break;

        // Right button operations
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_RBUTTONDBLCLK:
        {
            ButtonType btype = BTYPE_RBUTTON;
            int x = (int) LOWORD(lParam);
            int y = (int) HIWORD(lParam);
            if(message == WM_RBUTTONDOWN)
                app->MouseButtonDown(btype, x, y);
            else if (message == WM_RBUTTONUP)
                app->MouseButtonUp(btype, x, y);
            else
                app->MouseButtonDblClk(btype, x, y);
            return 0;
        }
        break;

        // Middle button operations
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MBUTTONDBLCLK:
        {
            ButtonType btype = BTYPE_MBUTTON;
            int x = (int) LOWORD(lParam);
            int y = (int) HIWORD(lParam);
            if(message == WM_MBUTTONDOWN)
                app->MouseButtonDown(btype, x, y);
            else if(message == WM_MBUTTONUP)
                app->MouseButtonUp(btype, x, y);
            else
                app->MouseButtonDblClk(btype, x, y);
            return 0;
        }
        break;

        // Mouse move operations
        case WM_MOUSEMOVE:
        {
            int x = (int) LOWORD(lParam);
            int y = (int) HIWORD(lParam);
            app->MouseMove(x, y);
       
            switch(wParam)
            {
            case MK_LBUTTON:
                app->MouseMove(BTYPE_LBUTTON, x, y);
            break;

            case MK_RBUTTON:
                app->MouseMove(BTYPE_RBUTTON, x, y);
                break;

            case MK_MBUTTON:
                app->MouseMove(BTYPE_MBUTTON, x, y);
                break;
            }
            return 0;
        }
        break;

    }

    // Pass all unhandled messages to DefWindowProc
    return DefWindowProc(hwnd, message, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
