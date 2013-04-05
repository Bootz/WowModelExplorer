#pragma once

#include "ITexture.h"

class ITextureWriter;

class CD3D9TextureLoader : public ITextureLoader
{
public:
	virtual ITexture* loadTexture( IImage* image, bool mipmap );
	virtual ITexture* loadTexture( IBLPImage* image, bool mipmap);
};

//创建静态纹理，动态render target
class CD3D9Texture : public ITexture
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D9Texture);
public:
	CD3D9Texture();
	~CD3D9Texture();
	CD3D9Texture( IBLPImage* blpimage, bool mipmap );
	CD3D9Texture( IImage* image, bool mipmap );		//from image format

	friend class CD3D9TextureLoader;

public:
	//ITexture
	virtual bool createEmptyTexture( dimension2du size, ECOLOR_FORMAT format );
	virtual void* lock(u32 level, u32& pitch, const recti* srcRect = NULL);
	virtual void unlock(u32 level);

	virtual dimension2du getSize() const { return TextureSize; }
	virtual ECOLOR_FORMAT getColorFormat() const { return ColorFormat; }
	virtual bool hasMipMaps() const { return HasMipMaps; }
	virtual bool isValid() const { return DXTexture!=NULL; }
	virtual bool isLockable() const;

	//video memory
	virtual bool createVideoTexture();
	virtual void releaseVideoTexture();

	//
	IDirect3DTexture9*  getDXTexture() const { return DXTexture; }

private:
	dimension2du getTextureSize(u32 level) const;

	bool createTexture( dimension2du size, ECOLOR_FORMAT format, bool mipmap = true );
	
	//blp
	void copyTexture( ITextureWriter* writer, IBLPImage* blpimage );
	bool copyBlpMipMaps( ITextureWriter* writer, u32 level = 1);

	//image
	void copyTexture( ITextureWriter* writer, IImage* image );
	bool createMipMaps( ITextureWriter* writer, u32 level = 1 );		

	void copyA8L8MipMap(char* src, char* tgt,
		s32 width, s32 height,  s32 pitchsrc, s32 pitchtgt) const;
	void copy16BitMipMap(char* src, char* tgt,
		s32 width, s32 height,  s32 pitchsrc, s32 pitchtgt) const;
	static void copy32BitMipMap(char* src, char* tgt,
		s32 width, s32 height,  s32 pitchsrc, s32 pitchtgt);

private:
	IDirect3DTexture9*		DXTexture;
	IImage*		Image;
	IBLPImage*	BlpImage;

	dimension2du	TextureSize;
	ECOLOR_FORMAT	ColorFormat;

	bool	HasMipMaps;
	bool	IsBLP;
};