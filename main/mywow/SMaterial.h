#pragma once

#include "base.h"
#include "SColor.h"

class ITexture;
class IVertexShader;
class IPixelShader;

//sampler
struct SMaterialLayer
{
	E_TEXTURE_CLAMP TextureWrapU;
	E_TEXTURE_CLAMP TextureWrapV;
	E_TEXTURE_CLAMP TextureWrapW;
	bool	UseTextureMatrix : 1;
	matrix4* TextureMatrix;

	SMaterialLayer()
		: TextureWrapU(ETC_CLAMP),
		TextureWrapV(ETC_CLAMP),
		TextureWrapW(ETC_CLAMP),
		UseTextureMatrix(false),
		TextureMatrix(NULL)
	{
	}

	inline bool operator!=(const SMaterialLayer& b) const
	{
		if (!UseTextureMatrix)
		{
			return TextureWrapU != b.TextureWrapU ||
				TextureWrapV != b.TextureWrapV ||
				UseTextureMatrix != b.UseTextureMatrix;
		}
		else
		{
			if (!TextureMatrix)
			{
				return b.TextureMatrix ||
					TextureWrapU != b.TextureWrapU ||
					TextureWrapV != b.TextureWrapV ||
					UseTextureMatrix != b.UseTextureMatrix;
			}
			else
			{
				return !b.TextureMatrix ||
					TextureWrapU != b.TextureWrapU ||
					TextureWrapV != b.TextureWrapV ||
					UseTextureMatrix != b.UseTextureMatrix ||
					memcmp(TextureMatrix, b.TextureMatrix, sizeof(matrix4)) != 0;
			}
		}
	}

	inline bool operator==(const SMaterialLayer& b) const
	{ return !(b!=*this); }

};

//global sampler
struct SOverrideMaterial
{
	SOverrideMaterial() 
	{
		for(u32 i=0; i<MATERIAL_MAX_TEXTURES; ++i)
		{	
			TextureFilters[i] = ETF_BILINEAR;
			MipMapLodBias[i] = 0;
		}
	}

	E_TEXTURE_FILTER	TextureFilters[MATERIAL_MAX_TEXTURES];
	s32		MipMapLodBias[MATERIAL_MAX_TEXTURES];

	inline bool operator!=(const SOverrideMaterial& b) const
	{
		return memcmp(this, &b, sizeof(SOverrideMaterial)) != 0;
	}

	inline bool operator==(const SOverrideMaterial& b) const
	{ return memcmp(this, &b, sizeof(SOverrideMaterial)) == 0; }
};

/*
//basic
SColorf		AmbientColor;
SColorf		DiffuseColor;
SColorf		EmissiveColor;
SColorf		SpecularColor;
f32		Shininess;

//vs
bool		GouraudShading : 1;
bool		Lighting : 1;
bool		FogEnable : 1;
IVertexShader*		VertexShader;

//rasterize
bool		Wireframe : 1;
E_CULL_MODE		Cull;
E_ANTI_ALIASING_MODE		AntiAliasing;

//sampler state
SMaterialLayer		TextureLayer[MATERIAL_MAX_TEXTURES];

//depth stencil
u8			ZBuffer;
bool		ZWriteEnable : 1;
bool		StencilEnable : 1;

//ps(texture stage), blend
E_MATERIAL_TYPE	MaterialType;	//blend
E_PS_TYPE	PsType;			//ps
*/

//render state
struct SMaterial
{
	//basic
	SColorf		AmbientColor;
	SColorf		DiffuseColor;
	SColorf		EmissiveColor;
	SColorf		SpecularColor;
	f32		Shininess;

	bool		GouraudShading : 1;
	bool		Lighting : 1;
	bool		FogEnable : 1;
	bool		Wireframe : 1;
	bool		ZWriteEnable : 1;
	bool		StencilEnable : 1;
	
	u8			ZBuffer;
	E_CULL_MODE		Cull;
	E_ANTI_ALIASING_MODE		AntiAliasing;
	E_MATERIAL_TYPE	MaterialType;	//blend
	E_PS_TYPE	PsType;			//ps

	SMaterialLayer		TextureLayer[MATERIAL_MAX_TEXTURES];
	IVertexShader*		VertexShader;

