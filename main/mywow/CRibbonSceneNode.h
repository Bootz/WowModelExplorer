#pragma once

#include "IRibbonSceneNode.h"
#include "wow_particle.h"
#include "SMaterial.h"

class ISceneManager;
class IRibbonEmitterServices;

class CRibbonSceneNode : public IRibbonSceneNode
{
public:
	CRibbonSceneNode(RibbonEmitter* re, IM2SceneNode* parent);
	virtual ~CRibbonSceneNode();

public:
	//ISceneNode
	virtual void registerSceneNode(bool frustumcheck = true);
	virtual aabbox3df getBoundingBox() const { return aabbox3df::Zero(); }
	virtual void tick(u32 timeSinceStart, u32 timeSinceLastFrame, bool visible);
	virtual void render();
	virtual void onPreRender();
	virtual bool isNodeEligible() const;

private:
	SMaterial		Material;

	ISceneManager*		SceneManager;
	IRibbonEmitterServices*		RibbonEmitterServices;
	wow_m2instance*		Character;
	RibbonEmitter*	Re;
	ITexture*		Texture;
	LENTRY	LiveSegmentList;
	u32		LiveSegmentCount;

	vector3df		tpos;
	SColorf		tcolor;
	f32	tabove, tbelow;

};