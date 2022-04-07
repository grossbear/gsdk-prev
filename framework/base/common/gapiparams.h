
/////////////////////////////////////////////////////////////////////////////////////////////
// gapiparams.h
//
// Render interface parameters
/////////////////////////////////////////////////////////////////////////////////////////////
enum GAPIFUNCTION 
{
    NEVER    = 0,
    LESS     = 1,
    EQUAL    = 2,
    LEQUAL   = 3,
    GREATER  = 4,
    NOTEQUAL = 5,
    GEQUAL   = 6,
    ALWAYS   = 7,
};


enum GAPIOPERATION 
{
    KEEP    = 0,
    ZERO    = 1,
    REPLACE = 2,
    INCRSAT = 3,
    DECRSAT = 4,
    INVERT  = 5,
    INCR    = 6,
    DECR    = 7,
};

enum GAPIBLENDOPERATION 
{
    BLENDOP_ZERO                = 0,
    BLENDOP_ONE                 = 1,                
    BLENDOP_DST_COLOR           = 2, //For Source-Blending Factor Only
    BLENDOP_ONE_MINUS_DST_COLOR = 3, //For Source-Blending Factor Only
    BLENDOP_SRC_ALPHA           = 4,
    BLENDOP_ONE_MINUS_SRC_ALPHA = 5,
    BLENDOP_DST_ALPHA           = 6,
    BLENDOP_ONE_MINUS_DST_ALPHA = 7,
    BLENDOP_SRC_ALPHA_SATURATE  = 8,
    BLENDOP_SRC_COLOR           = 9, //For Destination-Blending  Factor Only
    BLENDOP_ONE_MINUS_SRC_COLOR = 10,//For Destination-Blending  Factor Only
};

enum GAPIBLENDFUNCTION
{
    BLENDFUNC_ADD               = 0,
    BLENDFUNC_SUBTRACT          = 1,
    BLENDFUNC_REVERSE_SUBTRACT  = 2,
    BLENDFUNC_MIN               = 3,
    BLENDFUNC_MAX               = 4,
};

typedef GAPIFUNCTION        GAPIFUNC;
typedef GAPIOPERATION       GAPIOP;
typedef GAPIBLENDOPERATION  GAPIBLENDOP;
typedef GAPIBLENDFUNCTION   GAPIBLENDFUNC;

//Fill Mode
enum GAPIFILLMODE
{
    GAPIFILL_NONE       = 0,
    GAPIFILL_POINT      = 1,
    GAPIFILL_WIREFRAME  = 2,
    GAPIFILL_SOLID      = 3,
};

//Texture Parameters
enum TEXTURETYPE 
{
    TEX_NONE,
    TEX_1D,
    TEX_2D,
    TEX_3D,
    TEX_CUBE,
};


enum TEXTUREFILTER 
{
    //Single Texture Filters
    TEXFLT_POINT,
    TEXFLT_LINEAR,

    //Mipmap Texture Filters
    TEXFLT_BILINEAR,
    TEXFLT_TRILINEAR,

    //Mipmap Texture Filters With Anisotropic
    TEXFLT_BILINEAR_ANISOTROPY,
    TEXFLT_TRILINEAR_ANISOTROPY,
};

#define TEXF TEXTUREFILTER

enum TEXTUREADDRESS 
{
    TEXADDR_REPEAT      =   1,
    TEXADDR_CLAMP       =   2,
    TEXADDR_BORDER      =   3,
    TEXADDR_MIRROR      =   4,
    TEXADDR_MIRRORONCE  =   5,
};

enum TEXTUREFORMAT
{
    TEXFMT_NONE, 
    TEXFMT_L8,
    TEXFMT_LA8,
    TEXFMT_RGB8,
    TEXFMT_RGBA8,
    TEXFMT_BGR8,
    TEXFMT_BGRA8,
    TEXFMT_L16,
    TEXFMT_LA16,
    TEXFMT_RG16,
    TEXFMT_RGB16,
    TEXFMT_RGBA16,
    TEXFMT_R16f,
    TEXFMT_RG16f,
    TEXFMT_RGB16f,
    TEXFMT_RGBA16f,
    TEXFMT_R32f,
    TEXFMT_RG32f,
    TEXFMT_RGB32f,
    TEXFMT_RGBA32f,

    TEXFMT_UV8,
    TEXFMT_UVWQ8,
    TEXFMT_UV16,
    TEXFMT_UVWQ16,

