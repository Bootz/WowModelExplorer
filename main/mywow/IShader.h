#pragma once

#include "base.h"

#pragma pack(push,1)
struct BlsHeader
{
	char    _magic[4];  /// shader type,must be "SPXG" or "SVXG"
	u16  _minor;        /// minor version
	u16  _major;			/// major version
	u32  shaderCount;    /// shader count in each shader block
};

struct BlsBlockHeader
{
	u32 constSize;
	u32 samplerSize;
	u32 textureSize;
	u32 codeSize;
};

struct BlsConst
{
	u32 index;
	u32 size;
	u32 tbuffer;
	c8 name[1];
};

struct BlsSampler 
{
	u32 index;
	c8 name[1];
};

struct BlsTexture
{
	u32 index;
	c8 name[1];
};

#pragma pack(pop)

class IVertexShader;
class IPixelShader;
struct SMaterial;

typedef void (*VSHADERCONSTCALLBACK)(IVertexShader* vshader, const SMaterial& material, u32 pass);
typedef void (*PSHADERCONSTCALLBACK)(IPixelShader* vshader, const SMaterial& material, u32 pass);

class IVertexShader
{
public:
	IVertexShader(VSHADERCONSTCALLBACK callback) : ShaderConstCallback(callback) {}
	virtual ~IVertexShader() {}

public:
	virtual bool isValid() const  = 0;
	virtual E_VS_TYPE getType() const  = 0;
	virtual void onShaderUsed() = 0;			//when shader is used

	VSHADERCONSTCALLBACK		ShaderConstCallback;
};

class IPixelShader
{
public:
	IPixelShader(PSHADERCONSTCALLBACK callback) : ShaderConstCallback(callback) {}
	virtual ~IPixelShader() {}

public:
	virtual bool isValid() const  = 0;
	virtual E_PS_TYPE getType() const  = 0;
	virtual void onShaderUsed() = 0;		//when shader is used

	PSHADERCONSTCALLBACK		ShaderConstCallback;
};
