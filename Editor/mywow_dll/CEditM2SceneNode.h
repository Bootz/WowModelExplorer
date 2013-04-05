#pragma once

#include "CM2SceneNode.h"
#include "editor_structs.h"

class CEditM2SceneNode : public CM2SceneNode
{
public:
	CEditM2SceneNode(IFileM2* mesh, ISceneNode* parent, bool npc);
	virtual ~CEditM2SceneNode();

public:
	virtual void tick(u32 timeSinceStart, u32 timeSinceLastFrame, bool visible);
	virtual void render();

public:
	bool	isPlaying() const { return !Paused; }
	void	pause() { Paused = true; }
	void	resume() { Paused = false; }
	void	stop() { Animation.setCurrentFrame(0); pause(); }
	void	step(f32 frame) { 
		Animation.setCurrentFrame(Animation.getCurrentFrame() + frame); 
		pause(); 
		TickDelta = (u32)(frame * Animation.getAnimationSpeed()); }

public:
	void showShoulder(bool show);
	void showLeftHand(bool show);
	void showRightHand(bool show);
	void showParticles(bool show);
	void showGeoset(u32 index, bool show);
	bool isGeosetShow(u32 index);
	void setOverrideWireframe(editor::E_OVERRIDE_WIREFRAME wireframe);

	bool getChildSceneNodes(editor::SM2ChildSceneNodes* childSceneNodes);
	void getReplaceTextureFileName(editor::E_MODEL_REPLACE_TEXTURE texture, c8* filename, u32 size);
	void getTextureFileName(u32 index, c8* filename, u32 size);
	void getRegionTextureFileName(ECharRegions region, c8* filename, u32 size);

	void getGeosetDebugInfo(c16* msg, u32 size);
	void drawBoundingBox(SColor color);
	void drawBones(SColor color);
	
private:
	void renderGeoset(u32 index);

	void drawBone(u32 idx, SColor color);
	void updateAttachmentSceneNodes();

public:
	bool	ShowBones;
	bool	ShowAttachmentPoints;
	bool	ShowBoundingBox;
	bool	ShowModel;

private:
	editor::E_OVERRIDE_WIREFRAME		OverrideWireframe;

private:
	bool	Paused;
	u32		TickDelta;
	bool*	ShowGeosets;
	bool*	IsGeosetsVisible;
	bool*	BonesDrawn;
	
	IMeshSceneNode**		AttachmentSceneNodes;

	friend class CEditSceneManager;
};