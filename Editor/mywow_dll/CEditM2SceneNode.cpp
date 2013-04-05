#include "stdafx.h"
#include "CEditM2SceneNode.h"
#include "CFileM2.h"

CEditM2SceneNode::CEditM2SceneNode( IFileM2* mesh, ISceneNode* parent, bool npc )
	: CM2SceneNode(mesh, parent, npc), ShowGeosets(NULL), IsGeosetsVisible(NULL), AttachmentSceneNodes(NULL)
{
	ShowModel = true;
	ShowBoundingBox = false;
	ShowBones = false;
	ShowAttachmentPoints = false;
	
	Paused = false;
	TickDelta = 0;

	OverrideWireframe = editor::EOW_NONE;

	CFileSkin* skin = M2Instance->CurrentSkin;
	if (skin)
	{
		ShowGeosets = new bool[skin->NumGeosets];
		for (u32 i=0; i<skin->NumGeosets; ++i)
			ShowGeosets[i] = true;

		IsGeosetsVisible = new bool[skin->NumGeosets];
		::memset(IsGeosetsVisible, 0, sizeof(bool)*skin->NumGeosets);
	}

	BonesDrawn = NULL;
	if (Mesh->NumBones > 0)
	{
		BonesDrawn = new bool[Mesh->NumBones];
		::memset(BonesDrawn, 0, sizeof(bool)*Mesh->NumBones);
	}

	if (Mesh->NumAttachments > 0)
	{
		AttachmentSceneNodes = new IMeshSceneNode*[Mesh->NumAttachments];
		for (u32 i=0; i<Mesh->NumAttachments; ++i)
		{
			AttachmentSceneNodes[i] = g_Engine->getSceneManager()->addMeshSceneNode("$sphere8X4", this);
			AttachmentSceneNodes[i]->setRenderInstType(ERT_WIRE);
			AttachmentSceneNodes[i]->Visible = false;
			SMaterial& mat = AttachmentSceneNodes[i]->getMaterial();
			mat.MaterialType = EMT_LINE;
			mat.Wireframe = true;
			mat.ZWriteEnable = false;
			mat.ZBuffer = ECFN_ALWAYS;
			mat.Lighting = false;
		}
	}
}


CEditM2SceneNode::~CEditM2SceneNode()
{
	delete[] AttachmentSceneNodes;
	delete[] BonesDrawn;
	delete[] IsGeosetsVisible;
	delete[] ShowGeosets;
}

void CEditM2SceneNode::tick( u32 timeSinceStart, u32 timeSinceLastFrame, bool visible )
{
	if (Paused)
	{
		if (TickDelta)
		{
			CM2SceneNode::tick(timeSinceStart, TickDelta, visible);
			TickDelta = 0;
		}
		return;
	}

	for (T_ParticleSystemNodes::iterator i=ParticleSystemNodes.begin(); i != ParticleSystemNodes.end(); ++i)
	{
		(*i)->setEmitting(true);
	}

	//default
	CM2SceneNode::tick(timeSinceStart, timeSinceLastFrame, visible);

	//
	updateAttachmentSceneNodes();
}

void CEditM2SceneNode::render()
{
	if (!ShowModel)
		return;

	CFileSkin* skin = M2Instance->CurrentSkin;
	if (skin)
	{
		::memset(IsGeosetsVisible, 0, sizeof(bool)*skin->NumGeosets);

		for (PLENTRY p = M2Instance->VisibleGeosetList.Flink; p != &M2Instance->VisibleGeosetList; p = p->Flink)
		{
			u32 c = reinterpret_cast<SDynGeoset*>CONTAINING_RECORD(p, SDynGeoset, Link) - M2Instance->DynGeosets;

			if (M2Instance->DynGeosets[c].NoAlpha || !ShowGeosets[c])
				continue;

			IsGeosetsVisible[c] = true;

			renderGeoset(c);
		}
	}

}

