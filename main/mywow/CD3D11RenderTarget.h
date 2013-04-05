#pragma once

#include "IRenderTarget.h"

class CD3D11RenderTarget : public IRenderTarget
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D11RenderTarget);

public:
	CD3D11RenderTarget(dimension2du size, ECOLOR_FORMAT format);
	~CD3D11RenderTarget();

public:
	virtual dimension2du getSize() const { return TextureSize; }
	virtual ECOLOR_FORMAT getColorFormat() const { return ColorFormat; }

	virtual bool isValid() const { return DXTexture != NULL; }

	//lost reset
	void onLost();
	void onReset();

	ID3D11Resource* getTextureResource() const { return DXTexture; }
	ID3D11RenderTargetView* getRenderTargetView() const { return RTView; }

private:
	bool createAsRenderTarget( dimension2du size, ECOLOR_FORMAT format, u32 antialias, u32 quality );
	void releaseVideoTexture();		//Îªlock,unlock´´½¨buffer

	bool createViews(DXGI_FORMAT format, bool multisample);

private:
	ID3D11Texture2D*		DXTexture;
	ID3D11Texture2D*		DepthTexture;
	ID3D11RenderTargetView*		RTView;
	ID3D11DepthStencilView*		DepthView;

	dimension2du	TextureSize;
	ECOLOR_FORMAT	ColorFormat;
};