#pragma once

#include "core.h"
#include "SColor.h"
#include "SMaterial.h"
#include "IShader.h"

class CD3D9ShaderServices;

class CD3D9_VS30
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D9_VS30);

public:
	CD3D9_VS30() {}

	static void Terrain_setShaderConst(IVertexShader* vs, const SMaterial& material, u32 pass);
	static void HwSkinning_setShaderConst(IVertexShader* vs, const SMaterial& material, u32 pass);
	static void Default_W_setShaderConst(IVertexShader* vs, const SMaterial& material, u32 pass);
	static void Default_WMat_setShaderConst(IVertexShader* vs, const SMaterial& material, u32 pass);
	static void Default_WTex_setShaderConst(IVertexShader* vs, const SMaterial& material, u32 pass);
	static void Default_WMatTex_setShaderConst(IVertexShader* vs, const SMaterial& material, u32 pass);

public:
	void loadAll(CD3D9ShaderServices* shaderServices);

private:
	struct SVertexShaderEntry
	{
		E_VS_TYPE vsType;
		string64	path;
		VSHADERCONSTCALLBACK callback;
	};

	struct SParamW
	{
		matrix4 		mWorldViewProjection;    // World * View * Projection
	};

	struct SParamWMat
	{
		matrix4 		mWorldViewProjection;    // World * View * Projection
		SColorf			AmbientColor;
		SColorf			EmissiveColor;
	};

	struct SParamWTex
	{
		matrix4 		mWorldViewProjection;    // World * View * Projection
		float				Params[4];		//0: numBones, 1: animTexture
		matrix4			mTexture;
	};

	struct SParamWMatTex
	{
		matrix4 		mWorldViewProjection;    // World * View * Projection
		SColorf			AmbientColor;
		SColorf			EmissiveColor;
		float				Params[4];		//0: numBones, 1: animTexture
		matrix4			mTexture;
	};

	struct SParamTerrain
	{
		matrix4 		mWorldViewProjection;    // World * View * Projection
		matrix4			mWorldView;		//World * View
		float fogParams[4];		//0: fogMode, 1: fogStart, 2: fogEnd, 3: fogDensity
		float				Params[4];		//0: animTexture, 1: fogEnable
		matrix4			mTexture;
	};
};