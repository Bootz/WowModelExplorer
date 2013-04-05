#pragma once

#include "IMapTileSceneNode.h"
#include "IFileWDT.h"
#include "SMaterial.h"
#include <list>

class CMapChunk;
class ICamera;
class IM2SceneNode;
class IWMOSceneNode;

class CMapTileSceneNode : public IMapTileSceneNode
{
public:
	CMapTileSceneNode(IFileWDT* wdt, STile* tile, ISceneNode* parent);
	virtual ~CMapTileSceneNode();

public:
	//IMapTileSceneNode
	virtual IFileADT*	getFileADT() const { return Tile->fileAdt; }
	virtual vector3df  getCenter() const;
	virtual void addM2SceneNodes();
	virtual void addWMOSceneNodes();

	virtual void startLoadingM2SceneNodes();
	virtual void startLoadingWMOSceneNodes();

	//ISceneNode
	virtual void registerSceneNode(bool frustumcheck = true);
	virtual aabbox3df getBoundingBox() const;
	virtual void tick(u32 timeSinceStart, u32 timeSinceLastFrame, bool visible);
	virtual void render();
	virtual bool isNodeEligible() const;
	virtual void onUpdated();

protected:
	struct SDynChunk 
	{
		bool highres;
		bool lowres;
		aabbox3df		terrianWorldBox;
	};

	struct SDynM2Inst
	{
		IM2SceneNode*	node;
		aabbox3df box;
		f32 radius;
	};

	struct SDynWmoInst
	{
		IWMOSceneNode* node;
	};

protected:
	void registerVisibleChunks(ICamera* cam);
	void registerVisibleM2Instances(ICamera* cam);
	void registerVisibleWmoInstances(ICamera* cam);

	void classifyM2Instance(u32 index, const matrix4& instMat, bool passive);

	void processResources();

protected:
	SMaterial		Material;

	SDynChunk	DynChunks[16][16];

	IFileWDT*		WDT;
	STile*		Tile;
	
	SDynM2Inst*		M2InstSceneNodes;
	bool*		M2InstVisible;

	SDynWmoInst*		WmoInstSceneNodes;
	bool*		WmoInstVisible;

	CMapChunk*			LastCamChunk;

protected:
	typedef std::list<u32, qzone_allocator<u32>> T_InstanceList;

	struct SChunkM2List
	{
		T_InstanceList		m2InstList;
	};

	//小物体
	SChunkM2List		LittleChunkM2List[16][16];
	//大物体
	SChunkM2List		BigChunkM2List;
};