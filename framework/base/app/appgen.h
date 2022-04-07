////////////////////////////////////////////////////////////////////////////////
// Preparing app input data and creating app instance functions
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPGEN_H_
#define _APPGEN_H_

#define ARGS_LIST_SIZE 32768

#include "base/utils/strutils.h"

// Defined with derived class
extern ApplicationBase * CreateApplicationInstance(const char * args);

////////////////////////////////////////////////////////////////////////////////
char * PrepareArgumentsList(char * argsList, uisize_t size,
                                int argc, char ** argv)
{
    if(argc <= 1) return NULL;

    char * head = argsList;
    for(int i = 1; i < argc; i++)
    {
        argsList = strutils::append(argsList, argv[i], size);
        if(i < argc-1)
            strutils::append(argsList, (char)0x20, size);
    }    

    return head;
}

////////////////////////////////////////////////////////////////////////////////
ApplicationBase * CreateApplication(int argc, char ** argv)
{
    char argsList[ARGS_LIST_SIZE]={0};
    char * args = NULL;
    args = PrepareArgumentsList(argsList, ARGS_LIST_SIZE, argc, argv);

    printf("args list: %s\n", args);

    ApplicationBase * app = CreateApplicationInstance(args);

    return app;
}


#endif //_APPGEN_H_
////////////////////////////////////////////////////////////////////////////////
