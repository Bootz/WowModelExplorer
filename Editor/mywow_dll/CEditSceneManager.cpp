#include "stdafx.h"
#include "CEditSceneManager.h"
#include "CEditM2SceneNode.h"
#include "CEditWMOSceneNode.h"

CEditSceneManager::CEditSceneManager()
	: CSceneManager(), 
	DebugM2Node(NULL), ShowDebugM2Geosets(false),
	DebugWMONode(NULL)
{
	g_Engine->getManualMeshServices()->addSphere("$sphere8X4", 1.0f, 8, 4, SColor(255,255,0) );
}

IM2SceneNode* CEditSceneManager::addM2SceneNode( IFileM2* mesh, ISceneNode* parent, bool npc )
{
	if (!mesh)
		return NULL;

	CEditM2SceneNode* node = new CEditM2SceneNode(mesh, parent, npc);
	mesh->drop();

	mesh->buildVideoResources();

	if (!parent)
		InsertTailList(&SceneNodeList, &node->Link);

	return node;
}

IWMOSceneNode* CEditSceneManager::addWMOSceneNode( IFileWMO* wmo, ISceneNode* parent )
{
	if (!wmo)
		return NULL;

	CEditWMOSceneNode* node = new CEditWMOSceneNode(wmo, parent);
	wmo->drop();

	wmo->buildVideoResources();

	if (!parent)
		InsertTailList(&SceneNodeList, &node->Link);

	return node;
}

void CEditSceneManager::drawM2GeosetsDebugInfo(CEditM2SceneNode* node)
{
	if (!node || !node->Mesh->Skin)
		return;

	vector2di pos = vector2di(5,300);
	node->getGeosetDebugInfo(DebugMsg, 512);
	g_Engine->getFont()->drawW(DebugMsg, SColor(255,255,0), pos);
}

void CEditSceneManager::removeSceneNode( ISceneNode* node )
{
	if (node == DebugM2Node)
		DebugM2Node = NULL;

	if (node == DebugWMONode)
		DebugWMONode = NULL;

	CSceneManager::removeSceneNode(node);
}