	SMaterial()
		: MaterialType((E_MATERIAL_TYPE)-1),
		PsType((E_PS_TYPE)-1),
		AmbientColor(1.0f,1.0f,1.0f,1.0f),
		DiffuseColor(1.0f,1.0f,1.0f,1.0f),
		EmissiveColor(0,0,0,0),
		SpecularColor(0,0,0,0),
		Shininess(0.0f),
		ZBuffer(ECFN_LESSEQUAL),
		Wireframe(false),
		GouraudShading(true), Lighting(true),
		ZWriteEnable(true),
		StencilEnable(false),
		Cull(ECM_NONE),
		FogEnable(false),
		AntiAliasing(EAAM_SIMPLE),
		VertexShader(NULL)
	{

	}

	float getMaterialAlpha() const
	{
		if (Lighting)
			return AmbientColor.getAlpha();
		else
			return EmissiveColor.getAlpha();
	}

	SColor getMaterialColor() const
	{
		if (Lighting)
			return AmbientColor.toSColor();
		else
			return EmissiveColor.toSColor();
	}

	void setMaterialAlpha(float alpha)
	{
		if (Lighting)
			AmbientColor.setAlpha(AmbientColor.getAlpha() * alpha);
		else
			EmissiveColor.setAlpha(EmissiveColor.getAlpha() * alpha);
	}

	void setMaterialColor(SColor color)
	{
		//不改变alpha
		if (Lighting)
		{
			AmbientColor.setRed(color.getRed() / 255.0f);
			AmbientColor.setGreen(color.getGreen() / 255.0f);
			AmbientColor.setBlue(color.getBlue() / 255.0f);
		}
		else
		{
			EmissiveColor.setRed(color.getRed() / 255.0f);
			EmissiveColor.setGreen(color.getGreen() / 255.0f);
			EmissiveColor.setBlue(color.getBlue() / 255.0f);
		}
	}

	inline bool operator!=(const SMaterial& b) const
	{
		return memcmp(this, &b, sizeof(SMaterial)) != 0;
	}

	inline bool operator==(const SMaterial& b) const
	{ return !(b!=*this); }

	inline bool isTransparent() const 
	{
		return MaterialType > EMT_ALPHA_TEST;
	}
};

//blend state
struct  SRenderStateBlock
{
	struct STextureStageBlock
	{
		STextureStageBlock() :
		colorOp(ETO_DISABLE), colorArg1(ETA_TEXTURE), colorArg2(ETA_DIFFUSE),
		alphaOp(ETO_DISABLE), alphaArg1(ETA_TEXTURE), alphaArg2(ETA_DIFFUSE),
		texcoordIndex(0) { }

		E_TEXTURE_OP		colorOp;
		E_TEXTURE_ARG		colorArg1;
		E_TEXTURE_ARG		colorArg2;
		E_TEXTURE_OP		alphaOp;
		E_TEXTURE_ARG		alphaArg1;
		E_TEXTURE_ARG		alphaArg2;
		u8	texcoordIndex;
	};

	SRenderStateBlock()
		: alphaBlendEnabled(false), blendOp(EBO_ADD),
		srcBlend(EBF_ONE), destBlend(EBF_ZERO),
		alphaTestEnabled(false),
		alphaTestFunc(ECFN_GREATEREQUAL),
		alphaTestRef(0),
		alphaToCoverage(false),
		pixelShader(NULL)
	{
		for (u8 i=0; i<MATERIAL_MAX_TEXTURES; ++i)
		{
			textureUnits[i].texcoordIndex = i;
		}
	}

	STextureStageBlock		textureUnits[MATERIAL_MAX_TEXTURES];
	IPixelShader*		pixelShader;		//ps通常取代STextureStageBlock

	E_BLEND_OP		blendOp;
	E_BLEND_FACTOR	srcBlend;
	E_BLEND_FACTOR	destBlend;
	bool  alphaTestEnabled;
	E_COMPARISON_FUNC	alphaTestFunc;
	u8	alphaTestRef;
	bool	alphaToCoverage;
	bool	alphaBlendEnabled;

	inline bool operator!=(const SRenderStateBlock& b) const
	{
		return memcmp(this, &b, sizeof(SRenderStateBlock)) != 0;
	}

	inline bool operator==(const SRenderStateBlock& b) const
	{ return !(b!=*this); }
};


