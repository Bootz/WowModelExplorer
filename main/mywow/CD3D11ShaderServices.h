#pragma once

#include "IShaderServices.h"
#include <map>
#include <set>
#include "CD3D11_VS40.h"
#include "CD3D11_VS50.h"
#include "CD3D11_PS40.h"
#include "CD3D11_PS50.h"

class CD3D11VertexShader;
class CD3D11PixelShader;
class CD3D11Driver;
struct SConstDesc11;

enum E_CB_TYPE
{
	ECBT_CONSTANT = 0,
	ECBT_TEXTURE,

	ECBT_COUNT,
};

enum E_CB_CATEGORY
{
	ECBC_PERSCENE = 0,
	ECBC_PEROBJECT,
	ECBC_PERFRAME,

	ECBC_COUNT,
};

class CD3D11ShaderServices : public IShaderServices
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D11ShaderServices);

public:
	CD3D11ShaderServices();
	~CD3D11ShaderServices();

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

	virtual IVertexShader* getVertexShader(E_VS_TYPE type);
	virtual IPixelShader* getPixelShader(E_PS_TYPE type);
	virtual IVertexShader* getDefaultVertexShader(E_VERTEX_TYPE vType);
	virtual IPixelShader* getDefaultPixelShader(E_VERTEX_TYPE vType);

private:
	struct SConstantBuffer
	{
		bool operator<(const SConstantBuffer& other) const
		{
			return size < other.size;
		}
		u32 size;
		ID3D11Buffer*	constBuffer;
		ID3D11ShaderResourceView*	shaderResourceView;		//for tbuffer
	};

	const SConstantBuffer* getConstantBuffer(const SConstDesc11* desc) const; 

	void loadAll();

	void buildConstantBuffers();
	void releaseConstantBuffers();
	void buildTextureBuffers();
	void releaseTextureBuffers();

	void assignBuffersToShaders();

	typedef std::set<SConstantBuffer, std::less<SConstantBuffer>, qzone_allocator<SConstantBuffer>>	T_ConstanBufferSet;

	const T_ConstanBufferSet& getBufferSet(const SConstDesc11* desc) const;
	E_CB_CATEGORY getBufferCategory(const SConstDesc11* desc) const;

	struct SShaderCache
	{
		void reset()
		{
			vshader = NULL;
			pshader = NULL;
		}

		ID3D11VertexShader*		vshader;
		ID3D11PixelShader*		pshader;
	};

	SShaderCache ShaderCache;

	CD3D11_VS40 vs40Loader;
	CD3D11_VS50 vs50Loader;
	CD3D11_PS40 ps40Loader;
	CD3D11_PS50 ps50Loader;

private:
	typedef std::map<E_VS_TYPE, CD3D11VertexShader*, std::less<E_VS_TYPE>, qzone_allocator<std::pair<E_VS_TYPE, CD3D11VertexShader*>>> T_VertexShaderMap;
	T_VertexShaderMap		VertexShaderMap;

	typedef std::map<E_PS_TYPE, CD3D11PixelShader*, std::less<E_PS_TYPE>, qzone_allocator<std::pair<E_PS_TYPE, CD3D11PixelShader*>>> T_PixelShaderMap;
	T_PixelShaderMap		PixelShaderMap;

	ID3D11Device*		Device;
	CD3D11Driver*		Driver;

	typedef std::set<u32, std::less<u32>, qzone_allocator<u32>>		T_Set;

	T_ConstanBufferSet	BufferMaps[ECBT_COUNT][ECBC_COUNT];
};