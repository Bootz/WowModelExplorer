#pragma once

#include "ITexture.h"

class ITextureWriter;

class CD3D11TextureLoader : public ITextureLoader
{
public:
	virtual ITexture* loadTexture( IImage* image, bool mipmap );
	virtual ITexture* loadTexture( IBLPImage* image, bool mipmap );
};

class CD3D11Texture : public ITexture
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D11Texture);

public:
	CD3D11Texture();
	~CD3D11Texture();
	CD3D11Texture( IBLPImage* blpimage, bool mipmap );
	CD3D11Texture( IImage* image, bool mipmap );		//from image format

	friend class CD3D11TextureLoader;

public:
	//ITexture
	virtual bool createEmptyTexture( dimension2du size, ECOLOR_FORMAT format );
	virtual void* lock(u32 level, u32& pitch, const recti* srcRect = NULL);
	virtual void unlock(u32 level);

	virtual dimension2du getSize() const { return TextureSize; }
	virtual ECOLOR_FORMAT getColorFormat() const { return ColorFormat; }
	virtual bool hasMipMaps() const { return HasMipMaps; }
	virtual bool isValid() const { return DXTexture!=NULL; }
	virtual bool isLockable() const { return false; }

	//video memory
	virtual bool createVideoTexture();
	virtual void releaseVideoTexture();

	ID3D11Texture2D* getDXTexture() const { return DXTexture; }
	ID3D11ShaderResourceView* getShaderResourceView() const { return SRView; }

public:
	virtual void onLost() {}
	virtual void onReset() {}

private:
	dimension2du getTextureSize(u32 level) const;

	bool createViews(DXGI_FORMAT format);
	bool createTexture( dimension2du size, ECOLOR_FORMAT format, bool mipmap = true );

	//blp
	void copyTexture( ITextureWriter* writer, IBLPImage* blpimage );
	bool copyBlpMipMaps( ITextureWriter* writer, u32 level = 1);

	//image
	void copyTexture( ITextureWriter* writer, IImage* image );
	bool createMipMaps( ITextureWriter* writer, u32 level = 1 );		

	void copy32BitMipMap(char* src, char* tgt,
		s32 width, s32 height,  s32 pitchsrc, s32 pitchtgt) const;

	dimension2du getMipMapSize(u32 level);

private:
	ID3D11Texture2D*		DXTexture;
	ID3D11ShaderResourceView*	SRView;
	IImage*		Image;
	IBLPImage*	BlpImage;

	u32	NumberOfMipLevels;
	dimension2du	TextureSize;
	ECOLOR_FORMAT	ColorFormat;

	bool	HasMipMaps;
	bool	IsBLP;
};