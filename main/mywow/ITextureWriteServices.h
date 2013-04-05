#pragma once

#include "core.h"
#include "ILostResetCallback.h"

class ITexture;

//��d3d9�У�������managed����(lockable)��textureWriter�������һ������
//��d3d9ex, d3d10, d3d11�У�����������Դ�����(unlockable)��textureWriter����ר�����ڴ�����д�Դ�����Ĺ���
class ITextureWriter
{
public:
	virtual ~ITextureWriter() {}

public:
	virtual void* lock(u32 level, u32& pitch) = 0;
	virtual void unlock(u32 level) = 0;
	virtual bool copyToTexture(ITexture* texture, const recti* descRect = NULL) = 0;

public:
	dimension2du	TextureSize;
	ECOLOR_FORMAT	ColorFormat;
	bool HasMipmap;
};

class ITextureWriteServices
{
public:
	virtual ~ITextureWriteServices() {}

public:
	virtual ITextureWriter* getTextureWriter(ITexture* texture)= 0;
};