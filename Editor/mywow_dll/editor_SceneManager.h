#pragma once

#include "editor_base.h"
#include "editor_structs.h"

class ICamera;
class ISceneNode;
class ICoordSceneNode;
class IM2SceneNode;

//
MW_API void  SceneManager_drawAll();
MW_API void  SceneManager_setBackgroundColor(SColor color);
MW_API void  SceneManager_getBackgroundColor(SColor* color);
MW_API void  SceneManager_showDebug(editor::E_SCENE_DEBUG_PART part, bool show);

MW_API void  SceneManager_removeSceneNode(ISceneNode* node);
MW_API void  SceneManager_removeAllCameras();
MW_API void  SceneManager_removeAllSceneNodes();
MW_API void  SceneManager_setDebugM2Node(IM2SceneNode* node);
MW_API void SceneManager_setDebugWMONode( IWMOSceneNode* node );

MW_API void  SceneManager_setActiveCamera(ICamera* cam);
MW_API ICamera*  SceneManager_getActiveCamera();
MW_API ICamera*  SceneManager_addCamera( vector3df position, vector3df lookat, vector3df up, f32 nearValue, f32 farValue, f32 fov );

MW_API ICoordSceneNode* SceneManager_addCoordSceneNode();
MW_API IM2SceneNode*  SceneManager_addM2SceneNode(const c8* meshfilename, ISceneNode* parent, bool npc);
MW_API IMeshSceneNode*  SceneManager_addMeshSceneNode(const c8* name, ISceneNode* parent);
MW_API IWMOSceneNode* SceneManager_addWMOSceneNode(const c8* wmofilename, ISceneNode* parent);