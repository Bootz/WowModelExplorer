#include "stdafx.h"
#include "editor_M2SceneNode.h"
#include "CEditM2SceneNode.h"
#include "wow_m2appearance.h"

void  M2SceneNode_getFileM2( IM2SceneNode* node, SFileM2* filem2 )
{
	IFileM2* m2 = node->getFileM2();

	strcpy_s(filem2->name, DEFAULT_SIZE, m2->Name);
	strcpy_s(filem2->longname, 256, m2->getFileName());
	filem2->numVertices = m2->NumVertices;
	filem2->numBoundingVerts = m2->NumBoundingVerts;
	filem2->numBoundingTriangles = m2->NumBoundingTriangles;
	filem2->numTextures = m2->NumTextures;
	filem2->numTexLookup = m2->NumTexLookup;
	filem2->numAttachLookup =  m2->NumAttachLookup;
	filem2->numGlobalSequences = m2->NumGlobalSequences;
	filem2->numColors = m2->NumColors;
	filem2->numTransparencies = m2->NumTransparencies;
	filem2->numTransparencyLookup = m2->NumTranparencyLookukp;
	filem2->numTexAnim = m2->NumTexAnim;
	filem2->numAnimations = m2->NumAnimations;
	filem2->numBones = m2->NumBones;
	filem2->numRenderFlags = m2->NumRenderFlags;
	filem2->numParticleSystems = m2->NumParticleSystems;
	filem2->numRibbonEmitters = m2->NumRibbonEmitters;

	//skin
	if (m2->Skin)
	{
		filem2->numGeosets = m2->Skin->NumGeosets;
		filem2->numTexUnit = m2->Skin->NumTexUnit;
	}
	else
	{
		filem2->numGeosets = 0;
		filem2->numTexUnit = 0;
	}
}

M2Type  M2SceneNode_getType( IM2SceneNode* node )
{
	return node->getM2Instance()->getMesh()->getType();
}

bool  M2SceneNode_isNpc( IM2SceneNode* node )
{
	return node->isNpc();
}

void  M2SceneNode_buildVisibleGeosets( IM2SceneNode* node )
{
	node->buildVisibleGeosets();
}

void  M2SceneNode_updateCharacter(IM2SceneNode* node)
{
	node->updateCharacter();
}

bool  M2SceneNode_updateNpc( IM2SceneNode* node, s32 npcid )
{
	return node->updateNpc(npcid);
}

bool  M2SceneNode_setModelCamera( IM2SceneNode* node, s32 cameraIndex )
{
	return node->setModelCamera(cameraIndex);
}

s32  M2SceneNode_getModelCamera( IM2SceneNode* node )
{
	return node->getModelCamera();
}

bool  M2SceneNode_playAnimationByName( IM2SceneNode* node, const c8* name, u32 subIdx, bool loop, s32 timeblend )
{
	return node->playAnimationByName(name, subIdx, loop, timeblend);
}

bool  M2SceneNode_playAnimationByIndex( IM2SceneNode* node, u32 anim, bool loop, s32 timeblend )
{
	return node->playAnimationByIndex(anim, loop, timeblend);
}

u32  M2SceneNode_getAnimationCount( IM2SceneNode* node )
{
	return node->getFileM2()->NumAnimations;
}

bool  M2SceneNode_getAnimation( IM2SceneNode* node, u32 index, SAnimation* anim )
{
	IFileM2* m2 = node->getFileM2();
	if (index >= m2->NumAnimations)
		return false;

	const c8* name = g_Engine->getWowDatabase()->getAnimationName(m2->Animations[index].animID);
	if (name)
		strcpy_s(anim->name, 64, name);
	else
		strcpy_s(anim->name, 64, "<unknown>");
	anim->subIndex = m2->Animations[index].animSubID;
	anim->length = m2->Animations[index].timeLength;
	anim->next = m2->Animations[index].NextAnimation;
	anim->animIndex = index;
	return true;
}


void  M2SceneNode_setCharFeature( IM2SceneNode* node, SCharFeature feature )
{
	wow_m2instance* instance = node->getM2Instance();
	if (!instance->CharacterInfo)
		return;

	if (instance->CharacterInfo->SkinColor == feature.skinColor &&
		instance->CharacterInfo->FaceType == feature.faceType &&
		instance->CharacterInfo->HairColor == feature.hairColor &&
		instance->CharacterInfo->HairStyle == feature.hairStyle &&
		instance->CharacterInfo->FacialHair == feature.facialHair)
		return;

	instance->CharacterInfo->SkinColor = feature.skinColor;
	instance->CharacterInfo->FaceType = feature.faceType;
	instance->CharacterInfo->HairColor = feature.hairColor;
	instance->CharacterInfo->HairStyle = feature.hairStyle;
	instance->CharacterInfo->FacialHair = feature.facialHair;

	instance->updateCharacter();
}

