#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>

///////////////////////////////////////////////////////////////////////////////
class AppWindow
{
public:
    AppWindow(int posx, int posy, int width, int height, int flags,
                const char * wname);
    ~AppWindow();

    void ProcessEvents();

    bool WindowAvailable() const;
    void SetWindowTitle(const char * title);

protected:
    bool Create(int posx, int posy, int width, int height, int flags,
                 const char * wname);
    bool Destroy();

    Display * display;
    Window winId;

    bool uname_ok;
    Atom wmDeleteWindow; 
    Atom wmState;
    Atom wmStateHidden;
    Atom wmStateFullscreen;
    Atom wmStateFocused;
    Atom wmStateMaxHori;
    Atom wmStateMaxVert;
};
///////////////////////////////////////////////////////////////////////////////
