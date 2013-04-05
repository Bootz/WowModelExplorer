#pragma once

#include "core.h"
#include "SColor.h"
#include "SMaterial.h"
#include "IShader.h"

class CD3D11ShaderServices;

class CD3D11_PS40
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D11_PS40);

public:
	CD3D11_PS40() {}

	static void Terrain_setShaderConst(IPixelShader* ps, const SMaterial& material, u32 pass);
	static void MapObj_setShaderConst(IPixelShader* ps, const SMaterial& material, u32 pass);
	static void UI_setShaderConst(IPixelShader* ps, const SMaterial& material, u32 pass);
	static void Default_setShaderConst_T1(IPixelShader* ps, const SMaterial& material, u32 pass);
	static void Default_setShaderConst_T2(IPixelShader* ps, const SMaterial& material, u32 pass);

public:
	void loadAll(CD3D11ShaderServices* shaderServices);

private:
	struct SPixelShaderEntry
	{
		E_PS_TYPE psType;
		string64	path;
		PSHADERCONSTCALLBACK callback;
	};

	struct Common_CB
	{
		float				params[4];		//0: alphatest, 1: alpharef
	};

	struct Terrain_CB
	{
		float params[4];		//0: numTextures
		SColorf			fogColor;
	};

	struct UI_CB
	{
		float				params[4];	//0: alpha, 1: alphachannel
	};

	struct MapObj_CB
	{
		SColorf 		MaterialAmbient;
		SColorf			AmbientColor;
		SColorf			FogColor;
		float			params[4];			//0: alphatest, 1: ref, 2: specular strength
	};
};