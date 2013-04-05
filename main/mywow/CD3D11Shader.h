#pragma once

#include "core.h"
#include "IShader.h"
#include <list>

class CD3D11Driver;

struct SConstDesc11 
{
	bool operator<(const SConstDesc11& other) const
	{
		return index < other.index;
	}

	c8 name[32];
	u32 index;		//register index in dx9, cbuffer/tbuffer index in dx11
	u32 size;			//const size
	bool tbuffer;		//is tbuffer ? 
	ID3D11Buffer*	constBuffer;
	ID3D11ShaderResourceView*	shaderResourceView;		//for tbuffer
};

struct SSamplerDesc11
{
	bool operator<(const SSamplerDesc11& other) const
	{
		return index < other.index;
	}

	c8 name[32];
	u32 index;
	u32 count;
};

struct STextureDesc11
{
	bool operator<(const STextureDesc11& other) const
	{
		return index < other.index;
	}

	c8 name[32];
	u32 index;
	u32 count;
};

class CD3D11VertexShader : public IVertexShader
{
private:
	CD3D11VertexShader(E_VS_TYPE type, ID3D11VertexShader* vs, VSHADERCONSTCALLBACK callback, const void* codeBuffer, u32 codeSize);

	~CD3D11VertexShader();

	typedef std::list<SConstDesc11, qzone_allocator<SConstDesc11>>		T_BufferList;
	typedef std::list<SSamplerDesc11, qzone_allocator<SSamplerDesc11>>		T_SamplerList;
	typedef std::list<STextureDesc11, qzone_allocator<STextureDesc11>>		T_TextureList;

	T_BufferList& getCBufferList() { return CBufferList; }
	T_BufferList& getTBufferList() { return TBufferList; }
	T_SamplerList& getSamplerList() { return SamplerList; }
	T_TextureList& getTextureList() { return TextureList; }

	SConstDesc11* getConstantDesc(u32 index);

public:
	virtual E_VS_TYPE getType() const { return Type; }
	virtual bool isValid() const { return VertexShader != NULL; }
	virtual void onShaderUsed();

	u32 getConstantCount() const { return CBufferList.size() + TBufferList.size(); }
	const SConstDesc11* getConstantDesc(const c8* name) const;
	u32 getTextureCount() const { return TextureList.size(); }
	const STextureDesc11* getTextureDesc(const c8* name) const;
	u32 getSamplerCount() const { return SamplerList.size(); }
	const SSamplerDesc11* getSamplerDesc(const c8* name) const;

	ID3D11VertexShader* getDXVShader() const { return VertexShader; }
	const void* getCodeBuffer() const { return CodeBuffer; }
	u32 getCodeSize() const { return CodeSize; }
	void setShaderConstant(const SConstDesc11* desc, const void* srcData, u32 size);

private:
	CD3D11Driver*		Driver;
	ID3D11VertexShader*			VertexShader;
	E_VS_TYPE	Type;

	T_BufferList		CBufferList;
	T_BufferList		TBufferList;
	T_SamplerList		SamplerList;
	T_TextureList		TextureList;

	void*	CodeBuffer;
	u32		CodeSize;

	friend class CD3D11ShaderServices;

};

class CD3D11PixelShader : public IPixelShader
{
private:
	CD3D11PixelShader(E_PS_TYPE type, ID3D11PixelShader* ps, PSHADERCONSTCALLBACK callback); 

	~CD3D11PixelShader();

	typedef std::list<SConstDesc11, qzone_allocator<SConstDesc11>>		T_BufferList;
	typedef std::list<SSamplerDesc11, qzone_allocator<SSamplerDesc11>>	T_SamplerList;
	typedef std::list<STextureDesc11, qzone_allocator<STextureDesc11>>		T_TextureList;

	T_BufferList& getCBufferList() { return CBufferList; }
	T_BufferList& getTBufferList() { return TBufferList; }
	T_SamplerList& getSamplerList() { return SamplerList; }
	T_TextureList& getTextureList() { return TextureList; }

	SConstDesc11* getConstantDesc(u32 index);

public:
	virtual E_PS_TYPE getType() const { return Type; }
	virtual bool isValid() const { return PixelShader != NULL; }
	virtual void onShaderUsed();

	u32 getConstantCount() const { return CBufferList.size() + TBufferList.size(); }
	const SConstDesc11* getConstantDesc(const c8* name) const;
	u32 getTextureCount() const { return TextureList.size(); }
	const STextureDesc11* getTextureDesc(const c8* name) const;
	u32 getSamplerCount() const { return SamplerList.size(); }
	const SSamplerDesc11* getSamplerDesc(const c8* name) const;

	ID3D11PixelShader* getDXPShader() const { return PixelShader; }
	void setShaderConstant(const SConstDesc11* desc, const void* srcData, u32 size);

private:
	CD3D11Driver*	Driver;
	ID3D11PixelShader*		PixelShader;
	E_PS_TYPE	Type;

	T_BufferList		CBufferList;
	T_BufferList		TBufferList;
	T_SamplerList		SamplerList;
	T_TextureList		TextureList;

	friend class CD3D11ShaderServices;

};