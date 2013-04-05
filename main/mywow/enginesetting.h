#pragma once

#include "base.h"

class engineSetting
{
private:
	DISALLOW_COPY_AND_ASSIGN(engineSetting);

public:
	engineSetting();

public:
	//
	struct SVideoSetting 
	{
		SVideoSetting()
		{
			antialias = 0;
			vsync = false;
			fullscreen = false;
			materialResolution = EL_ONE;
			textureFilter = ETF_BILINEAR;
			materialProjection = false;
			viewDistance = envDetail = groundScene = shadowQuality = liquidDetail =
				sunLightEffect = particleDensity = EL_ONE;
			SSAO = EL_ZERO;
		}
		u32 antialias;
		bool vsync;
		bool fullscreen;
		bool materialProjection;							//材质投射
		E_LEVEL	materialResolution;	//材质分辨率
		E_TEXTURE_FILTER	textureFilter;		//材质过滤
		E_LEVEL	viewDistance;			//视野距离
		E_LEVEL	envDetail;		//环境细节
		E_LEVEL	groundScene;		//地面景观
		E_LEVEL	shadowQuality;		//阴影质量
		E_LEVEL	liquidDetail;	//液体细节
		E_LEVEL	sunLightEffect;		//阳光效果
		E_LEVEL		particleDensity;		//粒子密度
		E_LEVEL		SSAO;
	};

	//
	struct SAdvancedSetting
	{
		SAdvancedSetting()
		{
			tripleBuffers = false;
			reduceInputDelay = false;
			useHardwarePointer = false;
			maxForegroundFPS = 120;
			maxBackgroundFPS = 40;
		}
		bool tripleBuffers;
		bool reduceInputDelay;
		bool useHardwarePointer;
		s32 maxForegroundFPS;
		s32 maxBackgroundFPS;
	};

public:

	void retrieveVideoSetting(SVideoSetting* videoSetting) const;
	void applyVideoSetting(const SVideoSetting& videosetting);

	//材质分辨率
	void setMaterialResolution(E_LEVEL level);
	E_LEVEL getMaterialResolution() const;

	//材质过滤
	void setTextureFilter(E_TEXTURE_FILTER filter);
	E_TEXTURE_FILTER getTextureFilter() const;

	//材质投射
	void setMaterialProjection(bool projection);
	bool getMaterialProjection() const;

	//视野距离
	void setViewDistance(E_LEVEL level);
	E_LEVEL getViewDistance() const;

	//环境细节
	void setEnvironmentDetail(E_LEVEL level);
	E_LEVEL getEnvironmentDetail() const;

	//地面景观
	void setGroundScene(E_LEVEL level);
	E_LEVEL getGroundScene() const;

	//阴影质量
	void setShadowQuality(E_LEVEL level);
	E_LEVEL getShadowQuality() const;

	//液体细节
	void setLiquidDetail(E_LEVEL level);
	E_LEVEL getLiquidDetail() const;

	//阳光效果
	void setSunLightEffect(E_LEVEL level);
	E_LEVEL getSunLightEffect() const;

	//粒子密度
	void setParticleDensity(E_LEVEL level);
	E_LEVEL getParticleDensity() const;

	//ssao
	void setSSAO(E_LEVEL level);
	E_LEVEL getSSAO() const;

	void retrieveAdvancedSetting(SAdvancedSetting* advancedSetting) const;
	void applyAdvancedSetting(const SAdvancedSetting& advancedSetting);

	//三倍缓冲
	void setTripleBuffers(bool tripleBuffers);
	bool getTripleBuffers() const;

	//减少输入延迟
	void setReduceInputDelay(bool reduce);
	bool getReduceInputDelay() const;

	//使用硬件指针
	void setHardwarePointer(bool use);
	bool getHardwarePointer() const;

	//前台，后台fps
	void setForegroundFPSLimit(s32 limit);
	s32 getForegroundFPSLimit() const;
	void setBackgroundFPSLimit(s32 limit);
	s32 getBackgroundFPSLimit() const;

};