void CEditM2SceneNode::renderGeoset( u32 index )
{
	CFileSkin* skin = M2Instance->CurrentSkin;

	CGeoset* set = &M2Instance->CurrentSkin->Geosets[index];
	SDynGeoset* dset = &M2Instance->DynGeosets[index];
	for (CGeoset::T_BoneUnits::iterator itr =set->BoneUnits.begin(); itr != set->BoneUnits.end(); ++itr)
	{
		SRenderUnit unit =  {0};

		if(!M2Instance->setGeosetMaterial(index, unit.material))
			continue;
		unit.material.FogEnable = EnableFog;

		if (RenderInstType == ERT_MESH && ModelAlpha)
			unit.priority = RenderPriority + (set->GeoID != 0 ? 1 : 0);	//子模型优先渲染, 身体最后渲染
		unit.distance = Distance;

		unit.bufferParam.vbuffer0 = skin->GVertexBuffer; 
		unit.bufferParam.vbuffer1 = skin->AVertexBuffer;
		unit.bufferParam.vType = EVT_MODEL;
		unit.bufferParam.ibuffer = skin->IndexBuffer;
		unit.primType = EPT_TRIANGLES;
		unit.primCount = itr->PrimCount;

		unit.drawParam.voffset0 = 0; 
		unit.drawParam.voffset1 = itr->BoneVStart - set->VStart;		//现在位置和顶点位置的偏移
		unit.drawParam.minVertIndex = set->VStart;
		unit.drawParam.startIndex = itr->StartIndex;
		unit.drawParam.numVertices = set->VCount;

		unit.sceneNode = this;
		unit.u.useBoneMatrix = dset->Units[itr->Index].Enable;
		unit.u.boneMatrixArray =  dset->Units[itr->Index].BoneMatrixArray;
		unit.matWorld = &AbsoluteTransformation;

		//texture anim
		unit.material.TextureLayer[0].UseTextureMatrix = dset->UseTextureAnim;
		if (dset->UseTextureAnim)
		{
			unit.material.TextureLayer[0].TextureMatrix = &dset->TextureMatrix;	
		}

		//wireframe
		switch(OverrideWireframe)
		{
		case editor::EOW_NONE:
			unit.material.Wireframe = false;
			break;
		case editor::EOW_WIREFRAME:
			unit.material.Wireframe = true;
			break;
		case editor::EOW_WIREFRAME_SOLID:
			unit.material.Wireframe = true;
			unit.material.MaterialType = EMT_SOLID;
			break;
		case editor::EOW_WIREFRAME_ONECOLOR:
			unit.material.Wireframe = true;
			unit.material.MaterialType = EMT_LINE;
			break;
		}

		//camera anim
		if (CurrentCamera != -1)
		{
			unit.matView = &CurrentView;
			unit.matProjection = &CurrentProjection;
		}

		unit.textures[0] = dset->Texture0;

		g_Engine->getSceneRenderServices()->addRenderUnit(&unit, RenderInstType);
	}
}

void CEditM2SceneNode::showShoulder( bool show )
{
	for (PLENTRY e = AttachmentList.Flink; e != &AttachmentList; )
	{
		SAttachmentEntry* entry = reinterpret_cast<SAttachmentEntry*>CONTAINING_RECORD(e, SAttachmentEntry, Link);
		e = e->Flink;

		if (entry->slot == CS_SHOULDER)
		{
			ISceneNode* node = static_cast<ISceneNode*>(entry->node);
			node->Visible = show;
		}
	}
}

void CEditM2SceneNode::showLeftHand( bool show )
{
	for (PLENTRY e = AttachmentList.Flink; e != &AttachmentList; )
	{
		SAttachmentEntry* entry = reinterpret_cast<SAttachmentEntry*>CONTAINING_RECORD(e, SAttachmentEntry, Link);
		e = e->Flink;

		if (entry->slot == CS_HAND_LEFT)
		{
			ISceneNode* node = static_cast<ISceneNode*>(entry->node);
			node->Visible = show;
		}
	}
}

void CEditM2SceneNode::showRightHand( bool show )
{
	for (PLENTRY e = AttachmentList.Flink; e != &AttachmentList; )
	{
		SAttachmentEntry* entry = reinterpret_cast<SAttachmentEntry*>CONTAINING_RECORD(e, SAttachmentEntry, Link);
		e = e->Flink;

		if (entry->slot == CS_HAND_RIGHT)
		{
			ISceneNode* node = static_cast<ISceneNode*>(entry->node);
			node->Visible = show;
		}
	}
}

void CEditM2SceneNode::showParticles( bool show )
{
	M2Instance->ShowParticles = show;

	for (T_ParticleSystemNodes::iterator i=ParticleSystemNodes.begin(); i != ParticleSystemNodes.end(); ++i)
	{
		(*i)->Visible = show;
	}

	for (PLENTRY e = AttachmentList.Flink; e != &AttachmentList; )
	{
		SAttachmentEntry* entry = reinterpret_cast<SAttachmentEntry*>CONTAINING_RECORD(e, SAttachmentEntry, Link);
		e = e->Flink;

		CEditM2SceneNode* node = static_cast<CEditM2SceneNode*>(entry->node);
		node->showParticles(show);
	}
}

