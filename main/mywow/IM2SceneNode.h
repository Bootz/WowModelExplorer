#pragma once

#include "ISceneNode.h"
#include "SColor.h"

class IFileM2;
class wow_m2instance;
class wow_m2appearance;
class wow_m2FSM;
class ITexture;
class IParticleSystemSceneNode;
class IRibbonSceneNode;
class ParticleSystem;
class RibbonEmitter;

class IM2SceneNode : public ISceneNode
{
public:
	IM2SceneNode(ISceneNode* parent)
		: ISceneNode(parent), RenderPriority(0), RenderInstType(ERT_MESH) {}

	virtual ~IM2SceneNode() {}

public:
	virtual IFileM2* getFileM2() const = 0;
	virtual wow_m2instance* getM2Instance() const  = 0;
	virtual wow_m2appearance* getM2Appearance() const = 0;
	virtual wow_m2FSM* getM2FSM() const = 0;

	virtual bool isNpc() const = 0;
	virtual void buildVisibleGeosets() = 0;
	virtual void updateCharacter() = 0;
	virtual bool updateNpc(s32 npcid) = 0;

	virtual aabbox3df getAnimatedWorldAABB() const = 0;
	virtual f32 getWorldRadius() const = 0;

	virtual bool playAnimationByIndex(u32 anim, bool loop, s32 timeblend = 200) = 0;
	virtual bool playAnimationByName(const c8* name, u32 subIdx, bool loop, s32 timeblend = 200) = 0;
	virtual s32 getCurrentAnimationIndex() const = 0;	
	virtual void setParticleSpeed(f32 speed) = 0;
	virtual f32 getParticleSpeed() const = 0;

	virtual bool setModelCamera(s32 index) = 0;
	virtual s32 getModelCamera() const = 0;

	virtual void setM2ModelEquipment(s32 slot, s32 itemid) = 0;

	virtual void setModelAlpha(bool enable, f32 val) = 0;
	virtual void setModelColor(bool enable, SColor color) = 0;
	virtual void enableFog(bool enable) = 0;

	virtual IParticleSystemSceneNode* addParticleSystemSceneNode(ParticleSystem* ps) = 0;
	virtual IRibbonSceneNode* addRibbonEmitterSceneNode(RibbonEmitter* re) = 0;

public:
	animation		Animation;
	s8	RenderPriority;
	E_RENDERINST_TYPE		RenderInstType;
};