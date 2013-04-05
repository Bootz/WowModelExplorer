#pragma once

#include "ITextureWriteServices.h"
#include "core.h"
#include <list>

class CD3D11Driver;

class CD3D11TextureWriter : public ITextureWriter
{
private:
	CD3D11TextureWriter(dimension2du size, ECOLOR_FORMAT format, bool mipmap);
	~CD3D11TextureWriter();

	friend class CD3D11TextureWriteServices;

public:
	virtual void* lock(u32 level, u32& pitch);
	virtual void unlock(u32 level);
	virtual bool copyToTexture(ITexture* texture, const recti* descRect = NULL);

private:
	CD3D11Driver*		Driver;
	ID3D11Texture2D*	SrcTexture;
};

class CD3D11TextureWriteServices : public ITextureWriteServices
{
public:
	CD3D11TextureWriteServices();
	~CD3D11TextureWriteServices();
public:
	virtual ITextureWriter* getTextureWriter(ITexture* texture);

private:
	typedef std::list<ITextureWriter*, qzone_allocator<ITextureWriter*>>	T_TextureWriterList;
	T_TextureWriterList	TextureWriters;
};