#pragma  once

#include "base.h"
#include "IMaterialRenderServices.h"
#include <map>

class ITexture;
class CD3D9Driver;

class CD3D9MaterialRenderServices : public IMaterialRenderServices
{
public:
	explicit CD3D9MaterialRenderServices(bool ffpipeline);

public:
	virtual void setBasicRenderStates( const SMaterial& material,
		const SMaterial& lastMaterial,
		bool resetAllRenderstates );

	virtual void setOverrideRenderStates( const SOverrideMaterial& overrideMaterial,
		bool resetAllRenderStates );

	virtual bool isFFPipeline() const { return FFpipeline; }

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

	//render states
	void setDepthBias(f32 depthbias);
	f32 getDepthBias() const;

private:
	void ResetRSCache();

	void set2DPixelShaderMaterialBlock(SRenderStateBlock& block, bool alpha, bool alphaChannel);

private:
	struct SRenderStateCache		
	{
		struct STextureUnit
		{
			ITexture*	texture;

			DWORD		textureTransformFlags;
			DWORD		colorOp;
			DWORD		colorArg1;
			DWORD		colorArg2;
			DWORD		alphaOp;
			DWORD		alphaArg1;
			DWORD		alphaArg2;
			DWORD		texcoordIndex;

			DWORD		addressU;
			DWORD		addressV;
			DWORD		addressW;
			DWORD		maxAniso;
			DWORD		magFilter;
			DWORD		minFilter;
			DWORD		mipFilter;
			DWORD		mipLodBias;
		};

		DWORD	 Lighting;
		DWORD	 SpecularEnable;
		DWORD	 ZEnable;
		DWORD	 ZFunc;
		DWORD	 FillMode;
		DWORD	 ShadeMode;
		DWORD	 ZWriteEnable;
		DWORD	 StencilEnable;
		DWORD	 CullMode;
		DWORD	 FogEnable;
		DWORD	 MultiSampleAntiAlias;
		DWORD	 AntiAliasedLineEnable;
		DWORD	 SlopeScaleDepthBias;
		DWORD	 DepthBias;
		DWORD	 AlphaBlendEnable;
		DWORD	 BlendOp;
		DWORD	 SrcBlend;
		DWORD	 DestBlend;
		DWORD	 AlphaTestEnable;
		DWORD	 AlphaFunc;
		DWORD	 AlphaRef;
		DWORD	 AdaptivetessY;
		DWORD	 PointSize;

		STextureUnit	TextureUnits[MATERIAL_MAX_TEXTURES];
	};

private:
	typedef std::map<E_MATERIAL_TYPE, IMaterialRenderer*, std::less<E_MATERIAL_TYPE>, qzone_allocator<std::pair<E_MATERIAL_TYPE, IMaterialRenderer*>>> T_MaterialRenderersMap;
	T_MaterialRenderersMap		MaterialRenderersMap;

	CD3D9Driver*	Driver;
	IDirect3DDevice9*	pID3DDevice;
	bool	FFpipeline;

	SRenderStateCache	CurrentRenderState;

	SRenderStateCache	RsCache;

	SRenderStateBlock		LastMaterialBlock;					//»º´æmaterial block

	SOverrideMaterial		LastOverrideMaterial;

	S2DBlendParam	Last2DBlendParam;
};