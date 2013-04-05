#pragma once

#include "core.h"
#include "IResourceCache.h"
#include "wow_adt_structs.h"
#include <list>

class IVertexBuffer;
class ITexture;

struct MHDR {
	enum MHDRFlags {
		mhdr_MFBO = 1,                // contains a MFBO chunk.
		mhdr_northrend = 2,           // is set for some northrend ones.
	};
	u32 flags;
	u32* mcin;
	u32* mtex;
	u32* mmdx;
	u32* mmid;
	u32* mwmo;
	u32* mwid;
	u32* mddf;
	u32* modf;
	u32* mfbo;                     // this is only set if flags & mhdr_MFBO.
	u32* mh2o;
	u32* mtfx;
	u32 unused[4];
};

struct SChunkSound
{
	SChunkSound() : soundID(-1) {}

	s32 soundID;			//SoundEntriesAdvanced.dbc
	vector3df pos;
	vector3df range;
};

class CMapChunk
{
private:
	DISALLOW_COPY_AND_ASSIGN(CMapChunk);

public:
	CMapChunk() : sounds(NULL), numTextures(0), numAlphaMap(0)
	{ 
		::memset(textures,0, sizeof(ITexture*)*4);
		areaID = 0;
		xbase = ybase = zbase = 0;

		::memset(mclys, 0, sizeof(mclys));

		data_shadowmap = NULL;
		shadowmap = NULL;
		for (u32 i=0; i<3; ++i)
		{
			data_alphamap[i] = NULL;
			alphamap[i] = NULL;
		}
		data_blendmap = new u8[64 * 64 * 4];
		memset(data_blendmap, 0, 64 * 64 * 4);
		//blendmap = NULL;
	}

	~CMapChunk()
	{
		delete[] sounds;
		delete[] data_shadowmap;
		for (u32 k=0; k<3; ++k)
		{
			delete[] data_alphamap[k];
		}
		delete[] data_blendmap;
	}

public:
	u32	areaID;
	aabbox3df	box;
	f32	xbase, ybase, zbase;
		
	u32		numTextures;
	u32		numAlphaMap;

	u8*		data_shadowmap;
	u8*		data_alphamap[3];
	u8*		data_blendmap;

	ITexture*	textures[4];
	ITexture*	shadowmap;
	ITexture*	alphamap[3];
	//sound
	SChunkSound*		sounds;	

	ADT::MCLY	mclys[4];

	bool hasSameTexture(const CMapChunk& other) const
	{
		if (numTextures != other.numTextures)
			return false;
		for (u32 i=0; i<numTextures; ++i)
		{
			if (textures[i] != other.textures[i])
				return false;
		}
		return true;
	}

};

class MPQFile;
class IFileM2;
class IFileWMO;

//maptile
class IFileADT : public IReferenceCounted<IFileADT>
{
private:
	virtual void onRemove() 
	{
		releaseVideoResources(); 
	}

public:
	IFileADT() : VideoBuilt(false)
	{
		WmoInstances = NULL;
		M2Instances = NULL;
		M2FileNameIndices = NULL;
		M2FileNameBlock = NULL;
		WmoFileNameIndices = NULL;
		WmoFileNameBlock = NULL;

		NumWmoInstance = NumM2Instance = 
		NumWmoFileNames = NumM2FileNames = 0;

		::memset(Name, 0, sizeof(Name));
		Row = Col = 0;
	}

	virtual ~IFileADT() { }

public:
	struct SWmoInstance
	{
		u32 wmoIndex;
		s32 id;
		vector3df pos;
		vector3df dir;
		aabbox3df		box;
		f32		scale;
		u16		doodadset;
		u16		nameset;
	};

	struct SM2Instance
	{
		u32 m2Index;
		u32 id;
		vector3df	dir;
		vector3df	position;
		f32	scale;
	};

public:
	virtual void SetPosition(u8 row, u8 col) { Row = row; Col = col; }
	virtual bool loadFile(MPQFile* file) = 0;
	virtual bool loadFileSimple(MPQFile* file) = 0;
	virtual u8* getFileData() const = 0;
	virtual const CMapChunk* getChunk(u8 row, u8 col) const = 0;
	virtual aabbox3df getBoundingBox() const = 0;
	
	virtual const c8* getM2FileName(u32 index) const = 0;
	virtual const c8* getWMOFileName(u32 index) const = 0;

	virtual bool buildVideoResources() = 0;
	virtual void releaseVideoResources() = 0;

	virtual IVertexBuffer* getVBuffer() const = 0;
	virtual E_VERTEX_TYPE getVertexType() const = 0;
	virtual u32 getChunkVerticesOffset(u8 row, u8 col) const = 0;
	virtual ITexture* getBlendMap() const = 0;

	virtual const SM2Instance* getM2Instance(u32 index) const = 0;
	virtual const SWmoInstance* getWMOInstance(u32 index) const = 0;

protected:
	SM2Instance*		M2Instances;
	SWmoInstance*		WmoInstances;

	u32* M2FileNameIndices;
	c8*	M2FileNameBlock;	

	u32*  WmoFileNameIndices;
	c8*	WmoFileNameBlock;

public:
	u32 NumWmoInstance;
	
	u32 NumM2Instance;
	
	u32 NumM2FileNames;
	
	u32 NumWmoFileNames;		
	
protected:
	c8			Name[MAX_PATH];
	u8		Row;
	u8		Col;
	bool		VideoBuilt;
};