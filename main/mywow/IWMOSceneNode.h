#pragma once

#include "ISceneNode.h"

class IFileWMO;

class IWMOSceneNode : public ISceneNode
{
public:
	IWMOSceneNode(ISceneNode* parent)
		: ISceneNode(parent){}

	virtual ~IWMOSceneNode() {}

public:
	virtual IFileWMO*  getFileWMO() const = 0;

	virtual void enableFog(bool enable) = 0;
};