    TEXFMT_DEPTH16,
    TEXFMT_DEPTH24,
    TEXFMT_L4A4,
    TEXFMT_A4RGB4,
    TEXFMT_R3G3B2,
    TEXFMT_R5G6B5,
    TEXFMT_A1RGB5,
    TEXFMT_A2RGB10,
    TEXFMT_RG11B10,
    TEXFMT_RGB9E5,

    TEXFMT_UV5L6,
    TEXFMT_UVW10A2,

    TEXFMT_DXT1,
    TEXFMT_DXT3,
    TEXFMT_DXT5,
    TEXFMT_ATI1N,
    TEXFMT_ATI2N,
};


typedef TEXTURETYPE TEXTYPE;
typedef TEXTUREFORMAT TEXFMT;
typedef TEXTUREFILTER TEXFLT;
typedef TEXTUREADDRESS TEXADDR;


enum CUBEMAPFACE 
{
    FACE_POSITIVE_X = 0,
    FACE_NEGATIVE_X = 1,
    FACE_POSITIVE_Y = 2,
    FACE_NEGATIVE_Y = 3,
    FACE_POSITIVE_Z = 4,
    FACE_NEGATIVE_Z = 5,
};

// Rendering Primitive Type
enum GAPIPRIMITIVETYPE
{
    GAPI_POINTS,
    GAPI_LINES,
    GAPI_LINE_STRIP,
    GAPI_LINE_LOOP,
    GAPI_TRIANGLES,
    GAPI_TRIANGLE_STRIP, 
    GAPI_TRIANGLE_FAN,
    GAPI_QUAD,
    GAPI_QUAD_STRIP,
};

typedef GAPIPRIMITIVETYPE GAPIPRIMTYPE;

enum VERTEXELEM
{
    VERTELEM_POSITION,
    VERTELEM_NORMAL,
    VERTELEM_DIFFUSE,
    VERTELEM_SPECULAR,
    VERTELEM_TANGENT,
    VERTELEM_BINORMAL,
    VERTELEM_FOGCOORD,
    VERTELEM_POINTSIZE,
    VERTELEM_TEXCOORD,
    VERTELEM_ATTRIBUTE,
    VERTELEM_INDEX,
};


enum GAPIDATATYPE
{
    GAPI_NONE,
    GAPI_FLOAT,
    GAPI_DOUBLE,
    GAPI_HALF,
    GAPI_FIXED,
    GAPI_BYTE,
    GAPI_UBYTE,
    GAPI_INT16,
    GAPI_UINT16,
    GAPI_INT32,
    GAPI_UINT32,
};

enum GAPIMODEFUNC
{
    GAPI_LINEAR,
    GAPI_EXP,
    GAPI_EXP2,
};

enum GAPIBUFFERUSAGE 
{
    GAPI_BUFUSAGE_DYNAMIC,
    GAPI_BUFUSAGE_STATIC,
    GAPI_BUFUSAGE_STREAM,
};

struct GAPIVERTATTRIBDATA
{
    uint32t StreamIndex;
    char AttribName[64];
    uint32t Size;
    GAPIDATATYPE Type;
    uint32t Stride;
    uint32t Offset;
    bool Normalize;
    bool DirectFunc;
    uint32t BufferIdx;
};



enum GAPIUNIFORMTYPE
{
    GAPI_UNIFORM_INT,
    GAPI_UNIFORM_UINT,
    GAPI_UNIFORM_FLOAT,
    GAPI_UNIFORM_DOUBLE,

    GAPI_UNIFORM_VECTOR2I,
    GAPI_UNIFORM_VECTOR3I,
    GAPI_UNIFORM_VECTOR4I,

    GAPI_UNIFORM_VECTOR2UI,
    GAPI_UNIFORM_VECTOR3UI,
    GAPI_UNIFORM_VECTOR4UI,

    GAPI_UNIFORM_VECTOR2F,
    GAPI_UNIFORM_VECTOR3F,      
    GAPI_UNIFORM_VECTOR4F,
    GAPI_UNIFORM_VECTOR2D,
    GAPI_UNIFORM_VECTOR3D,
    GAPI_UNIFORM_VECTOR4D,
    GAPI_UNIFORM_MTX33F,
    GAPI_UNIFORM_MTX44F,
    GAPI_UNIFORM_MTX33D,
    GAPI_UNIFORM_MTX44D,
};

struct GAPIUNIFORMDATA
{
    GAPIUNIFORMTYPE Type;
    const char *Name;
    const void *Data;
};

enum GAPIACTIVEUNIFORMTYPE
{
    GAPI_UNIFORM_SIZE,
    GAPI_UNIFORM_OFFSET,
};
