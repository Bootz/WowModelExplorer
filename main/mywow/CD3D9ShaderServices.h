#pragma once

#include "IShaderServices.h"
#include <map>
#include "CD3D9_VS20.h"
#include "CD3D9_VS30.h"
#include "CD3D9_PS20.h"
#include "CD3D9_PS30.h"

class CD3D9VertexShader;
class CD3D9PixelShader;
class CD3D9Driver;

class CD3D9ShaderServices : public IShaderServices
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D9ShaderServices);

public:
	CD3D9ShaderServices();
	~CD3D9ShaderServices();

public:
	virtual void onLost();
	virtual void onReset();

public:
	virtual bool loadVShader( const c8* filename, E_VS_TYPE type, VSHADERCONSTCALLBACK callback );
	virtual bool loadPShader( const c8* filename, E_PS_TYPE type, PSHADERCONSTCALLBACK callback );
	virtual bool loadVShaderHLSL( const c8* filename, const c8* entry, const c8* profile, E_VS_TYPE type, VSHADERCONSTCALLBACK callback );
	virtual bool loadPShaderHLSL( const c8* filename, const c8* entry, const c8* profile, E_PS_TYPE type, PSHADERCONSTCALLBACK callback );

	virtual void useVertexShader(IVertexShader* vshader);
	virtual void usePixelShader(IPixelShader* pshader);
	virtual void setShaderConstants(IVertexShader* vs, const SMaterial& material, u32 pass);
	virtual void setShaderConstants(IPixelShader* ps, const SMaterial& material, u32 pass);

	virtual void getWVPMatrix(matrix4& mat) const;
	virtual void getWVMatrix(matrix4& mat) const;
	virtual void getVPMatrix(matrix4& mat) const;

public:
	virtual IVertexShader* getVertexShader(E_VS_TYPE type);
	virtual IPixelShader* getPixelShader(E_PS_TYPE type);
	virtual IVertexShader* getDefaultVertexShader(E_VERTEX_TYPE vType);
	virtual IPixelShader* getDefaultPixelShader(E_VERTEX_TYPE vType);

private:
	void loadAll();

	struct SShaderCache
	{
		void reset()
		{
			vshader = NULL;
			pshader = NULL;
		}

		IDirect3DVertexShader9*		vshader;
		IDirect3DPixelShader9*	pshader;
	};

private:
	SShaderCache ShaderCache;

	CD3D9_VS20 vs20Loader;
	CD3D9_VS30 vs30Loader;
	CD3D9_PS20 ps20Loader;
	CD3D9_PS30 ps30Loader;

private:
	typedef std::map<E_VS_TYPE, CD3D9VertexShader*, std::less<E_VS_TYPE>, qzone_allocator<std::pair<E_VS_TYPE, CD3D9VertexShader*>>> T_VertexShaderMap;
	T_VertexShaderMap		VertexShaderMap;

	typedef std::map<E_PS_TYPE, CD3D9PixelShader*, std::less<E_PS_TYPE>, qzone_allocator<std::pair<E_PS_TYPE, CD3D9PixelShader*>>> T_PixelShaderMap;
	T_PixelShaderMap		PixelShaderMap;

	IDirect3DDevice9*		Device;
	CD3D9Driver*	Driver;
};