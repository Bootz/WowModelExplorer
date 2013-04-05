#pragma once

#include "ISceneNode.h"

class IFileADT;

class IMapTileSceneNode : public ISceneNode
{
public:
	IMapTileSceneNode(ISceneNode* parent)
		: ISceneNode(parent){}

	virtual ~IMapTileSceneNode() {}

public:
	virtual IFileADT*	getFileADT() const = 0;
	virtual vector3df getCenter() const = 0;

	virtual void addM2SceneNodes() = 0;
	virtual void addWMOSceneNodes() = 0;

	virtual void startLoadingM2SceneNodes() = 0;
	virtual void startLoadingWMOSceneNodes() = 0;
};