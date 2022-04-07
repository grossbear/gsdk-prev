///////////////////////////////////////////////////////////////////////////////
// strutils.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "strutils.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
uisize_t strutils::length(const char * str)
{
    if(!str) return 0;

    uisize_t size = 0;
    while(*str++) size++;

    return size;
}

///////////////////////////////////////////////////////////////////////////////
char * strutils::copy(char * dest, const char * src, uisize_t size)
{
    if(!dest || !src) return NULL;

    char * ptr = dest;
    uisize_t len = 0;
    while(*dest++ = *src++) 
    {
        len++;
        if(len >= size) break;
    }
    return ptr;
}

///////////////////////////////////////////////////////////////////////////////
char * strutils::append(char * dest, const char * src, uisize_t size)
{
    if(!dest || !src) return NULL;

    char * ptr = dest;
    uisize_t len = 0;

    uisize_t destsize = strutils::length(dest);
    if(size)
    {
        uisize_t srcsize = strutils::length(src);
        uisize_t fullsize = destsize + srcsize;
        if( (fullsize + 1) > size ) return NULL;
    }

    dest += destsize;
    while(*dest++ = *src++);

    return ptr;
}

///////////////////////////////////////////////////////////////////////////////
char * strutils::append(char * dest, char symbol, uisize_t maxsize)
{
    if(!dest) return NULL;
    
    char * ptr = dest;
    uisize_t len = 0;

    uisize_t destsize = strutils::length(dest);
    if(maxsize && (destsize+2 > maxsize))
        if(destsize + 2 > maxsize) return NULL;

    dest += destsize;
    *dest++ = symbol;
    *dest = 0;

    return ptr; 
} 

////////////////////////////////////////////////////////////////////////////////
const char * strutils::find(const char * data, char symbol)
{
    if(!data) return NULL;

    const char * ptr = data;
    while(*ptr != symbol) ptr++;

    return (*ptr) ? (ptr) : (NULL);
}

////////////////////////////////////////////////////////////////////////////////
const char * strutils::find_not(const char * data, char symbol)
{
    if(!data) return NULL;

    const char * ptr = data;
    while(*ptr == symbol) ptr++;

    return (*ptr) ? (ptr) : (NULL);
}
