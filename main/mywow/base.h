#pragma once

#include <crtdbg.h>

#include "qzone_allocator.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&);               \
void operator=(const TypeName&)

typedef		unsigned __int8		u8;
typedef		__int8		s8;

typedef		char		c8;
typedef		wchar_t	c16;

typedef		unsigned	__int16		u16;
typedef		__int16		s16;

typedef		unsigned	__int32		u32;
typedef		__int32		s32;

typedef		float		f32;
//	typedef	double	f64;

typedef		char		UTF8;
typedef		unsigned __int16		UTF16;
typedef		unsigned	__int32		UTF32;

#ifndef MAX_PATH
#define		MAX_PATH	260
#endif

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

#define F32_AS_DWORD(f)		(*((DWORD*)&(f)))
#define DWORD_AS_F32(d)		(*((f32*)&(d)))

#define		DEFAULT_SIZE	64
#define		MAX_TEXT_LENGTH	512
#define		FONT_TEXTURE_SIZE	512

#define VS11	"vs_1_1"
#define VS20	"vs_2_0"
#define VS2A	"vs_2_a"
#define VS30	"vs_3_0"

#define PS11	"ps_1_1"
#define PS12	"ps_1_2"
#define PS13	"ps_1_3"
#define PS14	"ps_1_4"
#define PS20	"ps_2_0"
#define PS2A	"ps_2_a"
#define PS2B	"ps_2_b"
#define PS30	"ps_3_0"

//terrain
#define TILESIZE (533.33333f)
#define CHUNKSIZE ((TILESIZE) / 16.0f)
#define UNITSIZE (CHUNKSIZE / 8.0f)
#define ZEROPOINT (32.0f * (TILESIZE))

#define	CHUNKS_IN_TILE	16				//每个tile包括 16 X 16 个chunk

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)		{ if (p) { delete (p); (p) = NULL; } }
#endif

#ifndef SAFE_RELEASE_STRICT
#define SAFE_RELEASE_STRICT(p)      { if (p) { ULONG u = (p)->Release(); _ASSERT(!u); (p)=NULL; } }
#endif

#ifndef RELEASE_ALL
#define RELEASE_ALL(x)			\
	ULONG rest = x->Release();	\
	while( rest > 0 )			\
	rest = x->Release();	\
	x = 0;
#endif

#ifndef ARRAY_COUNT
#define ARRAY_COUNT(a)		(sizeof(a)/sizeof(a[0]))
#endif

enum E_LOG_TYPE
{
	ELOG_GX = 0,
	ELOG_RES,

