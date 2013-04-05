#pragma once

#include "core.h"
#include "IResourceCache.h"
#include "wow_wmo_structs.h"
#include "S3DVertex.h"
#include "SColor.h"

class ITexture;

struct SWMOMaterial
{
	SWMOMaterial() : texture0(NULL), texture1(NULL)
	{
		flags = 0;
		alphatest = false;
	}
	u32 flags;
	bool alphatest;
	ITexture* texture0;
	ITexture* texture1;
	SColor color0;
	SColor color1;
};

struct SWMOBatch
{
	u32 indexStart;
	u16 indexCount;
	u16 vertexStart;
	u16 vertexEnd;
	u8 matId;

	aabbox3df box;
};

class IFileWMO;
class IIndexBuffer;
class IVertexBuffer;

struct SWMOGroup
{
	SWMOGroup()
	{
		flags = 0;
		name = NULL;

		Indices = NULL;
		Vertices = NULL;
		Batches = NULL;
		Lights = NULL;
		Doodads = NULL;

		IndexBuffer = NULL;
		VertexBuffer = NULL;

		NumBatches = NumLights = NumDoodads = 0;	
		VCount = ICount = 0;
	}

	bool loadFile(u32 index, IFileWMO* wmo);

	u32		flags;
	u32		NumBatches;
	u32		NumLights;
	u32		NumDoodads;
	u32		ICount;
	u32		VCount;

	vector3df b1, b2;
	aabbox3df		box;
	c8*		name;
	SWMOBatch*	Batches;
	u16*		Lights;
	u16*		Doodads;
	u16*		Indices;
	SVertex_PNCT2*	 Vertices;

	IVertexBuffer*		VertexBuffer;
	IIndexBuffer*		IndexBuffer;
};

struct SWMOPortal
{
	u16 vStart;
	u16 vCount;
	vector3df	normal;
};

struct SWMOLight
{
	E_LIGHT_TYPE lighttype;
	SColor color;
	vector3df position;
	f32 intensity;
	f32 attenStart, attenEnd;
};

struct SWMODoodadSet
{
	c8 name[20];
	u32 start;
	u32 count;
};

struct SWMODoodad
{
	c8* name;
	vector3df position;
	quaternion quat;
	f32 scale;
	SColor color;
};

struct SWMOFog
{
	vector3df position;
	f32 radius1, radius2;
	f32 fogend, fogstart;
	SColor color;
};

class MPQFile;

class IFileWMO : public IReferenceCounted<IFileWMO>
{
protected:
	virtual void onRemove() 
	{
		releaseVideoResources(); 
	}

public:
	IFileWMO() : VideoBuilt(false)
	{
		TextureFileNameBlock = NULL;
		Materials = NULL;
		GroupNamesBlock = NULL;
		Groups = NULL;
		PortalVertices = NULL;
		Portals = NULL;
		Lights = NULL;
		DoodadSets = NULL;
		ModelNamesBlock = NULL;
		Doodads = NULL;
		Fogs = NULL;

		NumDoodads = NumPortalVertices = NumFogs = 0;

		::memset(Name, 0, sizeof(Name));
		::memset(&Header, 0, sizeof(Header));
	}

	virtual ~IFileWMO() {}

public:
	virtual bool loadFile(MPQFile* file) = 0;
	virtual u8* getFileData() const = 0;
	virtual aabbox3df getBoundingBox() const = 0;

	virtual bool buildVideoResources() = 0;
	virtual void releaseVideoResources() = 0;

public:
	c8		Name[MAX_PATH];

	bool	VideoBuilt;
	u32		NumPortalVertices;
	u32		NumDoodads;
	u32		NumFogs;

	WMO::wmoHeader		Header;
	c8*		TextureFileNameBlock;
	SWMOMaterial*		Materials;
	c8*		GroupNamesBlock;
	SWMOGroup*		Groups;
	vector3df*		PortalVertices;
	SWMOPortal*		Portals;
	SWMOLight*			Lights;
	c8*		ModelNamesBlock;
	SWMODoodadSet*		DoodadSets;
	SWMODoodad*		Doodads;
	SWMOFog*		Fogs;
};