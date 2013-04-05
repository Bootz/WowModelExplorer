#pragma once

#include "editor_base.h"
#include "editor_structs.h"

using namespace editor;

MW_API void  M2SceneNode_getFileM2(IM2SceneNode* node, SFileM2* filem2);
MW_API M2Type  M2SceneNode_getType(IM2SceneNode* node);
MW_API bool  M2SceneNode_isNpc(IM2SceneNode* node);
MW_API void  M2SceneNode_buildVisibleGeosets(IM2SceneNode* node);
MW_API void  M2SceneNode_updateCharacter(IM2SceneNode* node);
MW_API bool  M2SceneNode_updateNpc(IM2SceneNode* node, s32 npcid);

//camera
MW_API bool  M2SceneNode_setModelCamera(IM2SceneNode* node, s32 cameraIndex);
MW_API s32  M2SceneNode_getModelCamera(IM2SceneNode* node);

//animations
MW_API bool  M2SceneNode_playAnimationByName(IM2SceneNode* node, const c8* name, u32 subIdx, bool loop, s32 timeblend);
MW_API bool  M2SceneNode_playAnimationByIndex(IM2SceneNode* node, u32 anim, bool loop, s32 timeblend);
MW_API u32  M2SceneNode_getAnimationCount(IM2SceneNode* node);
MW_API bool  M2SceneNode_getAnimation(IM2SceneNode* node, u32 index, SAnimation* anim);


//charfeature
MW_API void  M2SceneNode_setCharFeature(IM2SceneNode* node, SCharFeature feature);
MW_API void  M2SceneNode_getCharFeature(IM2SceneNode* node, SCharFeature* feature);


//item
MW_API bool  M2SceneNode_takeItem(IM2SceneNode* node, s32 itemId, s32* slot);
MW_API void  M2SceneNode_resetSlot(IM2SceneNode* node, s32 slot);
MW_API int  M2SceneNode_getSlotItemId(IM2SceneNode* node, s32 slot);
MW_API bool  M2SceneNode_slotHasModel(IM2SceneNode* node, s32 slot);
MW_API void  M2SceneNode_loadStartOutfit(IM2SceneNode* node, s32 startId, bool deathknight);
MW_API void  M2SceneNode_loadSet(IM2SceneNode* node, s32 setid);


//animation player
MW_API void  M2SceneNode_pause(IM2SceneNode* node);
MW_API void  M2SceneNode_resume(IM2SceneNode* node);
MW_API void  M2SceneNode_stop(IM2SceneNode* node);
MW_API void  M2SceneNode_step(IM2SceneNode* node, f32 frame);
MW_API bool  M2SceneNode_isPlaying(IM2SceneNode* node);
MW_API s32  M2SceneNode_getCurrentAnimationIndex(IM2SceneNode* node);
MW_API f32  M2SceneNode_getCurrentFrame(IM2SceneNode* node);
MW_API void  M2SceneNode_setCurrentFrame(IM2SceneNode* node, f32 frame);
MW_API void  M2SceneNode_setLoop(IM2SceneNode* node, bool loop);
MW_API bool  M2SceneNode_isLoop(IM2SceneNode* node);

//show/hide
MW_API void  M2SceneNode_showModelPart(IM2SceneNode* node, E_MODEL_PART modelpart, bool show);
MW_API void  M2SceneNode_showEditPart(IM2SceneNode* node, E_MODEL_EDIT_PART editpart, bool show);
MW_API void  M2SceneNode_setWireframe(IM2SceneNode* node, editor::E_OVERRIDE_WIREFRAME wireframe);

//child scene nodes
MW_API bool M2SceneNode_getChildSceneNodes(IM2SceneNode* node, editor::SM2ChildSceneNodes* childSceneNodes);

//file property
MW_API void M2SceneNode_getReplaceTextureFileName(IM2SceneNode* node, editor::E_MODEL_REPLACE_TEXTURE texture, c8* filename, u32 size);
MW_API void M2SceneNode_getTextureFileName(IM2SceneNode* node, u32 index, c8* filename, u32 size);
MW_API void M2SceneNode_getRegionTextureFileName(IM2SceneNode* node, ECharRegions region, c8* filename, u32 size);
MW_API bool  M2SceneNode_getRenderFlag(IM2SceneNode* node, SRenderFlag* renderflag, u32 index);
MW_API bool  M2SceneNode_getGeoset(IM2SceneNode* node, u32 index, editor::SGeoset* geoset);
MW_API void  M2SceneNode_showGeoset(IM2SceneNode* node, u32 index, bool show);
MW_API bool M2SceneNode_isGeosetShow(IM2SceneNode* node, u32 index);

//
MW_API void M2SceneNode_setModelAlpha(IM2SceneNode* node, f32 val);
MW_API f32 M2SceneNode_getModelAlpha(IM2SceneNode* node);
MW_API void M2SceneNode_setModelColor(IM2SceneNode* node, SColor color);
MW_API void M2SceneNode_getModelColor(IM2SceneNode* node, SColor* color);

//logic
MW_API void M2SceneNode_resetState(IM2SceneNode* node);
MW_API bool M2SceneNode_isStateValid(IM2SceneNode* node, E_M2_STATES state);
MW_API bool M2SceneNode_changeState(IM2SceneNode* node, E_M2_STATES state);
