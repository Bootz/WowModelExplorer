#pragma once

#include <d3d11.h>

struct SD3D11_BLEND_DESC : public D3D11_BLEND_DESC
{
	SD3D11_BLEND_DESC()
	{
		reset();
	}

	inline bool operator==(const SD3D11_BLEND_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_BLEND_DESC) ) == 0;
	}

	inline bool operator!=(const SD3D11_BLEND_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_BLEND_DESC) ) != 0;
	}

	inline bool operator<(const SD3D11_BLEND_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_BLEND_DESC) ) < 0;
	}

	inline void reset()
	{
		AlphaToCoverageEnable = FALSE;
		IndependentBlendEnable = FALSE;
		RenderTarget[0].BlendEnable = FALSE;
		RenderTarget[0].SrcBlend	= D3D11_BLEND_ONE;
		RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		for (u32 i=1; i<8; ++i)
		{
			RenderTarget[i] = RenderTarget[0];
		}
	}
};

struct SD3D11_RASTERIZER_DESC : public D3D11_RASTERIZER_DESC
{
	SD3D11_RASTERIZER_DESC()
	{
		reset();
	}

	inline bool operator==(const SD3D11_RASTERIZER_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_RASTERIZER_DESC) ) == 0;
	}

	inline bool operator!=(const SD3D11_RASTERIZER_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_RASTERIZER_DESC) ) != 0;
	}

	inline bool operator<(const SD3D11_RASTERIZER_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_RASTERIZER_DESC) ) < 0;
	}

	inline void reset()
	{
		FillMode = D3D11_FILL_SOLID;
		CullMode = D3D11_CULL_BACK;
		FrontCounterClockwise = FALSE;
		DepthBias = 0;
		DepthBiasClamp = 0;
		SlopeScaledDepthBias = 0;
		DepthClipEnable = TRUE;
		ScissorEnable = FALSE;
		MultisampleEnable = FALSE;
		AntialiasedLineEnable = FALSE;
	}
};

struct SD3D11_DEPTH_STENCIL_DESC : public D3D11_DEPTH_STENCIL_DESC
{
	SD3D11_DEPTH_STENCIL_DESC()
	{
		reset();
	}

	inline bool operator==(const SD3D11_DEPTH_STENCIL_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_DEPTH_STENCIL_DESC) ) == 0;
	}

	inline bool operator!=(const SD3D11_DEPTH_STENCIL_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_DEPTH_STENCIL_DESC) ) != 0;
	}

	inline bool operator<(const SD3D11_DEPTH_STENCIL_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_DEPTH_STENCIL_DESC) ) < 0;
	}

	inline void reset()
	{
		DepthEnable = TRUE;
		DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DepthFunc = D3D11_COMPARISON_LESS;
		StencilEnable = FALSE;
		StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	}
};

struct SD3D11_SAMPLER_DESC : public D3D11_SAMPLER_DESC
{
	SD3D11_SAMPLER_DESC()
	{
		reset();
	}

	inline bool operator==(const SD3D11_SAMPLER_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_SAMPLER_DESC) ) == 0;
	}

	inline bool operator!=(const SD3D11_SAMPLER_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_SAMPLER_DESC) ) != 0;
	}

	inline bool operator<(const SD3D11_SAMPLER_DESC& other) const
	{
		return memcmp(this, &other, sizeof(SD3D11_SAMPLER_DESC) ) < 0;
	}

	inline void reset()
	{
		Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		MipLODBias = 0;
		MaxAnisotropy = 16;
		ComparisonFunc = D3D11_COMPARISON_NEVER;
		MinLOD = 0.0f;
		MaxLOD = D3D11_FLOAT32_MAX;
	}
};