void  M2SceneNode_getCharFeature( IM2SceneNode* node, SCharFeature* feature )
{
	wow_m2instance* instance = node->getM2Instance();
	if (!instance->CharacterInfo)
		return;

	feature->skinColor = instance->CharacterInfo->SkinColor;
	feature->faceType = instance->CharacterInfo->FaceType;
	feature->hairColor = instance->CharacterInfo->HairColor;
	feature->hairStyle = instance->CharacterInfo->HairStyle;
	feature->facialHair = instance->CharacterInfo->FacialHair;
}


bool  M2SceneNode_takeItem( IM2SceneNode* node, s32 itemId, s32* slot )
{
	wow_m2appearance* appearance = node->getM2Appearance();
	_ASSERT(appearance);
	return appearance->takeItem(itemId, slot);
}

void  M2SceneNode_resetSlot( IM2SceneNode* node, s32 slot )
{
	wow_m2instance* instance = node->getM2Instance();

	instance->updateEquipments(slot, 0);
	if (instance->slotHasModel(slot))
		node->setM2ModelEquipment(slot, 0);
}

int  M2SceneNode_getSlotItemId( IM2SceneNode* node, s32 slot )
{
	wow_m2instance* instance = node->getM2Instance();
	return instance->CharacterInfo->Equipments[slot];
}

bool  M2SceneNode_slotHasModel( IM2SceneNode* node, s32 slot )
{
	wow_m2instance* instance = node->getM2Instance();
	return instance->slotHasModel(slot);
}

void  M2SceneNode_loadStartOutfit( IM2SceneNode* node, s32 startId, bool deathknight )
{
	wow_m2appearance* appearance = node->getM2Appearance();
	_ASSERT(appearance);
	appearance->loadStartOutfit(startId, deathknight);
}

void  M2SceneNode_loadSet(IM2SceneNode* node, s32 setid)
{
	wow_m2appearance* appearance = node->getM2Appearance();
	_ASSERT(appearance);
	appearance->loadSet(setid);
}


void  M2SceneNode_pause(IM2SceneNode* node)
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->pause();
}

void  M2SceneNode_resume(IM2SceneNode* node)
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->resume();
}

void  M2SceneNode_stop(IM2SceneNode* node)
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->stop();
}

void  M2SceneNode_step(IM2SceneNode* node, f32 frame)
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->step(frame);
}

bool  M2SceneNode_isPlaying( IM2SceneNode* node )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	return editNode->isPlaying();
}

f32  M2SceneNode_getCurrentFrame( IM2SceneNode* node )
{
	return node->Animation.getCurrentFrame();
}

void  M2SceneNode_setCurrentFrame( IM2SceneNode* node, f32 frame )
{
	node->Animation.setCurrentFrame(frame);
}

s32  M2SceneNode_getCurrentAnimationIndex( IM2SceneNode* node )
{
	return node->getCurrentAnimationIndex();
}

void  M2SceneNode_setLoop( IM2SceneNode* node, bool loop )
{
	node->Animation.setLoopMode(loop);
}

bool  M2SceneNode_isLoop( IM2SceneNode* node )
{
	return node->Animation.isLoop();
}


void  M2SceneNode_showModelPart( IM2SceneNode* node, E_MODEL_PART modelpart, bool show )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	wow_m2appearance* appearance = node->getM2Appearance();
	_ASSERT(appearance);
	switch (modelpart)
	{
	case EMP_ALL:
		 appearance->showHelm(show);
		 appearance->showCape(show);
		 editNode->showShoulder(show);
		 editNode->showLeftHand(show);
		 editNode->showRightHand(show);
		 editNode->showParticles(show);
		 break;
	case EMP_HEAD:
		 appearance->showHelm(show);
		 break;
	case EMP_CAPE:
		 appearance->showCape(show);
		 break;
	case EMP_SHOULDER:
		editNode->showShoulder(show);
		break;
	case EMP_LEFTHAND:
		editNode->showLeftHand(show);
		break;
	case EMP_RIGHTHAND:
		editNode->showRightHand(show);
		break;
	}
}

