/////////////////////////////////////////////////////////////////////////////////////////////
// graphicapi.h
//
// Renderer interface class and structures
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GRAPHICAPI_H_
#define _GRAPHICAPI_H_

#include "platformtypes.h"
#include "gapiparams.h"
#include "gapidevcaps.h"



struct GAPICREATIONINFO
{
    uint32t width;
    uint32t height;
    bool    fullscreen;
    int     colorbits;
    int     depthbits;
    int     stencilbits;
    int     multisample;
    bool    vsync;     
    void    *hwindow;
};


////////////////////////////////////////////////////////////////////////////////
class GraphicAPIBase
{
public:
    GraphicAPIBase(){}
    virtual ~GraphicAPIBase(){}

    virtual bool Create(const GAPICREATIONINFO *info) {return false;}
    virtual void Render() {}
    virtual void Resize(int width, int height) {}
    virtual bool SwapGraphicBuffers() {return false;}

    virtual void Clear(){}
    virtual void Clear(bool color, bool depth, bool stencil) {}

    // Setting Framebuffer Clear Color
    virtual void SetClearColor(float red, float green, float blue, float alpha){}
    virtual void SetClearColor(ubyte red, ubyte green, ubyte blue, ubyte alpha){}
    
};
////////////////////////////////////////////////////////////////////////////////

#endif //_GRAPHICAPI_

