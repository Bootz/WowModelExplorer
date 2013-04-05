#pragma once

#include "IRenderTarget.h"

class CD3D9RenderTarget : public IRenderTarget
{
public:
	CD3D9RenderTarget(dimension2du size, ECOLOR_FORMAT format);
	~CD3D9RenderTarget();

public:
	virtual dimension2du getSize() const { return TextureSize; }
	virtual ECOLOR_FORMAT getColorFormat() const { return ColorFormat; }

	virtual bool isValid() const { return RTTSurface != NULL; }

	//lost reset
	void onLost();
	void onReset();

	//
	IDirect3DSurface9*	getRTTSurface() const { return RTTSurface; }
	IDirect3DSurface9* getRTTDepthSurface() const { return DepthSurface; }

private:
	bool createAsRenderTarget( dimension2du size, ECOLOR_FORMAT format, u32 antialias, u32 quality);
	void releaseVideoTexture();

private:
	IDirect3DSurface9*		RTTSurface;
	IDirect3DSurface9*		DepthSurface;

	dimension2du	TextureSize;
	ECOLOR_FORMAT	ColorFormat;
};