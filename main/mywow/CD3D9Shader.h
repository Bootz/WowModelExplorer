#pragma once

#include "IShader.h"
#include "core.h"
#include <list>

struct SConstDesc
{
	bool operator<(const SConstDesc& other) const
	{
		return index < other.index;
	}

	c8	name[32];
	u32 index;		//register index in dx9
	u32 size;			//const size
};

class CD3D9VertexShader : public IVertexShader
{
private:
	CD3D9VertexShader(E_VS_TYPE type, IDirect3DVertexShader9* vs, VSHADERCONSTCALLBACK callback);
	
	~CD3D9VertexShader();

	typedef std::list<SConstDesc, qzone_allocator<SConstDesc>>		T_ConstList;
	
	T_ConstList& getConstList() { return ConstList; }

public:
	virtual E_VS_TYPE getType() const { return Type; }
	virtual bool isValid() const { return VertexShader != NULL; }
	virtual void onShaderUsed() {}

	u32 getConstantCount() const { return ConstList.size(); }
	const SConstDesc* getConstantDesc(const c8* name) const;

	IDirect3DVertexShader9* getDXVShader() const { return VertexShader; }
	void setShaderConstant(const SConstDesc* desc, const void* srcData, u32 size);

private:
	IDirect3DDevice9*	pID3DDevice;
	IDirect3DVertexShader9*	VertexShader;
	E_VS_TYPE	Type;

	T_ConstList		ConstList;

	friend class CD3D9ShaderServices;
};

class CD3D9PixelShader : public IPixelShader
{
private:
	CD3D9PixelShader(E_PS_TYPE type, IDirect3DPixelShader9* ps, PSHADERCONSTCALLBACK callback); 

	~CD3D9PixelShader();

	typedef std::list<SConstDesc, qzone_allocator<SConstDesc>>		T_ConstList;

	T_ConstList& getConstList() { return ConstList; }

public:
	virtual E_PS_TYPE getType() const { return Type; }
	virtual bool isValid() const { return PixelShader != NULL; }
	virtual void onShaderUsed() {}

	u32 getConstantCount() const { return ConstList.size(); }
	const SConstDesc* getConstantDesc(const c8* name) const;

	IDirect3DPixelShader9* getDXPShader() const { return PixelShader; }
	void setShaderConstant(const SConstDesc* desc, const void* srcData, u32 size);

private:
	IDirect3DDevice9*	pID3DDevice;
	IDirect3DPixelShader9*		PixelShader;
	E_PS_TYPE	Type;

	T_ConstList		ConstList;

	friend class CD3D9ShaderServices;
};

