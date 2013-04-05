#pragma once

#include "base.h"
#include "SMaterial.h"
#include "IShader.h"
#include "ILostResetCallback.h"

#define USE_COMPILED_SHADER

class matrix4A16;

//提供所有shader相关的辅助函数，参数设置等
//管理所有加载的shader 
class IShaderServices : public ILostResetCallback
{
public:
	virtual ~IShaderServices() {}

public:
	virtual IVertexShader* getVertexShader(E_VS_TYPE type) = 0;
	virtual IPixelShader* getPixelShader(E_PS_TYPE type) = 0;
	virtual IVertexShader* getDefaultVertexShader(E_VERTEX_TYPE vType) = 0;
	virtual IPixelShader* getDefaultPixelShader(E_VERTEX_TYPE vType) = 0;

	virtual bool loadVShader( const c8* filename, E_VS_TYPE type, VSHADERCONSTCALLBACK callback ) = 0;
	virtual bool loadPShader( const c8* filename, E_PS_TYPE type, PSHADERCONSTCALLBACK callback ) = 0;
	virtual bool loadVShaderHLSL( const c8* filename, const c8* entry, const c8* profile, E_VS_TYPE type, VSHADERCONSTCALLBACK callback ) = 0;
	virtual bool loadPShaderHLSL( const c8* filename, const c8* entry, const c8* profile, E_PS_TYPE type, PSHADERCONSTCALLBACK callback ) = 0;

	virtual void useVertexShader(IVertexShader* vshader) = 0;
	virtual void usePixelShader(IPixelShader* pshader) = 0;
	virtual void setShaderConstants(IVertexShader* vs, const SMaterial& material, u32 pass) = 0;
	virtual void setShaderConstants(IPixelShader* ps, const SMaterial& material, u32 pass) = 0;

	virtual void getWVPMatrix(matrix4& mat) const = 0;
	virtual void getWVMatrix(matrix4& mat) const = 0;
	virtual void getVPMatrix(matrix4& mat) const = 0;
};