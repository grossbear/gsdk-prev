#include "xappwin.h"
#include "appbase.h"

///////////////////////////////////////////////////////////////////////////////
AppWindow::AppWindow(int posx, int posy, int width, int height, int flags, 
const char * title):
display(NULL), winId(0)
{
    Create(posx, posy, width, height, flags, title);
}

///////////////////////////////////////////////////////////////////////////////
AppWindow::~AppWindow()
{
    Destroy();
}

///////////////////////////////////////////////////////////////////////////////
bool AppWindow::WindowAvailable() const
{
    return winId != 0;
}

///////////////////////////////////////////////////////////////////////////////
void AppWindow::SetWindowTitle(const char * title)
{
    XStoreName(display, winId, title);
}

///////////////////////////////////////////////////////////////////////////////
bool AppWindow::Create(int x, int y, int width, int height, int flags,
const char * wname)
{
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        return false;
    }

    int defScreenId = DefaultScreen(display);
    Window rootWinId = RootWindow(display, defScreenId);
    
    int borderWidth = 1;
    unsigned long borderColor = BlackPixel(display, defScreenId);
    unsigned long backgroundColor = WhitePixel(display, defScreenId);

    // Creating simple X window
    winId = XCreateSimpleWindow(
            display,
            rootWinId,
            x,
            y,
            width,
            height,
            borderWidth,
            borderColor,
            backgroundColor);

    long eventMask = ExposureMask | KeyPressMask |
                     ButtonPressMask | ButtonReleaseMask |
                     PointerMotionMask | ResizeRedirectMask |
                     VisibilityChangeMask |
                     FocusChangeMask | PropertyChangeMask | 
                     EnterWindowMask | LeaveWindowMask;           

    XSelectInput(display, winId, eventMask);
    XMapWindow(display, winId);

    //XStoreName(display, winId, wname);
    this->SetWindowTitle(wname);
 
    wmDeleteWindow = XInternAtom(display, "wmDeleteWindow", False);
    XSetWMProtocols(display, winId, &wmDeleteWindow, 1);

    wmState = XInternAtom(display, "_NET_WM_STATE", False);
    wmStateHidden = XInternAtom(display, "_NET_WM_STATE_HIDDEN", False);
    wmStateFullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
    wmStateFocused = XInternAtom(display, "_NET_WM_STATE_FOCUSED", False);
    wmStateMaxHori = XInternAtom(display, "_NET_WM_ACTION_MAXIMIZE_HORZ", False);
    wmStateMaxVert = XInternAtom(display, "_NET_WM_ACTION_MAXIMIZE_VERT", False);

    return true;
}

///////////////////////////////////////////////////////////////////////////////
bool AppWindow::Destroy()
{
    XDestroyWindow(display, winId);
    XCloseDisplay(display);
    
    display = NULL;
    winId = 0;

    return true;
}

///////////////////////////////////////////////////////////////////////////////
void AppWindow::ProcessEvents()
{
    XEvent event;
    XNextEvent(display, &event);

    switch(event.type)
    {
        case Expose:
        {
            printf("Expose \n");
            ApplicationBase * app = ApplicationBase::GetSingleton();
            app->OnDraw();
        }   
        break;

        case VisibilityNotify:
        {
            printf("VisibilityNotify\n");
        }
        break;

        case EnterNotify:
        {
            //printf("EnterNotify\n");
        }
        break;

        case LeaveNotify:
        {
            //printf("LeaveNotify\n");
        }
        break;

        case MotionNotify:
        {
            //printf("Motion notify \n");
            int x = event.xmotion.x;
            int y = event.xmotion.y;
            //printf("x = %d, y = %d\n", x, y);
            //printf("state = %d, button = %d\n", event.xbutton.state, event.xbutton.button);
        }
        break;

        case PropertyNotify:
        {
            printf("Property Notify\n");
            if (wmState == event.xproperty.atom)
            {
                printf("wmState is _NET_WM_STATE\n");
                Atom type;
                int format;
                unsigned long nItems;
                unsigned long bytesAfter;
                unsigned char *data;
                XGetWindowProperty(display, winId, wmState, 0, (~0L), False, AnyPropertyType, &type, &format, &nItems, &bytesAfter, &data);

                ApplicationBase * app = ApplicationBase::GetSingleton();
                printf("nItems = %lu\n",nItems);
                for (int i = 0; i < nItems; i++)
                {
                    Atom atomState = ((long *)(data))[i];
                    if (atomState == wmStateHidden)
                    {
                        app->OnWindowActive(false);
                    }
                    else if (atomState == wmStateFocused)
                    {
                        app->OnWindowActive(true);
                    }
                    else if (atomState == wmStateMaxHori || atomState == wmStateMaxVert)
                    {
                    }
                    
                    //printf("%ld\n", ((long *)(data))[i]);
                    //char * atomName = XGetAtomName(display, ((long *)(data))[i]);
                    //printf("atom name = %s\n", atomName);
                }
            }
                
        }
        break;

        case FocusIn:
        {
            //printf("FocusIn\n");
        }
        break;

        case FocusOut:
        {
            //printf("FocusOut\n");
        }
        break;

        case KeyPress:
        {
            char buffer[256] = {0};
            KeySym keysym;
            int len = XLookupString(&event.xkey,
                                    buffer,
                                    sizeof(buffer),
                                    &keysym,
                                    NULL);

            if (keysym == XK_Escape)
            {
                ApplicationBase * app = ApplicationBase::GetSingleton();
                app->OnCloseWindow();
            }
        }
        break;

        case ButtonPress:
        case ButtonRelease:
        {
            if(event.type == ButtonPress)
                printf("Button press: ");
            else
                printf("Button release: ");
            printf("x = %d, y = %d\n", event.xbutton.x, event.xbutton.y);
            printf("state = %d, button = %d\n", event.xbutton.state, event.xbutton.button);

            int x = event.xbutton.x;
            int y = event.xbutton.y;
            ButtonType type;
            int xbtntype = event.xbutton.button;
            if (xbtntype & Button1) type = BTYPE_LBUTTON;
            if (xbtntype & Button3) type = BTYPE_RBUTTON;
            if (xbtntype & Button2) type = BTYPE_MBUTTON;
            //if (xbtntype & Button4) //mouse wheel up
            //if (xbtntype & Button5) //mouse wheel down
            
            ApplicationBase * app = ApplicationBase::GetSingleton();
            if (event.type == ButtonPress)
                app->OnMouseButtonDown(type, x, y);
            else if (event.type == ButtonRelease)
                app->OnMouseButtonUp(type, x, y);    
        }
        break;

        case ResizeRequest:
        {
            printf("Resize request\n");
        }
        break;

        case ClientMessage:
        {
            unsigned int clientMsgId = 
                static_cast<unsigned int>(event.xclient.data.l[0]);
            if (clientMsgId == wmDeleteWindow)
            {
                ApplicationBase * app = ApplicationBase::GetSingleton();
                app->OnCloseWindow();
            }
        }
        break;
    } 

}

///////////////////////////////////////////////////////////////////////////////
