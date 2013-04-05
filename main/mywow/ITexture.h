#pragma once

#include "core.h"
#include "IResourceCache.h"

class IImage;
class IBLPImage;
class ITexture;

class ITextureLoader
{
public:
	~ITextureLoader() { }

public:
	virtual ITexture* loadTexture( IImage* image, bool mipmap ) = 0;
	virtual ITexture* loadTexture( IBLPImage* image, bool mipmap) = 0;
};

class ITexture : public IReferenceCounted<ITexture>
{
protected:
	virtual void onRemove() 
	{
		releaseVideoTexture();
	}

public:
	ITexture() : VideoBuilt(false) {}
	virtual ~ITexture() { }

public:
	virtual bool createEmptyTexture( dimension2du size, ECOLOR_FORMAT format ) = 0;
	virtual void* lock(u32 level, u32& pitch, const recti* srcRect = NULL) = 0;
	virtual void unlock(u32 level) = 0;

	virtual dimension2du getSize() const = 0;
	virtual ECOLOR_FORMAT getColorFormat() const = 0;
	virtual bool hasMipMaps() const = 0;;
	virtual bool isLockable() const = 0;

	virtual bool isValid() const = 0;

	//video memory
	virtual bool createVideoTexture() = 0;
	virtual void releaseVideoTexture() = 0;

protected:
	bool VideoBuilt;
};