////////////////////////////////////////////////////////////////////////////////
// win32api application window class declaration
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <windows.h>

#define WIN_NAME_SIZE 256

////////////////////////////////////////////////////////////////////////////////
class AppWindow
{
public:
    AppWindow(int posx, int posy, int width, int height, int flags,
                const char * wname);
    virtual ~AppWindow();

    void ProcessEvents();
    
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    bool WindowAvailable() const;
    void SetTitle(const char * title);

protected:
    bool Create(int posx, int posy, int width, int height, int flags);
    bool Destroy();

    HWND hWnd;    

private:
    bool RegisterWndClass(HINSTANCE hInst);

    char winName[WIN_NAME_SIZE];
    char winClassName[WIN_NAME_SIZE];

};
////////////////////////////////////////////////////////////////////////////////
