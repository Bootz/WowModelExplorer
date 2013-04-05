#pragma once

#include "IMaterialRenderer.h"
#include <map>

class CD3D11MaterialRenderer_Solid : public IMaterialRenderer
{
public:
	virtual void OnSetMaterial( E_VERTEX_TYPE vType, const SMaterial& material, bool resetAllRenderStates );
};

class CD3D11MaterialRenderer_Transparent_Alpha_Blend : public IMaterialRenderer
{
public:
	virtual void OnSetMaterial( E_VERTEX_TYPE vType, const SMaterial& material, bool resetAllRenderStates );
	virtual void OnRender(const SMaterial& material, u32 pass);
};

class CD3D11MaterialRenderer_Transparent_Alpha_Test : public IMaterialRenderer
{
public:
	virtual void OnSetMaterial( E_VERTEX_TYPE vType, const SMaterial& material, bool resetAllRenderStates );
	virtual void OnRender(const SMaterial& material, u32 pass);
};

class CD3D11MaterialRenderer_Terrain_MultiPass : public IMaterialRenderer
{
public:
	virtual u32 getNumPasses() const { return 1; }
	virtual void OnSetMaterial( E_VERTEX_TYPE vType, const SMaterial& material, bool resetAllRenderStates);
};