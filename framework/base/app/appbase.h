////////////////////////////////////////////////////////////////////////////////
// Application base class declaration
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "base/common/platformtypes.h"

#define APP_NAME_SIZE 256
#define APP_MAX_PARAMS_COUNT 1024
#define APP_MAX_PARAMS_STR_SIZE 32768

////////////////////////////////////////////////////////////////////////////////
enum ButtonType
{
    BTYPE_LBUTTON,
    BTYPE_RBUTTON,
    BTYPE_MBUTTON,
};

class AppWindow;

class ApplicationBase
{
public:
    static ApplicationBase * GetSingleton();
    virtual ~ApplicationBase();

    virtual void Init();
    virtual void Release();
    void Run();

    virtual void Render();
    virtual void Draw();

    virtual void WindowSizeChanged(int w, int h);
    virtual void WindowPosChanged(int x, int y);
    virtual void WindowActiveChanged(bool active);
    virtual void WindowClosed();

    void SetWindowSize(int w, int h);
    void SetWindowPos(int x, int y);

    virtual void KeyDown(unsigned char key);
    virtual void KeyUp(unsigned char key);

    virtual void MouseMove(int x, int y);
    virtual void MouseMove(ButtonType btype, int x, int y);
    virtual void MouseButtonDown(ButtonType btype, int x, int y);
    virtual void MouseButtonUp(ButtonType btype, int x, int y);
    virtual void MouseButtonDblClk(ButtonType btype, int x, int y);

protected:
    ApplicationBase(const char * appName, const char * args);
    static ApplicationBase * app;

private:
    char applicationName[APP_NAME_SIZE];
    bool running;
    AppWindow * window;

    struct ApplicationParamsData
    {
        char params[APP_MAX_PARAMS_STR_SIZE];
        const char * paramsPos[APP_MAX_PARAMS_COUNT];
        uint    paramsCount;

        ApplicationParamsData(const char * argsList);
        const char * GetParam(uint pos);
        uint GetParamsCount() const;
    };
    ApplicationParamsData appParams;
};
////////////////////////////////////////////////////////////////////////////////