	ELOG_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_DRIVER_TYPE
{
	EDT_NULL = 0,
	EDT_DIRECT3D9,
	EDT_DIRECT3D11,
	EDT_OPENGL,
	EDT_COUNT,

	EDT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

inline const c8* getEnumString(E_DRIVER_TYPE type)
{
	switch(type)
	{
	case EDT_DIRECT3D9:
		return "Direct3D9";
	case EDT_DIRECT3D11:
		return "Direct3D11";
	case EDT_OPENGL:
		return "OpenGL";
	default:
		return "Unknown";
	}
}

enum E_TRANSFORMATION_STATE
{
	ETS_VIEW = 0,
	ETS_WORLD,
	ETS_PROJECTION,
	ETS_TEXTURE_0,
	ETS_TEXTURE_1,
	ETS_TEXTURE_2,
	ETS_TEXTURE_3,
	ETS_COUNT,

	ETS_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_VIDEO_DRIVER_FEATURE
{
	EVDF_RENDER_TO_TARGET = 0,
	EVDF_HARDWARE_TL,
	EVDF_TEXTURE_ADDRESS,
	EVDF_SEPARATE_UVWRAP,
	EVDF_MIP_MAP,
	EVDF_STENCIL_BUFFER,
	EVDF_VERTEX_SHADER_2_0,
	EVDF_VERTEX_SHADER_3_0,
	EVDF_PIXEL_SHADER_2_0,
	EVDF_PIXEL_SHADER_3_0,
	EVDF_TEXTURE_NSQUARE,
	EVDF_TEXTURE_NPOT,
	EVDF_COLOR_MASK,
	EVDF_MULTIPLE_RENDER_TARGETS,
	EVDF_MRT_COLOR_MASK,
	EVDF_MRT_BLEND_FUNC,
	EVDF_MRT_BLEND,
	EVDF_STREAM_OFFSET,
	EVDF_W_BUFFER,
	EVDF_ALPHA_TO_COVERAGE,

	//! Supports Shader model 4
	EVDF_VERTEX_SHADER_4_0,
	EVDF_PIXEL_SHADER_4_0,
	EVDF_GEOMETRY_SHADER_4_0,
	EVDF_STREAM_OUTPUT_4_0,
	EVDF_COMPUTING_SHADER_4_0,

	//! Supports Shader model 4.1
	EVDF_VERTEX_SHADER_4_1,
	EVDF_PIXEL_SHADER_4_1,
	EVDF_GEOMETRY_SHADER_4_1,
	EVDF_STREAM_OUTPUT_4_1,
	EVDF_COMPUTING_SHADER_4_1,

	//! Supports Shader model 5.0
	EVDF_VERTEX_SHADER_5_0,
	EVDF_PIXEL_SHADER_5_0,
	EVDF_GEOMETRY_SHADER_5_0,
	EVDF_STREAM_OUTPUT_5_0,
	EVDF_TESSELATION_SHADER_5_0,
	EVDF_COMPUTING_SHADER_5_0,

	//! Supports texture multisampling
	EVDF_TEXTURE_MULTISAMPLING,
	EVDF_COUNT,

	EVDF_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum ECOLOR_FORMAT
{
	//8
	ECF_A8 = 0,
	//16
	ECF_A8L8,

	ECF_A1R5G5B5,
	ECF_R5G6B5,

	//24
	ECF_R8G8B8,

	//32
	ECF_A8B8G8R8,
	ECF_A8R8G8B8,

	//DXT
	ECF_DXT1,
	ECF_DXT3,
	ECF_DXT5,

	ECF_UNKNOWN,

	ECF_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

inline u32 getBytesPerPixelFromFormat( ECOLOR_FORMAT format)
{
	switch(format)
	{
	case ECF_A8:
		return 1;
	case ECF_A8L8:
	case ECF_A1R5G5B5:
	case ECF_R5G6B5:
		return 2;
	case ECF_R8G8B8:
		return 3;
	case ECF_A8B8G8R8:
	case ECF_A8R8G8B8:
		return 4;
	case ECF_DXT1:
		return 8;
	case ECF_DXT3:
	case ECF_DXT5:
		return 16;
	default:
		return 0;
	}
}

enum E_SHADER_VERSION
{
	ESV_VS_1_1 = 0,
	ESV_VS_2_0,
	ESV_VS_2_a,
	ESV_VS_3_0,
	ESV_VS_4_0,
	ESV_VS_4_1,
	ESV_VS_5_0,

	ESV_PS_1_1,
	ESV_PS_1_2,
	ESV_PS_1_3,
	ESV_PS_1_4,
	ESV_PS_2_0,
	ESV_PS_2_a,
	ESV_PS_2_b,
	ESV_PS_3_0,
	ESV_PS_4_0,
	ESV_PS_4_1,
	ESV_PS_5_0,

	ESV_GS_4_0,

	ESV_COUNT,

	ESV_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_STREAM_TYPE
{
	EST_P = 0,
	EST_PC,
	EST_PCT,
	EST_PN,
	EST_PNC,
	EST_PNT,
	EST_PT,
	EST_PNCT,
	EST_PNCT2,
	EST_PNTW,
	EST_A,
};

enum E_VERTEX_TYPE
{
	EVT_P = 0,
	EVT_PC,			//for bounding box
	EVT_PCT,
	EVT_PN,
	EVT_PNC,
	EVT_PNT,
	EVT_PT,
	EVT_PNCT,
	EVT_PNCT2,
	EVT_MODEL,						//fvf
	EVT_COUNT,

	EVT_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

inline bool hasTexture(E_VERTEX_TYPE vType)
{
	switch(vType)
	{
	case EVT_PCT:
	case EVT_PNT:
	case EVT_PT:
	case EVT_PNCT:
	case EVT_PNCT2:
	case EVT_MODEL:
		return true;
	default:
		return false;
	}
}

enum E_MESHBUFFER_MAPPING
{
	EMM_SOFTWARE = 0,					
	EMM_STATIC,
	EMM_DYNAMIC,
	EMM_COUNT,

	EMM_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_INDEX_TYPE
{
	EIT_16BIT = 0,
	EIT_32BIT,
	EIT_COUNT,

	EIT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_PRIMITIVE_TYPE
{
	EPT_POINTS=0,
	EPT_LINE_STRIP,
	EPT_LINES,
	EPT_TRIANGLE_STRIP,
	EPT_TRIANGLES,
	EPT_COUNT,

	EPT_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

inline u32 getPrimitiveCount(E_PRIMITIVE_TYPE primType, u32 count)
{
	u32 p = 0;

	switch (primType)
	{
	case EPT_POINTS:
		p= count;
		break;
	case EPT_LINES:
		_ASSERT(count>=2);
		p = count/2;
		break;
	case EPT_LINE_STRIP:
		_ASSERT(count>=2);
		p = count - 1;
		break;
	case EPT_TRIANGLE_STRIP:
		_ASSERT(count>=3);
		p = count - 2;
		break;
	case EPT_TRIANGLES:
		_ASSERT(count>=3);
		p = count / 3;
		break;
	default:
		_ASSERT(false);
	}
	return p;
}

inline u32 getIndexCount(E_PRIMITIVE_TYPE primType, u32 primCount)
{
	u32 p = 0;

	switch (primType)
	{
	case EPT_POINTS:
		p= primCount;
		break;
	case EPT_LINES:
		p = primCount * 2;
		break;
	case EPT_LINE_STRIP:
		p = primCount + 1;
		break;
	case EPT_TRIANGLE_STRIP:
		p = primCount + 2;
		break;
	case EPT_TRIANGLES:
		p = primCount * 3;
		break;
	default:
		_ASSERT(false);
	}
	return p;
}

enum E_MATERIAL_TYPE
{
	EMT_2D = 0,
	EMT_LINE,
	EMT_SOLID,

	EMT_TERRAIN_MULTIPASS,

	EMT_ALPHA_TEST,
	EMT_TRANSPARENT_ALPHA_BLEND,
	EMT_TRANSAPRENT_ALPHA_BLEND_TEST,
	EMT_TRANSPARENT_ADD_ALPHA,	
	EMT_TRANSPARENT_ADD_COLOR,
	EMT_TRANSPARENT_MODULATE,
	EMT_TRANSPARENT_MODULATE_X2,
	
	EMT_COUNT,

	EMT_FORCE_8BIT_DO_NOT_USE = 0x7f
};

enum E_COMPARISON_FUNC
{
	ECFN_NEVER = 0,
	ECFN_LESSEQUAL,
	ECFN_EQUAL,
	ECFN_LESS,
	ECFN_NOTEQUAL,
	ECFN_GREATEREQUAL,
	ECFN_GREATER,
	ECFN_ALWAYS,

	ECFN_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_BLEND_OP
{
	EBO_ADD = 0,
	EBO_SUBSTRACT,

	EBO_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_BLEND_FACTOR
{
	EBF_ZERO = 0,
	EBF_ONE,
	EBF_DST_COLOR,
	EBF_ONE_MINUS_DST_COLOR,
	EBF_SRC_COLOR,
	EBF_ONE_MINUS_SRC_COLOR,
	EBF_SRC_ALPHA,
	EBF_ONE_MINUS_SRC_ALPHA,
	EBF_DST_ALPHA,
	EBF_ONE_MINUS_DST_ALPHA,
	EBF_SRC_ALPHA_SATURATE,

	EBF_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_TEXTURE_OP
{
	ETO_DISABLE = 0,
	ETO_ARG1,
	ETO_ARG2,
	ETO_MODULATE,
	ETO_MODULATE_X2,
	ETO_MODULATE_X4,
	ETO_ADD,
	ETO_ADDSIGNED,

	ETO_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_TEXTURE_ARG
{
	ETA_CURRENT = 0,
	ETA_TEXTURE,
	ETA_DIFFUSE,

	ETA_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_TEXTURE_ADDRESS
{
	ETA_U = 0,
	ETA_V,
	ETA_W,
	ETA_COUNT,
};

enum E_TEXTURE_CLAMP
{
	ETC_REPEAT = 0,
	ETC_CLAMP,
	ETC_CLAMP_TO_BORDER,
	ETC_MIRROR,
	ETC_MIRROR_CLAMP,
	ETC_MIRROR_CLAMP_TO_BORDER,
	ETC_COUNT,

	ETC_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_TEXTURE_FILTER
{
	ETF_NONE = 0,
	ETF_BILINEAR,
	ETF_TRILINEAR,
	ETF_ANISOTROPIC_X1,
	ETF_ANISOTROPIC_X2,
	ETF_ANISOTROPIC_X4,
	ETF_ANISOTROPIC_X8,
	ETF_ANISOTROPIC_X16,


	ETF_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

inline u8 getAnisotropic(E_TEXTURE_FILTER filter)
{
	switch(filter)
	{
	case ETF_ANISOTROPIC_X1:
		return 1;
	case ETF_ANISOTROPIC_X2:
		return 2;
	case ETF_ANISOTROPIC_X4:
		return 4;
	case ETF_ANISOTROPIC_X8:
		return 8;
	case ETF_ANISOTROPIC_X16:
		return 16;
	default:
		return 1;
	}
}


#define  MATERIAL_MAX_TEXTURES		6

enum E_LIGHT_TYPE
{
	ELT_POINT = 0,
	ELT_SPOT,
	ELT_DIRECTIONAL,
	ELT_AMBIENT,

	ELT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_CULL_MODE
{
	ECM_NONE = 0,
	ECM_FRONT,
	ECM_BACK,

	ECM_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_ANTI_ALIASING_MODE
{
	EAAM_OFF = 0,
	EAAM_SIMPLE,
	EAAM_LINE_SMOOTH,

	EAAM_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

//雾
enum E_FOG_TYPE
{
	EFT_FOG_NONE=0,
	EFT_FOG_EXP,
	EFT_FOG_EXP2,
	EFT_FOG_LINEAR,
	
	EFT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_GEOMETRY_TYPE
{
	EGT_CUBE = 0,
	EGT_SPHERE,
	EGT_SKYDOME,
	EGT_GRID,

	EGT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_VS_TYPE
{
	EVST_TERRAIN = 0,
	EVST_HWSKINNING,
	EVST_DEFAULT_P,
	EVST_DEFAULT_PC,
	EVST_DEFAULT_PCT,
	EVST_DEFAULT_PN,
	EVST_DEFAULT_PNC,
	EVST_DEFAULT_PNCT,
	EVST_DEFAULT_PNCT2,
	EVST_DEFAULT_PNT,
	EVST_DEFAULT_PT,
	EVST_MAPOBJDIFFUSE_T1,
	EVST_COUNT,

	EVST_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_PS_TYPE
{
	EPST_UI = 0,
	EPST_TERRAIN,
	EPST_DEFAULT_P,
	EPST_DEFAULT_PC,
	EPST_DEFAULT_PCT,
	EPST_DEFAULT_PN,
	EPST_DEFAULT_PNC,
	EPST_DEFAULT_PNCT,
	EPST_DEFAULT_PNCT2,
	EPST_DEFAULT_PNT,
	EPST_DEFAULT_PT,

	//blend
	EPST_COMBINERS_MOD,
	EPST_COMBINERS_MOD_ADD,
	EPST_COMBINERS_MOD_ADD_ALPHA,
	EPST_COMBINERS_MOD_ADDALPHA,
	EPST_COMBINERS_MOD_ADDALPHA_ALPHA,
	EPST_COMBINERS_MOD_ADDALPHA_WGT,
	EPST_COMBINERS_MOD_ADDNA,
	EPST_COMBINERS_MOD_MOD,
	EPST_COMBINERS_MOD_MOD2X,
	EPST_COMBINERS_MOD_MOD2XNA,
	EPST_COMBINERS_MOD_OPAQUE,
	EPST_COMBINERS_OPAQUE,
	EPST_COMBINERS_OPAQUE_ADDALPHA,
	EPST_COMBINERS_OPAQUE_ADDALPHA_ALPHA,
	EPST_COMBINERS_OPAQUE_ADDALPHA_WGT,
	EPST_COMBINERS_OPAQUE_ALPHA,
	EPST_COMBINERS_OPAQUE_ALPHA_ALPHA,
	EPST_COMBINERS_OPAQUE_MOD,
	EPST_COMBINERS_OPAQUE_MOD2X,
	EPST_COMBINERS_OPAQUE_MOD2XNA,
	EPST_COMBINERS_OPAQUE_MOD2XNA_ALPHA,
	EPST_COMBINERS_OPAQUE_MOD2XNA_ALPHA_3S,
	EPST_COMBINERS_OPAQUE_MOD2XNA_ALPHA_ADD,
	EPST_COMBINERS_OPAQUE_MOD2XNA_ALPHA_ALPHA,
	EPST_COMBINERS_OPAQUE_MOD2XNA_ALPHA_UNSHALPHA,
	EPST_COMBINERS_OPAQUE_MOD_ADD_WGT,
	EPST_COMBINERS_OPAQUE_MODNA_ALPHA,
	EPST_COMBINERS_OPAQUE_OPAQUE,
	EPST_MAPOBJOPAQUE,
	EPST_COUNT,

	EPST_FORCE_8_BIT_DO_NOT_USE = 0x7f
};

enum E_RENDERINST_TYPE
{
	ERT_NONE = 0,
	ERT_SKY,
	ERT_TERRAIN,			//低精度地形
	ERT_WMO,					//建筑
	ERT_DOODAD,		//地形小物件
	ERT_MESH,					//角色模型,m2
	ERT_EFFECT,					//特效
	ERT_WIRE,						//编辑

	ERT_COUNT,

	ERT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_LEVEL
{
	EL_ZERO = 0,
	EL_ONE,
	EL_TWO,
	EL_THREE,
	EL_FOUR,
	EL_FIVE,

	EL_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_ADT_LOAD
{
	EAL_3X3 = 0,
	EAL_5X5,
//	EAL_7X7,		//7X7 is not used yet :(
};

class IAdtLoadSizeChangedCallback
{
public:
	virtual void OnAdtLoadSizeChanged(E_ADT_LOAD size) = 0;
};