#pragma once

#include "ITextureWriteServices.h"
#include "core.h"
#include <list>

class CD3D9Driver;

class CD3D9TextureWriter : public ITextureWriter
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D9TextureWriter);

	CD3D9TextureWriter(dimension2du size, ECOLOR_FORMAT format, bool mipmap);
	CD3D9TextureWriter();
	~CD3D9TextureWriter();

	void setSourceTexture(ITexture* texture);

	friend class CD3D9TextureWriteServices;

public:
	virtual void* lock(u32 level, u32& pitch);
	virtual void unlock(u32 level);
	virtual bool copyToTexture(ITexture* texture, const recti* descRect = NULL);

private:
	IDirect3DTexture9*	 SrcTexture;
	CD3D9Driver*	Driver;
	bool NeedCreate;
};


class CD3D9TextureWriteServices : public ITextureWriteServices
{
public:
	CD3D9TextureWriteServices();
	~CD3D9TextureWriteServices();
public:
	virtual ITextureWriter* getTextureWriter(ITexture* texture);

private:
	typedef std::list<ITextureWriter*, qzone_allocator<ITextureWriter*>>	T_TextureWriterList;
	T_TextureWriterList	TextureWriters;
	CD3D9TextureWriter*		SelfTextureWriter;
};