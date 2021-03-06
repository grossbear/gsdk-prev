////////////////////////////////////////////////////////////////////////////////
// Memory utils methods definitions
////////////////////////////////////////////////////////////////////////////////
#include "memutils.h"

////////////////////////////////////////////////////////////////////////////////
void * memutils::set(void * ptr, int value, uisize_t len)
{
    unsigned char * headptr = (unsigned char*)ptr;
    unsigned char * dataptr = (unsigned char*)ptr;
    while(len--)
    {
        *dataptr++ = (unsigned char)value;
    }

    return headptr;
}

////////////////////////////////////////////////////////////////////////////////
