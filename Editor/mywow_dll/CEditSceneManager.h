#pragma once

#include "CSceneManager.h"

class CEditM2SceneNode;
class CEditWMOSceneNode;

class CEditSceneManager : public CSceneManager
{
public:
	CEditSceneManager();

public:
	virtual IM2SceneNode* addM2SceneNode(IFileM2* mesh, ISceneNode* parent, bool npc);
	virtual IWMOSceneNode* addWMOSceneNode(IFileWMO* wmo, ISceneNode* parent);
	virtual void removeSceneNode(ISceneNode* node);
	virtual void drawAll();

	IM2SceneNode*	DebugM2Node;
	bool	ShowDebugM2Geosets;
	IWMOSceneNode*	DebugWMONode;

private:
	void drawM2GeosetsDebugInfo(CEditM2SceneNode* node);

private:
	c16	DebugMsg[512];
	
	matrix4		OldView;
	matrix4		OldProjection;
};