void  M2SceneNode_showEditPart( IM2SceneNode* node, E_MODEL_EDIT_PART editpart, bool show )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	switch (editpart)
	{
	case EEP_MODEL:
		editNode->ShowModel = show;
		break;
	case EEP_PARTICLES:
		editNode->showParticles(show);
		break;
	case EEP_RIBBONS:
	
		break;
	case EEP_BOUNDINGBOX:
		editNode->ShowBoundingBox = show;
		break;
	case EEP_BONES:
		editNode->ShowBones = show;
		break;
	case EEP_ATTACHMENTPOINTS:
		editNode->ShowAttachmentPoints = show;
		break;
	}
}

void M2SceneNode_setWireframe( IM2SceneNode* node, editor::E_OVERRIDE_WIREFRAME wireframe )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->setOverrideWireframe(wireframe);
}

bool  M2SceneNode_getRenderFlag( IM2SceneNode* node, SRenderFlag* renderflag, u32 index )
{
	IFileM2* filem2 = node->getFileM2();
	if (index >= filem2->NumRenderFlags)
		return false;

	renderflag->flags = filem2->RenderFlags[index].flags;
	renderflag->blend = filem2->RenderFlags[index].blend;
	renderflag->lighting = filem2->RenderFlags[index].lighting;
	renderflag->zwrite = filem2->RenderFlags[index].zwrite;

	return true;
}

bool  M2SceneNode_getGeoset( IM2SceneNode* node, u32 index, editor::SGeoset* geoset )
{
	CFileSkin* skin = node->getFileM2()->Skin;
	if(index >= skin->NumGeosets)
		return false;

	geoset->VCount = skin->Geosets[index].VCount;
	geoset->ICount = skin->Geosets[index].ICount;
	geoset->GeoID = skin->Geosets[index].GeoID;

	geoset->TexID = skin->Geosets[index].getTexUnit(0)->TexID;
	geoset->rfIndex =  skin->Geosets[index].getTexUnit(0)->rfIndex;
	geoset->ColorIndex = skin->Geosets[index].getTexUnit(0)->ColorIndex;
	geoset->TransIndex =  skin->Geosets[index].getTexUnit(0)->TransIndex;
	geoset->TexAnimIndex =  skin->Geosets[index].getTexUnit(0)->TexAnimIndex;

	return true;
}

void  M2SceneNode_showGeoset( IM2SceneNode* node, u32 index, bool show )
{	
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->showGeoset(index, show);
}

bool M2SceneNode_isGeosetShow( IM2SceneNode* node, u32 index )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	return editNode->isGeosetShow(index);
}

bool M2SceneNode_getChildSceneNodes( IM2SceneNode* node, editor::SM2ChildSceneNodes* childSceneNodes )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	return editNode->getChildSceneNodes(childSceneNodes);
}

void M2SceneNode_getReplaceTextureFileName( IM2SceneNode* node, editor::E_MODEL_REPLACE_TEXTURE texture, c8* filename, u32 size )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->getReplaceTextureFileName(texture, filename, size);
}

void M2SceneNode_getTextureFileName( IM2SceneNode* node, u32 index, c8* filename, u32 size )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->getTextureFileName(index, filename, size);
}

void M2SceneNode_getRegionTextureFileName( IM2SceneNode* node, ECharRegions region, c8* filename, u32 size )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->getRegionTextureFileName(region, filename, size);
}

void M2SceneNode_setModelAlpha( IM2SceneNode* node, f32 val )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->setModelAlpha(val < 1.0f, val);
}

f32 M2SceneNode_getModelAlpha( IM2SceneNode* node )
{
	return node->getM2Instance()->ModelAlpha;
}

void M2SceneNode_setModelColor( IM2SceneNode* node, SColor color )
{
	CEditM2SceneNode* editNode = (CEditM2SceneNode*)node;
	editNode->setModelColor(color != SColor::White(), color);
}

void M2SceneNode_getModelColor( IM2SceneNode* node, SColor* color )
{
	*color = node->getM2Instance()->ModelColor;
}

void M2SceneNode_resetState( IM2SceneNode* node )
{
	return node->getM2FSM()->resetState();
}

bool M2SceneNode_changeState( IM2SceneNode* node, E_M2_STATES state )
{
	return node->getM2FSM()->changeState(state);
}

bool M2SceneNode_isStateValid( IM2SceneNode* node, E_M2_STATES state )
{
	wow_m2State<IM2SceneNode>* st = node->getM2FSM()->getState(state);
	if (st && st->isValid(node))
		return true;

	return false;
}
