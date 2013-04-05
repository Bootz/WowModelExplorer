#pragma once

#include "IMaterialRenderServices.h"
#include "CD3D11Structs.h"

class CD3D11Driver;

class CD3D11MaterialRenderServices : public IMaterialRenderServices
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D11MaterialRenderServices);

public:
	CD3D11MaterialRenderServices();
	~CD3D11MaterialRenderServices();

public:
	virtual void setBasicRenderStates( const SMaterial& material,
		const SMaterial& lastMaterial,
		bool resetAllRenderstates );

	virtual void setOverrideRenderStates( const SOverrideMaterial& overrideMaterial,
		bool resetAllRenderStates );

	virtual bool isFFPipeline() const { return false; }

	virtual IMaterialRenderer* getMaterialRenderer( E_MATERIAL_TYPE type );

	virtual void set2DRenderStates( const S2DBlendParam& blendParam, bool resetAllRenderStates);

	virtual const S2DBlendParam& getCurrent2DBlendParam() const { return Last2DBlendParam; }
	virtual IPixelShader* getCurrentPixelShader() { return LastMaterialBlock.pixelShader; }

	virtual void applyMaterialBlock( const SRenderStateBlock& block, bool resetAllRenderStates );

	virtual void setPixelShaderMaterialBlock(SRenderStateBlock& block, E_PS_TYPE psType, E_VERTEX_TYPE vType);

	virtual void applyMaterialChanges();

	virtual ITexture* getSampler_Texture(u32 st) const { return CurrentRenderState.TextureUnits[st].texture; }
	virtual void setSampler_Texture(u32 st, ITexture* tex);
	virtual void setTextureWrap(u32 st, E_TEXTURE_ADDRESS address, E_TEXTURE_CLAMP wrap);
	virtual E_TEXTURE_CLAMP getTextureWrap(u32 st, E_TEXTURE_ADDRESS address) const;

	virtual const SRenderStateBlock& getRenderStateBlock() const { return LastMaterialBlock; }

public:
	//bind states to pipeline
	ID3D11BlendState*  getBlendState();
	ID3D11RasterizerState* getRasterizerState();
	ID3D11DepthStencilState* getDepthStencilState();
	ID3D11SamplerState* getSamplerState(u32 index);

	//state
private:
	typedef std::map<SD3D11_BLEND_DESC, ID3D11BlendState*, std::less<SD3D11_BLEND_DESC>, qzone_allocator<std::pair<SD3D11_BLEND_DESC, ID3D11BlendState*>>> T_BlendStateMap;
	typedef std::map<SD3D11_RASTERIZER_DESC, ID3D11RasterizerState*, std::less<SD3D11_RASTERIZER_DESC>, qzone_allocator<std::pair<SD3D11_RASTERIZER_DESC, ID3D11RasterizerState*>>>	T_RasterizerStateMap;
	typedef std::map<SD3D11_DEPTH_STENCIL_DESC, ID3D11DepthStencilState*, std::less<SD3D11_DEPTH_STENCIL_DESC>, qzone_allocator<std::pair<SD3D11_DEPTH_STENCIL_DESC, ID3D11DepthStencilState*>>> T_DepthStencilStateMap;
	typedef std::map<SD3D11_SAMPLER_DESC, ID3D11SamplerState*, std::less<SD3D11_SAMPLER_DESC>, qzone_allocator<std::pair<SD3D11_SAMPLER_DESC, ID3D11SamplerState*>>> T_SamplerStateMap;

	T_BlendStateMap	BlendStateMap;
	T_RasterizerStateMap	RasterizerStateMap;
	T_DepthStencilStateMap  DepthStencilStateMap;
	T_SamplerStateMap		SamplerStateMap;

private:
	void resetRSCache();
	void clearStateMap();

	void set2DPixelShaderMaterialBlock(SRenderStateBlock& block, bool alpha, bool alphaChannel);

private:
	struct SRenderState			//current render state
	{
		SRenderState()
		{
			for (u32 i=0; i<MATERIAL_MAX_TEXTURES; ++i)
			{
				TextureUnits[i].texture = NULL;
				TextureUnits[i].SamplerDesc.reset();
			}
			BlendDesc.reset();
			RasterizerDesc.reset();
			DepthStencilDesc.reset();
		}

		struct STextureUnit
		{
			ITexture*	texture;

			SD3D11_SAMPLER_DESC		SamplerDesc;
		};

		SD3D11_BLEND_DESC	BlendDesc;
		SD3D11_RASTERIZER_DESC	RasterizerDesc;
		SD3D11_DEPTH_STENCIL_DESC DepthStencilDesc;

		STextureUnit	TextureUnits[MATERIAL_MAX_TEXTURES];
	};

	struct SRenderStateCache			//render stateµÄ»º´æ
	{
		//
		ID3D11BlendState*		BlendState;
		ID3D11RasterizerState*	RasterizerState;
		ID3D11DepthStencilState*	DepthStencilState;
	};

private:
	typedef std::map<E_MATERIAL_TYPE, IMaterialRenderer*, std::less<E_MATERIAL_TYPE>, qzone_allocator<std::pair<E_MATERIAL_TYPE, IMaterialRenderer*>>> T_MaterialRenderersMap;
	T_MaterialRenderersMap		MaterialRenderersMap;
	CD3D11Driver*	Driver;

	SRenderState		CurrentRenderState;

	SRenderStateCache	RsCache;

	SRenderStateBlock		LastMaterialBlock;					//»º´æmaterial block

	SOverrideMaterial		LastOverrideMaterial;

	S2DBlendParam	Last2DBlendParam;
};