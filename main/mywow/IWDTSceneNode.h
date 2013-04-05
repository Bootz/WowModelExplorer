#pragma once

#include "ISceneNode.h"

struct STile;
class CMapEnvironment;

//地图，动态加载tile，场景
class IWDTSceneNode : public ISceneNode
{
public:
	IWDTSceneNode(ISceneNode* parent) : ISceneNode(parent){ }

	virtual ~IWDTSceneNode() { }

public:
	virtual void setCurrentTile(s32 row, s32 col) = 0;
	virtual vector3df getCenter() const = 0;
	virtual bool getTileByPosition(vector3df pos, s32& row, s32& col) = 0;
	virtual CMapEnvironment* getMapEnvironment() const = 0;
	virtual void setAdtLoadSize(E_ADT_LOAD size) = 0;
};