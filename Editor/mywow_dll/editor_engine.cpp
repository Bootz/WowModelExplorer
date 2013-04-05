#include "stdafx.h"
#include "editor_engine.h"
#include "CEditSceneManager.h"
#include "CMiniDump.h"

_CrtMemState oldState;
_CrtMemState newState;
_CrtMemState diffState;

void  Engine_create()
{
	CMiniDump::begin();

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	_CrtMemCheckpoint(&oldState);

	createEngine();
}

void  Engine_destroy()
{
	destroyEngine();

	_CrtMemCheckpoint(&newState);

	s32 diff = _CrtMemDifference(&diffState, &oldState, &newState);
	_ASSERT(diff == 0);

	CMiniDump::end();
}

bool  Engine_initDriver( HWND hwnd, E_DRIVER_TYPE driverType, u32 adapter, bool fullscreen, bool vsync, u32 antialias, bool multithread )
{
	return g_Engine->initDriver(hwnd, driverType, adapter, fullscreen, vsync, (u8)antialias, multithread);
}

void  Engine_initSceneManager()
{
	CEditSceneManager* mgr = new CEditSceneManager;
	g_Engine->setSceneManager(mgr);
}

HWND  Engine_createWindow()
{
	return Engine::createWindow("", ::DefWindowProcA, dimension2du(40,30), false, true);
}

IVideoDriver*  Engine_getDriver()
{
	return g_Engine->getDriver();
}

ISceneManager*  Engine_getSceneManager()
{
	return g_Engine->getSceneManager();
}

wowDatabase*  Engine_getWowDatabase()
{
	return g_Engine->getWowDatabase();
}

wowEnvironment*  Engine_getWowEnvironment()
{
	return g_Engine->getWowEnvironment();
}

IManualMeshServices*  Engine_getManualMeshServices()
{
	return g_Engine->getManualMeshServices();
}

IAudioPlayer* Engine_getAudioPlayer()
{
	return g_Engine->getAudioPlayer();
}

IResourceLoader* Engine_getResourceLoader()
{
	return g_Engine->getResourceLoader();
}

ISceneEnvironment* Engine_getSceneEnvironment()
{
	return g_Engine->getSceneEnvironment();
}

void Engine_setVideoSetting( engineSetting::SVideoSetting videosetting )
{
	g_Engine->getEngineSetting()->applyVideoSetting(videosetting);
}

void Engine_getVideoSetting( engineSetting::SVideoSetting* videosetting )
{
	g_Engine->getEngineSetting()->retrieveVideoSetting(videosetting);
}

void Engine_setAdvancedSetting( engineSetting::SAdvancedSetting advancedSetting )
{
	g_Engine->getEngineSetting()->applyAdvancedSetting(advancedSetting);
}

void Engine_getAdvancedSetting( engineSetting::SAdvancedSetting* advancedSetting )
{
	g_Engine->getEngineSetting()->retrieveAdvancedSetting(advancedSetting);
}

bool Engine_isAboveVista()
{
	return g_Engine->AboveVista();
}

