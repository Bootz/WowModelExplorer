#pragma once

#include "base.h"

class wowEnvironment;
class wowDatabase;
class wowM2Logic;
class CTimer;

class Engine
{
private:
	DISALLOW_COPY_AND_ASSIGN(Engine);
public:
	Engine();
	~Engine();

	static HWND createWindow( const char* caption, WNDPROC proc, dimension2du &windowSize, bool fullscreen=false, bool hide=false );

	bool initDriver(HWND hwnd, E_DRIVER_TYPE driverType, u32 adapter, bool fullscreen, bool vsync, u8 antialias, bool multithread);

	void initSceneManager();

public:	
	wowDatabase* getWowDatabase() const { return WowDatabase; }
	wowEnvironment* getWowEnvironment() const { return WowEnvironment; }
	wowM2Logic* getWowM2Logic() const { return WowM2Logic; }
	IFileSystem*	getFileSystem() const { return FileSystem; }
	IVideoDriver*	getDriver() const { return Driver; }
	IHardwareBufferServices*		getHardwareBufferServices() const { return HardwareBufferServices; }
	IDrawServices*		getDrawServices() const { return DrawServices; }
	ISceneRenderServices*		getSceneRenderServices() const { return SceneRenderServices; }
	ISceneEnvironment*	getSceneEnvironment() const { return SceneEnvironment; }
	ISceneManager*		getSceneManager() const { return SceneManager; }
	IFTFont*		getFont() const { return Font; }
	IResourceLoader*		getResourceLoader() const { return ResourceLoader; }
	IGeometryCreator*		getGeometryCreator() const { return GeometryCreator; }
	ITextureWriteServices*		getTextureWriteServices() const { return TextureWriteServices; }
	IManualMeshServices*		getManualMeshServices() const { return ManualMeshServices; }
	IManualTextureServices*		getManualTextureServices() const { return ManualTextureServices; }
	IParticleSystemServices*		getParticleSystemServices() const { return ParticleSystemServices; }
	IRibbonEmitterServices*		getRibbonEmitterServices() const { return RibbonEmitterServices; }
	ITerrainServices*	getTerrainServices() const { return TerrainServices; }
	ICollisionServices* getCollisioniServices() const { return CollisionServices; }
	IInputReader*	getInputReader() const { return InputReader; }
	IAudioPlayer*   getAudioPlayer() const { return AudioPlayer; }
	engineSetting*		getEngineSetting() const { return EngineSetting; } 
	CTimer*		getTimer() const { return Timer; }

	void setSceneManager(ISceneManager* smgr) { SceneManager = smgr; }

	bool	AboveVista() const { return AboveVersion6; }

private:
	bool		AboveVersion6;
	wowDatabase*		WowDatabase;
	wowEnvironment*		WowEnvironment;
	wowM2Logic*		WowM2Logic;
	IFileSystem*		FileSystem;
	IInputReader*		InputReader;
	IVideoDriver*		Driver;
	IHardwareBufferServices*		HardwareBufferServices;
	IDrawServices*		DrawServices;
	IFTFont*		Font;
	IResourceLoader*		ResourceLoader;
	ISceneRenderServices*		SceneRenderServices;
	ISceneEnvironment*		SceneEnvironment;
	ISceneManager*			SceneManager;
	IGeometryCreator*		GeometryCreator;
	ITextureWriteServices*		TextureWriteServices;
	IManualMeshServices*		ManualMeshServices;
	IManualTextureServices*		ManualTextureServices;
	IParticleSystemServices*		ParticleSystemServices;
	IRibbonEmitterServices*		RibbonEmitterServices;
	ITerrainServices*		TerrainServices;
	ICollisionServices*		CollisionServices;
	IAudioPlayer*		AudioPlayer;
	engineSetting*		EngineSetting;
	CTimer*			Timer;
};

extern Engine* g_Engine;
extern u32 g_MainThreadId;