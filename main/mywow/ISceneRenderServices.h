#pragma once

#include "core.h"

class ISceneNode;
class ICamera;
class ISceneRenderer;
struct SRenderUnit;

//先按场景结点排序分类，再按material类型分类
class ISceneRenderServices
{
public:
	ISceneRenderServices() : SCENE_SCALE(3.0f) { }
	virtual ~ISceneRenderServices() 	{}

	//整个场景缩放比例： 地形，建筑，物体，天空
	const f32 SCENE_SCALE;

public:
	virtual void addSceneNode(ISceneNode* node, bool visible) = 0;
	virtual void clearAllSceneNodes() = 0;
	virtual void tickAllSceneNodes(u32 timeSinceStart, u32 timeSinceLastFrame) = 0;
	virtual void renderAllSceneNodes() = 0;

	virtual void addRenderUnit(const SRenderUnit* unit, E_RENDERINST_TYPE type) = 0;
	virtual void renderAll(E_RENDERINST_TYPE type, ICamera* cam) = 0;

	virtual void begin_setupLightFog(E_RENDERINST_TYPE type, ICamera* cam) = 0;
	virtual void end_setupLightFog(E_RENDERINST_TYPE type) = 0;

	virtual SRenderUnit* getCurrentUnit() const = 0; 

	//scene related

	virtual void setModelLodBias(s32 lodbias) = 0;
	virtual s32 getModelLodBias() const = 0;

	virtual void setTerrainLodBias(s32 lodbias) = 0;
	virtual s32 getTerrainLodBias() const = 0;

	virtual void setObjectVisibleDistance(f32 distance) = 0;
	virtual f32 getObjectVisibleDistance() const = 0;
	virtual f32 getObjectAlphaDistance() const = 0;

	virtual void setM2InvisibleTickDistance(f32 distance) = 0;
	virtual f32 getM2InvisibleTickDistance() const = 0;
	virtual f32 getM2SlowTickBegin() const = 0;

	virtual f32 getClipDistance() const = 0;
	virtual void setClipDistance(f32 distance) = 0;

	virtual E_ADT_LOAD getAdtLoadSize() const = 0;
	virtual void setAdtLoadSize(E_ADT_LOAD adt) = 0;

	virtual void registerAdtLoadSizeChanged(IAdtLoadSizeChangedCallback* callback) = 0;
	virtual void removeAdtLoadSizeChanged(IAdtLoadSizeChangedCallback* callback) = 0;

	virtual	ISceneRenderer* getSceneRenderer(E_RENDERINST_TYPE type) = 0;
};
