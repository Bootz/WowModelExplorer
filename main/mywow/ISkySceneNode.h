#pragma once

#include "ISceneNode.h"

//����map�е���գ����գ���Ȼ�������
class ISkySceneNode : public ISceneNode
{
public:
	ISkySceneNode(ISceneNode* parent)
		: ISceneNode(parent){}

	virtual ~ISkySceneNode() {}

public:

};