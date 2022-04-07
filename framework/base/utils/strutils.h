///////////////////////////////////////////////////////////////////////////////
// String utils methods header
///////////////////////////////////////////////////////////////////////////////
//#include <stdlib.h>
// watch: https://github.com/GaloisInc/minlibc

#ifndef _STRUTILS_H_
#define _STRUTILS_H_

#include "base/common/platformtypes.h"

class strutils
{
public:
    static uisize_t length(const char * str);
    static char * copy(char * dest, const char * src, uisize_t size);
    static char * append(char * dest, const char * src, uisize_t size=0);
    static char * append(char * dest, char symbol, uisize_t size=0);
    static const char * find(const char * data, char symbol);
    static const char * find_not(const char * data, char symbol);
};


///////////////////////////////////////////////////////////////////////////////
#endif //_STRUTILS_H_
