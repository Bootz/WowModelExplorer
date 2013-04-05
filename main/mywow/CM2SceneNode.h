#pragma once

#include "IM2SceneNode.h"
#include "SMaterial.h"
#include "IParticleSystemSceneNode.h"
#include "IRibbonSceneNode.h"
#include <vector>

class ISceneManager;
struct SAttachmentEntry;

class CM2SceneNode : public IM2SceneNode
{
public:
	CM2SceneNode(IFileM2* mesh, ISceneNode* parent, bool npc);
	virtual ~CM2SceneNode();

public:
	//IM2SceneNode
	virtual IFileM2* getFileM2() const { return Mesh; }
	virtual wow_m2instance* getM2Instance() const { return M2Instance; }
	virtual wow_m2appearance* getM2Appearance() const { return M2Appearance; }
	virtual wow_m2FSM* getM2FSM() const { return M2FSM; }

	virtual bool isNpc() const { return IsNpc; }
	virtual void updateCharacter();
	virtual void buildVisibleGeosets();
	virtual bool updateNpc(s32 npcid);	
	virtual aabbox3df getAnimatedWorldAABB() const { return AnimatedWorldAABB; }
	virtual f32 getWorldRadius() const { return WorldRadius; }
	virtual bool playAnimationByIndex(u32 anim, bool loop, s32 timeblend = 200);
	virtual bool playAnimationByName(const c8* name, u32 subIdx, bool loop,  s32 timeblend = 200);
	virtual s32 getCurrentAnimationIndex() const { return CurrentAnim; }
	virtual void setParticleSpeed(f32 speed);
	virtual f32 getParticleSpeed() const { return ParticleSpeed; }

	virtual bool setModelCamera(s32 index);
	virtual s32 getModelCamera() const { return CurrentCamera; }
	virtual void setM2ModelEquipment(s32 slot, s32 itemid);

	virtual IParticleSystemSceneNode* addParticleSystemSceneNode(ParticleSystem* ps);
	virtual IRibbonSceneNode* addRibbonEmitterSceneNode(RibbonEmitter* re);

	virtual void setModelAlpha(bool enable, f32 val);
	virtual void setModelColor(bool enable, SColor color);
	virtual void enableFog(bool enable) { EnableFog = enable; }

	//ISceneNode
	virtual void registerSceneNode(bool frustumcheck = true);
	virtual aabbox3df getBoundingBox() const;
	virtual void tick(u32 timeSinceStart, u32 timeSinceLastFrame, bool visible);
	virtual void render();
	virtual bool isNodeEligible() const;
	virtual void onUpdated();

protected:
	void updateAttachmentEntry(SAttachmentEntry* entry);

	void getBillboardBoneMat(matrix4& mat);				//给billboard的骨骼的旋转矩阵 

	void renderGeoset(u32 index);

	void removeM2ModelEquipment( s32 slot );
	void removeAllM2ModelEquipments();
	void updateCloseHands();

	bool checkFrameLimit(u32& timeSinceLastFrame, s32 limit);

	void tickInvisible(u32 timeSinceStart, u32 timeSinceLastFrame);
	void tickVisible(u32 timeSinceStart, u32 timeSinceLastFrame);

protected:
	u32		FrameInterval;

	IFileM2* Mesh;
	wow_m2instance*		M2Instance;
	wow_m2appearance*		M2Appearance;
	wow_m2FSM*	M2FSM;

	aabbox3df AnimatedWorldAABB;

	f32		ParticleSpeed;
	f32		WorldRadius;
	s32		CurrentAnim;

	s32		TimeBlend;
	s32		AnimTimeBlend;

	s32		CurrentCamera;
	matrix4		CurrentView;
	matrix4		CurrentProjection;

	LENTRY		AttachmentList;

	bool	IsNpc;
	bool AnimateColors;
	bool Death;
	bool ModelAlpha;
	bool EnableFog;

	typedef std::vector<IParticleSystemSceneNode*>	T_ParticleSystemNodes;
	T_ParticleSystemNodes		ParticleSystemNodes;

	typedef std::vector<IRibbonSceneNode*>	T_RibbonEmitterNodes;
	T_RibbonEmitterNodes		RibbonEmitterNodes;

	//friend
	friend class wow_m2appearance;

};