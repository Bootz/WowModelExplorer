#pragma once

#include "ISceneRenderServices.h"
#include "ISceneNode.h"
#include <list>
#include <vector>

class CSceneRenderServices : public ISceneRenderServices
{
private:
	DISALLOW_COPY_AND_ASSIGN(CSceneRenderServices);

public:
	CSceneRenderServices();
	~CSceneRenderServices();

public:
	virtual void addSceneNode(ISceneNode* node, bool visible);

	virtual void clearAllSceneNodes();
	virtual void tickAllSceneNodes(u32 timeSinceStart, u32 timeSinceLastFrame);
	virtual void renderAllSceneNodes();

	virtual void addRenderUnit(const SRenderUnit* unit, E_RENDERINST_TYPE type);
	virtual void renderAll(E_RENDERINST_TYPE type, ICamera* cam);

	virtual void begin_setupLightFog(E_RENDERINST_TYPE type, ICamera* cam);
	virtual void end_setupLightFog(E_RENDERINST_TYPE type);

	virtual SRenderUnit* getCurrentUnit() const { return CurrentUnit; }

	//scene
	virtual void setModelLodBias(s32 lodbias) { ModelLodBias = lodbias; }
	virtual s32 getModelLodBias() const { return ModelLodBias; }

	virtual void setTerrainLodBias(s32 lodbias) { TerrainLodBias = lodbias; }
	virtual s32 getTerrainLodBias() const { return TerrainLodBias; }

	//地形上小物体由可见 -> alpha ->不可见
	virtual void setObjectVisibleDistance(f32 distance) { ObjectVisibleDistance = distance; }
	virtual f32 getObjectVisibleDistance() const { return ObjectVisibleDistance; }
	virtual f32 getObjectAlphaDistance() const { return ObjectVisibleDistance * 0.8f; }

	virtual void setM2InvisibleTickDistance(f32 distance) { M2InvisibleTickDistance = distance; }
	virtual f32 getM2InvisibleTickDistance() const { return M2InvisibleTickDistance; }
	virtual f32 getM2SlowTickBegin() const { return M2SlowTickStart; }

	//被雾的clip距离
	virtual f32 getClipDistance() const { return ClipDistance; }
	virtual void setClipDistance(f32 distance) { ClipDistance = distance; }

	virtual E_ADT_LOAD getAdtLoadSize() const { return AdtLoadSize; }
	virtual void setAdtLoadSize(E_ADT_LOAD adt);

	virtual void registerAdtLoadSizeChanged(IAdtLoadSizeChangedCallback* callback);
	virtual void removeAdtLoadSizeChanged(IAdtLoadSizeChangedCallback* callback);

	virtual	ISceneRenderer* getSceneRenderer(E_RENDERINST_TYPE type);

private:
	struct SEntry 
	{
		ISceneNode*		node;
		bool visible;

		bool operator<(const SEntry& c) const
		{
			return node->Generation < c.node->Generation;
		}
	};

private:
	std::vector<SEntry>		SceneNodes;

	//渲染顺序: 天空, 场景地表，wmo, doodads, 角色模型，特效
	ISceneRenderer*		Sky_Renderer;
	ISceneRenderer*		Terrain_Renderer;
	ISceneRenderer*		Wmo_Renderer;
	ISceneRenderer*		Doodad_Solid_Renderer;
	ISceneRenderer*		Mesh_Solid_Renderer;
	ISceneRenderer*		Transparent_Renderer;
	ISceneRenderer*		Wire_Renderer;

	SRenderUnit*			CurrentUnit;

	s32		ModelLodBias;
	s32		TerrainLodBias;
	f32		ObjectVisibleDistance;		//距离/半径比例，超过此值时物体不可见
	f32		M2SlowTickStart;				//
	f32		M2InvisibleTickDistance;		//距离/半径比例, 超过此值时m2最慢tick
	f32		ClipDistance;
	E_ADT_LOAD		AdtLoadSize;

	typedef std::list<IAdtLoadSizeChangedCallback*, qzone_allocator<IAdtLoadSizeChangedCallback*>> T_AdtLoadSizeChangedList;
	T_AdtLoadSizeChangedList	AdtLoadSizeChangedList;
};