void CEditM2SceneNode::showGeoset( u32 index, bool show )
{
	CFileSkin* skin = M2Instance->CurrentSkin;
	if (!skin || index > skin->NumGeosets)
		return;

	ShowGeosets[index] = show;
}

bool CEditM2SceneNode::isGeosetShow( u32 index )
{
	CFileSkin* skin = M2Instance->CurrentSkin;
	if (!skin || index > skin->NumGeosets)
		return false;

	return ShowGeosets[index];
}

void CEditM2SceneNode::getGeosetDebugInfo( c16* msg, u32 size )
{
	wcscpy_s(msg, size, L"Visible Geosets:\n");

	u32 numgeosets = Mesh->Skin->NumGeosets;
	u32 count = 0;
	for (u32 i=0; i<numgeosets; ++i)
	{
		if(IsGeosetsVisible[i])
		{
			++count;

			c16 tmp[8] = {0};
			_itow_s(i, tmp, 8, 10);
			wcscat_s(msg, 512, tmp);
			wcscat_s(msg, 512, L"  ");

			if (count%5 == 0)
				wcscat_s(msg, 512, L"\n");
		}
	}
}

void CEditM2SceneNode::drawBoundingBox(SColor color)
{
// 	if (Mesh->NumBoundingVerts && Mesh->NumBoundingTriangles)
// 	{
// 		g_Engine->getDrawServices()->draw3DVerts(Mesh->Bounds, Mesh->NumBoundingVerts,
// 			Mesh->BoundTris, Mesh->NumBoundingTriangles, color, AbsoluteTransformation);
// 	}

// 	if(!Mesh->BoundingAABBox.isZero())
// 		g_Engine->getDrawServices()->add3DBox(Mesh->BoundingAABBox, color);
	g_Engine->getDrawServices()->add3DBox(getAnimatedWorldAABB(), color);

	for (PLENTRY e = AttachmentList.Flink; e != &AttachmentList; )
	{
		SAttachmentEntry* entry = reinterpret_cast<SAttachmentEntry*>CONTAINING_RECORD(e, SAttachmentEntry, Link);
		e = e->Flink;

		CEditM2SceneNode* node = reinterpret_cast<CEditM2SceneNode*>(entry->node);
		node->drawBoundingBox(color);
	}
}

void CEditM2SceneNode::drawBone( u32 idx, SColor color )
{
	s32 parent = Mesh->Bones[idx].parent;
	if (parent == -1 || BonesDrawn[idx])
		return;

	vector3df v0 = M2Instance->DynBones[idx].transPivot;
	vector3df v1 = M2Instance->DynBones[parent].transPivot;
	AbsoluteTransformation.transformVect(v0);
	AbsoluteTransformation.transformVect(v1);

	g_Engine->getDrawServices()->add3DLine(line3df(v0, v1), color);

	BonesDrawn[idx] = true;

	drawBone(parent, color);
}

void CEditM2SceneNode::drawBones( SColor color )
{
	CFileSkin* skin = M2Instance->CurrentSkin;
	if (skin)
	{
		::memset(BonesDrawn, 0, sizeof(bool)*Mesh->NumBones);

		for (PLENTRY p = M2Instance->VisibleGeosetList.Flink; p != &M2Instance->VisibleGeosetList; p = p->Flink)
		{
			u32 c = reinterpret_cast<SDynGeoset*>CONTAINING_RECORD(p, SDynGeoset, Link) - M2Instance->DynGeosets;

			if (M2Instance->DynGeosets[c].NoAlpha || !ShowGeosets[c])
				continue;

			CGeoset* set = &skin->Geosets[c];
			for (CGeoset::T_BoneUnits::iterator itr=set->BoneUnits.begin(); itr != set->BoneUnits.end(); ++itr)
			{
				for(u8 k=0; k<(*itr).BoneCount; ++k)
				{
					u16 idx = (*itr).local2globalMap[k];
					drawBone(idx, color);
				}
			}
		}
	}
			
	//attachments
	for (PLENTRY e = AttachmentList.Flink; e != &AttachmentList; )
	{
		SAttachmentEntry* entry = reinterpret_cast<SAttachmentEntry*>CONTAINING_RECORD(e, SAttachmentEntry, Link);
		e = e->Flink;

		CEditM2SceneNode* node = reinterpret_cast<CEditM2SceneNode*>(entry->node);
		node->drawBones(color);
	}
}

