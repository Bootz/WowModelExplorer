#pragma once

#include "core.h"
#include <list>

class ISceneNode
{
public:
	ISceneNode(ISceneNode* parent)
		: Parent(parent), Generation(0), Distance(0)
	{
		InitializeListHead(&Link);
		InitializeListHead(&ChildNodeList);

		if (!Parent)
			Generation = 0;
		else
			Generation = Parent->Generation + 1;

		if (Parent)
			Parent->addChild(this);

		NeedUpdate = true;
		Visible = true;
	}

	virtual ~ISceneNode() {}
public:
	const matrix4& getAbsoluteTransformation() const { return AbsoluteTransformation; }
	const matrix4& getRelativeTransformation() const { return RelativeTransformation; }
	void setRelativeTransformation(const matrix4& mat) {	RelativeTransformation = mat; NeedUpdate = true; }
	void update(bool includeChildren = true);
	void updateAABB();
	void addChild(ISceneNode* child);
	void removeChild(ISceneNode* child);
	void removeAllChildren();

	virtual void registerSceneNode(bool frustumcheck = true);
	virtual void tick(u32 timeSinceStart, u32 timeSinceLastFrame, bool visible) {}
	virtual void onPreRender() { }
	virtual void render() = 0;
	virtual aabbox3df getBoundingBox() const  = 0;
	const aabbox3df& getWorldBoundingBox() const { return WorldBoundingBox; }

	virtual bool isNodeEligible() const = 0;

protected:
	virtual void onUpdated() { updateAABB(); }

public:
	LENTRY		Link;
	LENTRY		ChildNodeList;			//child lists
	ISceneNode*			Parent;
	f32  Distance;		//ºÍÉãÏñ»úµÄ¾àÀë

protected:
	matrix4			RelativeTransformation;
	matrix4			AbsoluteTransformation;
	aabbox3df		WorldBoundingBox;

public:
	bool		NeedUpdate;
	bool		Visible;
	u8	Generation;
};

inline void ISceneNode::update( bool includeChildren /*= true*/ )
{
	if ( NeedUpdate )
	{
		if ( Parent )
		{
			AbsoluteTransformation = getRelativeTransformation() * Parent->AbsoluteTransformation;
		}
		else
			AbsoluteTransformation = getRelativeTransformation();

		onUpdated();

		if ( includeChildren )
		{
			for (PLENTRY e = ChildNodeList.Flink; e != &ChildNodeList;  e = e->Flink)
			{
				ISceneNode* node = reinterpret_cast<ISceneNode*>CONTAINING_RECORD(e, ISceneNode, Link);
				node->NeedUpdate = true;
				node->update(includeChildren);
			}
		}
		NeedUpdate = false;
	}
}

inline void ISceneNode::updateAABB()
{
	WorldBoundingBox = getBoundingBox();
	if(!WorldBoundingBox.isZero())
		AbsoluteTransformation.transformBox(WorldBoundingBox);
}

inline void ISceneNode::addChild( ISceneNode* child )
{
	_ASSERT(child && child!=this);

	if (child->Parent && child->Parent != this)
		child->Parent->removeChild(this);

	InsertTailList(&ChildNodeList, &child->Link);
	child->Parent = this;

	child->Generation = Generation + 1;
}

inline void ISceneNode::removeChild( ISceneNode* child )
{
	_ASSERT(child && child!=this);

	for (PLENTRY e = ChildNodeList.Flink; e != &ChildNodeList; )
	{
		ISceneNode* node = reinterpret_cast<ISceneNode*>CONTAINING_RECORD(e, ISceneNode, Link);
		e = e->Flink;
		if(node == child)
		{
			RemoveEntryList(&child->Link);
			child->Parent = NULL;
			child->removeAllChildren();
			delete child;

			break;
		}
	}
}

inline void ISceneNode::removeAllChildren()
{
	for (PLENTRY e = ChildNodeList.Flink; e != &ChildNodeList; )
	{
		ISceneNode* node = reinterpret_cast<ISceneNode*>CONTAINING_RECORD(e, ISceneNode, Link);
		e = e->Flink;

		node->removeAllChildren();
		node->Parent = NULL;
		delete node;
	}
	InitializeListHead(&ChildNodeList);
}

inline void ISceneNode::registerSceneNode(bool frustumcheck)
{
	for (PLENTRY e = ChildNodeList.Flink; e != &ChildNodeList;  e = e->Flink)
	{
		ISceneNode* node = reinterpret_cast<ISceneNode*>CONTAINING_RECORD(e, ISceneNode, Link);

		node->registerSceneNode(frustumcheck);
	}
}
