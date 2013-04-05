#include "stdafx.h"
#include "CEditWMOSceneNode.h"
#include "CFileWMO.h"

CEditWMOSceneNode::CEditWMOSceneNode( IFileWMO* wmo, ISceneNode* parent )
	: CWMOSceneNode(wmo, parent), ShowGroups(NULL)
{
	ShowBoundingBox = false;
	ShowWMO = true;

	OverrideWireframe = editor::EOW_NONE;

	ShowGroups = new bool[Wmo->Header.nGroups];
	for (u32 i=0; i<Wmo->Header.nGroups; ++i)
		ShowGroups[i] = true;
}

CEditWMOSceneNode::~CEditWMOSceneNode()
{
	delete[] ShowGroups;
}

void CEditWMOSceneNode::render()
{
	//wmo
	if (ShowWMO)
	{
		for (u32 i=0; i<Wmo->Header.nGroups; ++i)
		{
			const SWMOGroup* group = &Wmo->Groups[i];
			if (!DynGroups[i].visible || !ShowGroups[i])
				continue;

			for (u32 c=0; c<group->NumBatches; ++c)
			{
				renderWMOGroup(i, c);
			}
		}
	}
	
	//doodads

	//liquid
}

void CEditWMOSceneNode::renderWMOGroup( u32 groupIndex, u32 batchIndex )
{
	SWMOGroup* group = &Wmo->Groups[groupIndex];
	SDynGroup* dynGroup = &DynGroups[groupIndex];
	const SWMOBatch* batch = &group->Batches[batchIndex];
	u8 matId = batch->matId;
	_ASSERT(matId < Wmo->Header.nMaterials);

	const SWMOMaterial* material = &Wmo->Materials[matId]; 

	SRenderUnit unit = {0};

	setMaterial(material, unit.material);

	unit.distance = dynGroup->distancesq;
	unit.bufferParam.vbuffer0 = group->VertexBuffer;
	unit.bufferParam.ibuffer = group->IndexBuffer;
	unit.bufferParam.vType = EVT_PNCT2;
	unit.primType = EPT_TRIANGLES;
	unit.primCount = batch->indexCount / 3;
	unit.drawParam.startIndex = batch->indexStart;
	unit.drawParam.minVertIndex = batch->vertexStart;
	unit.drawParam.numVertices = batch->vertexEnd - batch->vertexStart;
	unit.sceneNode = this;
	unit.matWorld = &AbsoluteTransformation;
	unit.textures[0] = material->texture0;
	unit.textures[1] = material->texture1;

	g_Engine->getSceneRenderServices()->addRenderUnit(&unit, ERT_WMO);
}

void CEditWMOSceneNode::setMaterial( const SWMOMaterial* material, SMaterial& mat )
{
	mat.VertexShader = g_Engine->getDriver()->getShaderServices()->getVertexShader(EVST_MAPOBJDIFFUSE_T1);
	mat.PsType = EPST_MAPOBJOPAQUE;

	mat.AmbientColor.set(0.6f, 0.6f, 0.6f);

	mat.FogEnable = EnableFog;
	mat.Lighting = true;

	mat.MaterialType = material->alphatest ? EMT_ALPHA_TEST : EMT_SOLID;

	mat.TextureLayer[0].TextureWrapU = mat.TextureLayer[0].TextureWrapV = ETC_REPEAT;
	mat.TextureLayer[1].TextureWrapU = mat.TextureLayer[1].TextureWrapV = ETC_REPEAT;

	//wireframe
	switch(OverrideWireframe)
	{
	case editor::EOW_NONE:
		mat.Wireframe = false;
		break;
	case editor::EOW_WIREFRAME:
		mat.Wireframe = true;
		break;
	case editor::EOW_WIREFRAME_SOLID:
		mat.Wireframe = true;
		mat.MaterialType = EMT_SOLID;
		break;
	case editor::EOW_WIREFRAME_ONECOLOR:
		mat.Wireframe = true;
		mat.MaterialType = EMT_LINE;
		break;
	}
}

void CEditWMOSceneNode::setOverrideWireframe( editor::E_OVERRIDE_WIREFRAME wireframe )
{
	OverrideWireframe = wireframe;
}

void CEditWMOSceneNode::showGroup( u32 index, bool show )
{
	if (index >= Wmo->Header.nGroups)
		return;

	ShowGroups[index] = show;
}

bool CEditWMOSceneNode::isGroupShow( u32 index )
{
	if (index >= Wmo->Header.nGroups)
		return false;

	return ShowGroups[index];
}

void CEditWMOSceneNode::drawBoundingBox( SColor color )
{
	for (u32 i=0; i<Wmo->Header.nGroups; ++i)
	{
		const SWMOGroup* group = &Wmo->Groups[i];
		if (!DynGroups[i].visible || !ShowGroups[i])
			continue;
	
		g_Engine->getDrawServices()->add3DBox(DynGroups[i].worldbox, color);
	}
}