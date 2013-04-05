#pragma once

#include "base.h"
#include "ISceneManager.h"
#include "CFPSCounter.h"
#include <list>

class IVideoDriver;
class ISceneRenderServices;
class IDrawServices;
class ITexture;
class CTimer;

class CSceneManager : public ISceneManager
{
private:
	DISALLOW_COPY_AND_ASSIGN(CSceneManager);

public:
	CSceneManager();
	virtual ~CSceneManager();

public:
	virtual void registerNodeForRendering(ISceneNode* node, bool visible);
	virtual void drawAll();
	virtual void removeSceneNode(ISceneNode* node);
	virtual void removeAllSceneNodes();
	virtual void removeAllCameras();

	virtual f32 getFPS() const { return FPSCounter.getFPS(); }

	virtual void setActiveCamera(ICamera* camera) { ActiveCamera = camera; }
	virtual ICamera* getActiveCamera() { return ActiveCamera; }

	virtual ICamera* addCamera(const vector3df& position, const vector3df& lookat, const vector3df& up, f32 nearValue, f32 farValue, f32 fov);

	virtual ICoordSceneNode* addCoordSceneNode();
	virtual IMeshSceneNode*	addMeshSceneNode(const c8* name, ISceneNode* parent);
	virtual IM2SceneNode* addM2SceneNode(IFileM2* mesh, ISceneNode* parent, bool npc = false);
	virtual IWMOSceneNode* addWMOSceneNode(IFileWMO* wmo, ISceneNode* parent);
	virtual IMapTileSceneNode* addMapTileSceneNode(IFileWDT* wdt, STile* tile, ISceneNode* parent);
	virtual IWDTSceneNode* addWDTSceneNode(IFileWDT* wdt, ISceneNode* parent);

public:
	bool		CalcPerf;

protected:
	void drawAreaInfo();

	void drawDebutText();

	void drawSceneInfo();

	void drawDebugTexture();

protected:
	LENTRY		SceneNodeList;			//scene nodes

	typedef std::list<ICamera*, qzone_allocator<ICamera*>> TCameras;
	TCameras		Cameras;

	ICamera*		ActiveCamera;
	IVideoDriver*			Driver;
	ISceneRenderServices*			SceneRenderServices;
	IDrawServices*		DrawServices;

	ITexture*		DebugTexture;
	CTimer*		Timer;

	c8 Text[MAX_TEXT_LENGTH];
	c16 SceneInfo[MAX_TEXT_LENGTH];

	CFPSCounter		FPSCounter;

	//performance
	u32		PerfCalcTime;
	u32		Perf_GPUTime;
	u32		Perf_registerTime, Perf_tickTime, Perf_renderTime;
	u32		Perf_terrainTime, Perf_wmoTime, Perf_doodadTime, Perf_meshTime, Perf_effectTime, Perf_wireTime;
};