void CEditM2SceneNode::updateAttachmentSceneNodes()
{
	//attachment scene nodes
	if (!ShowAttachmentPoints)
	{
		for (u32 i=0; i<Mesh->NumAttachments; ++i)
		{
			AttachmentSceneNodes[i]->Visible = false;
		}
	}
	else
	{
		for (u32 i=0; i<Mesh->NumAttachments; ++i)
		{
			AttachmentSceneNodes[i]->Visible = M2Instance->ShowAttachments[i];

			s32 idx = Mesh->Attachments[i].boneIndex;
			if (idx == -1)
				continue;

			vector3df v0 = M2Instance->DynBones[idx].transPivot;
			matrix4 mat;
			mat.setScale(0.05f);
			mat.setTranslation(v0);
			AttachmentSceneNodes[i]->setRelativeTransformation(mat);
		}
	}
}

void CEditM2SceneNode::setOverrideWireframe( editor::E_OVERRIDE_WIREFRAME wireframe )
{
	OverrideWireframe = wireframe;
	for (PLENTRY e = AttachmentList.Flink; e != &AttachmentList; )
	{
		SAttachmentEntry* entry = reinterpret_cast<SAttachmentEntry*>CONTAINING_RECORD(e, SAttachmentEntry, Link);
		e = e->Flink;

		CEditM2SceneNode* node = reinterpret_cast<CEditM2SceneNode*>(entry->node);
		node->OverrideWireframe = wireframe;
	}
}

bool CEditM2SceneNode::getChildSceneNodes( editor::SM2ChildSceneNodes* childSceneNodes )
{
	if (!getM2Instance()->CharacterInfo)
		return false;

	memset(childSceneNodes, 0, sizeof(editor::SM2ChildSceneNodes));

	for (PLENTRY e = AttachmentList.Flink; e != &AttachmentList; )
	{
		SAttachmentEntry* entry = reinterpret_cast<SAttachmentEntry*>CONTAINING_RECORD(e, SAttachmentEntry, Link);
		e = e->Flink;

		IM2SceneNode* node = static_cast<IM2SceneNode*>(entry->node);
		switch(entry->slot)
		{
		case CS_HEAD:
			childSceneNodes->head = node;
			break;
		case CS_HAND_LEFT:
			childSceneNodes->leftHand = node;
			break;
		case CS_HAND_RIGHT:
			childSceneNodes->rightHand = node;
			break;
		case CS_SHOULDER:
			if (entry->id == ATT_LEFT_SHOULDER)
				childSceneNodes->leftShoulder = node;
			else
				childSceneNodes->rightShoulder = node;
			break;
		}
		
	}
	return true;
}

void CEditM2SceneNode::getReplaceTextureFileName( editor::E_MODEL_REPLACE_TEXTURE texture, c8* filename, u32 size )
{
	memset(filename, 0, size);

	ETextureTypes textype = (ETextureTypes)0;

	switch(texture)
	{
	case editor::EMRT_CAPE:
		textype = TEXTURE_CAPE;
		break;
	case editor::EMRT_HAIR:
		textype = TEXTURE_HAIR;
		break;
	case editor::EMRT_FUR:
		textype = TEXTURE_FUR;
		break;
	case editor::EMRT_NPC1:
		textype = TEXTURE_GAMEOBJECT1;
		break;
	case editor::EMRT_NPC2:
		textype = TEXTURE_GAMEOBJECT2;
		break;
	case editor::EMRT_NPC3:
		textype = TEXTURE_GAMEOBJECT3;
		break;
	}

	if (textype)
	{
		ITexture* tex = getM2Instance()->ReplaceTextures[textype];
		if(tex)
		{
			strcpy_s(filename, size, tex->getFileName());
		}
	}
}

void CEditM2SceneNode::getTextureFileName( u32 index, c8* filename, u32 size )
{
	::memset(filename, 0, size);

	IFileM2* filem2 = getM2Instance()->getMesh();
	if (index >= filem2->NumTextures)
		return;

	ITexture* tex = filem2->Textures[index];
	if (tex)
	{
		strcpy_s(filename, size, tex->getFileName());
	}
}

void CEditM2SceneNode::getRegionTextureFileName( ECharRegions region, c8* filename, u32 size )
{
	::memset(filename, 0, size);
	if (getM2Instance()->CharacterInfo)
	{
		if(region <= NUM_REGIONS)
			strcpy_s(filename, size, getM2Instance()->CharacterInfo->BodyTextureFileNames[region]);
	}
}