void CEditSceneManager::drawAll()
{
	Timer->calculateTime();

	//frame limit
	//	if (!checkFrameLimit())
	//		return;

	u32 timeSinceStart = Timer->getTimeSinceStart();
	u32 timeSinceLastFrame = Timer->getTimeSinceLastFrame();

	CalcPerf = false;
	if (timeSinceStart - PerfCalcTime > 1000)
	{
		CalcPerf = true;
		PerfCalcTime = timeSinceStart;
	}

	SceneRenderServices->clearAllSceneNodes();

	//3d mode	
	Timer->beginPerf(CalcPerf);
	//visible nodes...
	for(PLENTRY e = SceneNodeList.Flink; e != &SceneNodeList; )
	{
		ISceneNode* node = reinterpret_cast<ISceneNode*>CONTAINING_RECORD(e, ISceneNode, Link);
		e = e->Flink;

		_ASSERT(node->Parent == NULL);
		node->registerSceneNode(true);
	}
	Timer->endPerf(CalcPerf, Perf_registerTime);

	Timer->beginPerf(CalcPerf);
	SceneRenderServices->tickAllSceneNodes(timeSinceStart, timeSinceLastFrame);
	Timer->endPerf(CalcPerf, Perf_tickTime);

	g_Engine->getAudioPlayer()->tickFadeOutSounds(timeSinceLastFrame);
	g_Engine->getParticleSystemServices()->adjustParticles();

	//render
	if (!Driver->beginScene())
		return;
	Driver->clear(true, true, false, BackgroundColor);

	if (!ActiveCamera)
	{
		sprintf_s(Text, MAX_TEXT_LENGTH, "no camera");
		Driver->drawDebugInfo(Text);

		Driver->endScene();
		return;
	}

	Timer->beginPerf(CalcPerf);
	SceneRenderServices->renderAllSceneNodes();
	Timer->endPerf(CalcPerf, Perf_renderTime);

	//clip plane for terrain and wmo
	f32 clip = SceneRenderServices->getClipDistance();
	if (ActiveCamera->getClipDistance() != clip)
		ActiveCamera->setClipDistance(clip);

	//terrain
	Timer->beginPerf(CalcPerf);
	SceneRenderServices->begin_setupLightFog(ERT_TERRAIN, ActiveCamera);
	SceneRenderServices->renderAll(ERT_TERRAIN, ActiveCamera);
	SceneRenderServices->end_setupLightFog(ERT_TERRAIN);
	Timer->endPerf(CalcPerf, Perf_terrainTime);

	//wmo
	Timer->beginPerf(CalcPerf);
	SceneRenderServices->begin_setupLightFog(ERT_WMO, ActiveCamera);
	SceneRenderServices->renderAll(ERT_WMO, ActiveCamera);
	SceneRenderServices->end_setupLightFog(ERT_WMO);
	Timer->endPerf(CalcPerf, Perf_wmoTime);

	//doodad
	Timer->beginPerf(CalcPerf);
	SceneRenderServices->begin_setupLightFog(ERT_DOODAD, ActiveCamera);
	SceneRenderServices->renderAll(ERT_DOODAD, ActiveCamera);
	SceneRenderServices->end_setupLightFog(ERT_DOODAD);
	Timer->endPerf(CalcPerf, Perf_doodadTime);

	Timer->beginPerf(CalcPerf);
	SceneRenderServices->begin_setupLightFog(ERT_MESH, ActiveCamera);
	SceneRenderServices->renderAll(ERT_MESH, ActiveCamera);
	SceneRenderServices->end_setupLightFog(ERT_MESH);
	Timer->endPerf(CalcPerf, Perf_meshTime);

	//sky
	SceneRenderServices->renderAll(ERT_SKY, ActiveCamera);

	Timer->beginPerf(CalcPerf);
	SceneRenderServices->begin_setupLightFog(ERT_EFFECT, ActiveCamera);
	SceneRenderServices->renderAll(ERT_EFFECT, ActiveCamera);
	SceneRenderServices->end_setupLightFog(ERT_EFFECT);
	Timer->endPerf(CalcPerf, Perf_effectTime);

	Timer->beginPerf(CalcPerf);
	SceneRenderServices->renderAll(ERT_WIRE, ActiveCamera);
	DrawServices->flushAll3DLines(ActiveCamera);
	DrawServices->flushAll3DVertices(ActiveCamera);
	DrawServices->flushAll2DLines();
	g_Engine->getFont()->flushText();
	Timer->endPerf(CalcPerf, Perf_wireTime);

	//m2 debug
	if (DebugM2Node)
	{
		 CEditM2SceneNode* node = (CEditM2SceneNode*)DebugM2Node;

		bool modelCamera = node->getModelCamera() != -1;
		if (modelCamera)
		{
			OldView = Driver->getTransform(ETS_VIEW);
			OldProjection = Driver->getTransform(ETS_PROJECTION);
			Driver->setTransform(ETS_VIEW, node->CurrentView);
			Driver->setTransform(ETS_PROJECTION, node->CurrentProjection);
		}

		if (node->ShowBoundingBox)
			node->drawBoundingBox(SColor(255,0,0));

		if (node->ShowBones)
			node->drawBones(SColor(0,0,255));

		DrawServices->flushAll3DLines(modelCamera ? NULL : ActiveCamera);

		if (modelCamera)
		{
			Driver->setTransform(ETS_PROJECTION, OldProjection);
			Driver->setTransform(ETS_VIEW, OldView);
		}

		if (ShowDebugM2Geosets)
			drawM2GeosetsDebugInfo(node);
	}

	//wmo debug
	if (DebugWMONode)
	{
		CEditWMOSceneNode* node = (CEditWMOSceneNode*)DebugWMONode;

		if (node->ShowBoundingBox)
			node->drawBoundingBox(SColor(255,0,0));

		DrawServices->flushAll3DLines(ActiveCamera);
	}

	if (ShowDebugBase)
	{
		sprintf_s(Text, MAX_TEXT_LENGTH, 
			"\nregister time: %d\ntick time: %d\nrender time: %d\nterrain: %d\nwmo: %d\ndoodad: %d\nmesh: %d\neffect: %d\nwire: %d\nGPU time: %d\n",
			Perf_registerTime, Perf_tickTime, Perf_renderTime, Perf_terrainTime, Perf_wmoTime, Perf_doodadTime, Perf_meshTime, Perf_effectTime, Perf_wireTime, Perf_GPUTime);

		Driver->drawDebugInfo(Text);
	}

	drawAreaInfo();

	//drawSceneInfo();

	Timer->beginPerf(CalcPerf);
	Driver->endScene();
	Timer->endPerf(CalcPerf, Perf_GPUTime);

	FPSCounter.registerFrame( Timer->getMillisecond() );
}

