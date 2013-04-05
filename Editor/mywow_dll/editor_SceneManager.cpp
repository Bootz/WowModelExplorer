#include "stdafx.h"
#include "editor_SceneManager.h"
#include "CEditSceneManager.h"

void  SceneManager_drawAll()
{
	g_Engine->getSceneManager()->drawAll();
}

void  SceneManager_setBackgroundColor( SColor color )
{
	g_Engine->getSceneManager()->BackgroundColor = color;
}

void  SceneManager_getBackgroundColor( SColor* color )
{
	*color = g_Engine->getSceneManager()->BackgroundColor;
}

void  SceneManager_showDebug( editor::E_SCENE_DEBUG_PART part, bool show )
{
	CEditSceneManager* mgr = (CEditSceneManager*)g_Engine->getSceneManager();
	switch(part)
	{
	case editor::ESDP_BASE:
		mgr->ShowDebugBase = show;
		break;
	case editor::ESDP_M2_GEOSETS:
		mgr->ShowDebugM2Geosets = show;
	}
}

void  SceneManager_removeSceneNode( ISceneNode* node )
{
	g_Engine->getSceneManager()->removeSceneNode(node);
}

void  SceneManager_removeAllCameras()
{
	g_Engine->getSceneManager()->removeAllCameras();
}

void  SceneManager_removeAllSceneNodes()
{
	g_Engine->getSceneManager()->removeAllSceneNodes();
}

void  SceneManager_setActiveCamera( ICamera* cam )
{
	g_Engine->getSceneManager()->setActiveCamera(cam);
}

ICamera*  SceneManager_getActiveCamera()
{
	return g_Engine->getSceneManager()->getActiveCamera();
}

ICamera*  SceneManager_addCamera( vector3df position, vector3df lookat, vector3df up, f32 nearValue, f32 farValue, f32 fov )
{
	return g_Engine->getSceneManager()->addCamera(position, lookat, up, nearValue, farValue, fov);
}

ICoordSceneNode* SceneManager_addCoordSceneNode()
{
	return g_Engine->getSceneManager()->addCoordSceneNode();
}

IM2SceneNode*  SceneManager_addM2SceneNode( const c8* meshfilename, ISceneNode* parent, bool npc )
{
	IFileM2* m2 = g_Engine->getResourceLoader()->loadM2(meshfilename);
	if (!m2)
		return NULL;

	return g_Engine->getSceneManager()->addM2SceneNode(m2, parent, npc);
}

IMeshSceneNode*  SceneManager_addMeshSceneNode( const c8* name, ISceneNode* parent )
{
	return g_Engine->getSceneManager()->addMeshSceneNode(name, parent);
}

IWMOSceneNode* SceneManager_addWMOSceneNode( const c8* wmofilename, ISceneNode* parent )
{
	IFileWMO* wmo = g_Engine->getResourceLoader()->loadWMO(wmofilename);
	if (!wmo)
		return NULL;

	return g_Engine->getSceneManager()->addWMOSceneNode(wmo, parent);
}

void  SceneManager_setDebugM2Node( IM2SceneNode* node )
{
	CEditSceneManager* mgr = (CEditSceneManager*)g_Engine->getSceneManager();
	mgr->DebugM2Node = node;
}

void SceneManager_setDebugWMONode( IWMOSceneNode* node )
{
	CEditSceneManager* mgr = (CEditSceneManager*)g_Engine->getSceneManager();
	mgr->DebugWMONode = node;
}


