#pragma once

#include "CWMOSceneNode.h"
#include "editor_structs.h"

class CEditWMOSceneNode : public CWMOSceneNode
{
public:
	CEditWMOSceneNode(IFileWMO* wmo, ISceneNode* parent);
	virtual ~CEditWMOSceneNode();

public:
	virtual void render();

public:
	void setOverrideWireframe(editor::E_OVERRIDE_WIREFRAME wireframe);
	void showGroup(u32 index, bool show);
	bool isGroupShow(u32 index);

	void drawBoundingBox(SColor color);

public:
	bool	ShowBoundingBox;
	bool	ShowWMO;

private:
	void renderWMOGroup(u32 groupIndex, u32 batchIndex);

	void setMaterial(const SWMOMaterial* material, SMaterial& mat);

private:
	editor::E_OVERRIDE_WIREFRAME		OverrideWireframe;
	bool*	ShowGroups;
};