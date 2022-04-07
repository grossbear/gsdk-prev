////////////////////////////////////////////////////////////////////////////////
// Application derived class example
////////////////////////////////////////////////////////////////////////////////

#include "apptest.h"

#define APP_NAME "AppTest"


ApplicationBase * CreateApplicationInstance(const char * args)
{
    AppTest::CreateSingleton(APP_NAME, args);
    return AppTest::GetSingleton();
}

////////////////////////////////////////////////////////////////////////////////
void AppTest::CreateSingleton(const char * name, const char * args)
{
    if(app == NULL)
    {
        app = new AppTest(name, args);
    }
}

////////////////////////////////////////////////////////////////////////////////
AppTest::AppTest(const char * name, const char * args):
ApplicationBase(name, args)
{

}

////////////////////////////////////////////////////////////////////////////////
