#include "stdafx.h"
#include "editor_WMOSceneNode.h"
#include "CEditWMOSceneNode.h"

void WMOSceneNode_showEditPart( IWMOSceneNode* node, editor::E_WMO_EDIT_PART editpart, bool show )
{
	CEditWMOSceneNode* editNode = (CEditWMOSceneNode*)node;
	switch (editpart)
	{
	case EWP_BOUNDINGBOX:
		editNode->ShowBoundingBox = show;
		break;
	case EWP_WMO:
		editNode->ShowWMO = show;
		break;
	}
}

void WMOSceneNode_setWireframe( IWMOSceneNode* node, editor::E_OVERRIDE_WIREFRAME wireframe )
{
	CEditWMOSceneNode* editNode = (CEditWMOSceneNode*)node;
	editNode->setOverrideWireframe(wireframe);
}

void WMOSceneNode_getFileWMO( IWMOSceneNode* node, SFileWMO* filewmo )
{
	IFileWMO* wmo = node->getFileWMO();

	getFileNameA(wmo->Name, filewmo->name, DEFAULT_SIZE);
	strcpy_s(filewmo->longname, 256, wmo->getFileName());
	filewmo->numMaterials = wmo->Header.nMaterials;
	filewmo->numGroups = wmo->Header.nGroups;
	filewmo->numPortals = wmo->Header.nPortals;
	filewmo->numLights = wmo->Header.nLights;
	filewmo->numModels = wmo->Header.nModels;
	filewmo->numDoodads = wmo->NumDoodads;
	filewmo->numDoodadSets = wmo->Header.nDoodadSets;
	filewmo->wmoID = wmo->Header.wmoID;
}

bool WMOSceneNode_getGroup( IWMOSceneNode* node, u32 index, editor::SWMOGroup* group )
{
	IFileWMO* fileWmo = node->getFileWMO();
	if (index >= fileWmo->Header.nGroups)
		return false;

	strcpy_s(group->name, DEFAULT_SIZE, fileWmo->Groups[index].name);
	group->numBatches = fileWmo->Groups[index].NumBatches;
	group->numDoodads = fileWmo->Groups[index].NumDoodads;
	group->numLights = fileWmo->Groups[index].NumLights;
	group->VCount = fileWmo->Groups[index].VCount;
	group->ICount = fileWmo->Groups[index].ICount;

	return true;
}

void WMOSceneNode_showGroup( IWMOSceneNode* node, u32 index, bool show )
{
	CEditWMOSceneNode* editNode = (CEditWMOSceneNode*)node;
	editNode->showGroup(index, show);
}

bool WMOSceneNode_isGroupShow( IWMOSceneNode* node, u32 index )
{
	CEditWMOSceneNode* editNode = (CEditWMOSceneNode*)node;
	return editNode->isGroupShow(index);
}