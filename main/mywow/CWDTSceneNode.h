#pragma once

#include "IWDTSceneNode.h"
#include "IFileWDT.h"
#include "SMaterial.h"
#include <list>
#include <map>
#include <vector>

class ICamera;
class ISkySceneNode;
class CMapChunk;

class CWDTSceneNode : public IWDTSceneNode
{
public:
	CWDTSceneNode(IFileWDT* wdt, ISceneNode* parent);
	virtual ~CWDTSceneNode();

public:
	virtual void setCurrentTile(s32 row, s32 col);
	virtual vector3df getCenter() const;
	virtual bool getTileByPosition(vector3df pos, s32& row, s32& col);
	virtual CMapEnvironment* getMapEnvironment() const;
	virtual void setAdtLoadSize(E_ADT_LOAD size) { AdtLoadSize = size; }

	//ISceneNode
	virtual void registerSceneNode(bool frustumcheck = true);
	virtual aabbox3df getBoundingBox() const { return aabbox3df::Zero(); }
	virtual void tick(u32 timeSinceStart, u32 timeSinceLastFrame, bool visible);
	virtual void render();
	virtual bool isNodeEligible() const { return true; }
	virtual void onUpdated();

protected:
	struct SDynChunk 
	{
		bool highres;
		bool lowres;
		aabbox3df		terrianWorldBox;
	};

	struct SChunkRenderUnit
	{
		SChunkRenderUnit() : row(0), col(0), chunkCount(0) {}

		u8 row;		//start
		u8 col;
		u8 chunkCount;
	};

	class CMapBlock
	{
	private:
		DISALLOW_COPY_AND_ASSIGN(CMapBlock);

	public:
		CMapBlock() : tile(NULL)
		{
			memset(DynChunks, 0, sizeof(DynChunks));
		}

		STile* tile;

		SDynChunk	DynChunks[16][16];

		typedef std::vector<SChunkRenderUnit> T_ChunkRenderList;
		T_ChunkRenderList HighResChunkRenderList;
		T_ChunkRenderList LowResChunkRenderList;
	};

protected:
	void registerVisibleChunks(CMapBlock* block, ICamera* cam);
	void updateMapBlock(CMapBlock* block);
	
	//void renderMapBlock(CMapBlock* block);

	void renderMapBlock(CMapBlock* block);
	void addChunkRenderList(CMapBlock* block, bool high, u8 row, u8 col);
	void renderChunkRenderList(CMapBlock* block, bool high);

	void startLoadADT(STile* tile);
	bool processADT();
	bool updateBlocksByCamera();
	void unloadOutBlocks();

	bool isLoading(STile* tile);
	void finishLoading(STile* tile);

	void recalculateTilesNeeded(s32 row, s32 col);
	bool isTileNeeded(STile* tile);		//是否在需要加载的范围内

	u32 getNumBlocks() const;

protected:
	SMaterial		Material;
	
	CMapBlock	MapBlocks[25];

	s32	Row, Col;
	vector2di		Coords[25];

	IFileWDT*		FileWDT;
	CMapChunk*			CamChunk;
	CMapChunk*			LastCamChunk;

	ISkySceneNode*		SkySceneNode;	
	E_ADT_LOAD		AdtLoadSize;

//已加载和加载中的tile, false为加载中，true为已加载
	typedef std::map<STile*, bool, std::less<STile*>, qzone_allocator<std::pair<STile*, bool>>>		T_TileMap;
	T_TileMap		TilesMap;
};