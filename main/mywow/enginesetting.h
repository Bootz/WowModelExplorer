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
		bool materialProjection;							//����Ͷ��
		E_LEVEL	materialResolution;	//���ʷֱ���
		E_TEXTURE_FILTER	textureFilter;		//���ʹ���
		E_LEVEL	viewDistance;			//��Ұ����
		E_LEVEL	envDetail;		//����ϸ��
		E_LEVEL	groundScene;		//���澰��
		E_LEVEL	shadowQuality;		//��Ӱ����
		E_LEVEL	liquidDetail;	//Һ��ϸ��
		E_LEVEL	sunLightEffect;		//����Ч��
		E_LEVEL		particleDensity;		//�����ܶ�
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

	//���ʷֱ���
	void setMaterialResolution(E_LEVEL level);
	E_LEVEL getMaterialResolution() const;

	//���ʹ���
	void setTextureFilter(E_TEXTURE_FILTER filter);
	E_TEXTURE_FILTER getTextureFilter() const;

	//����Ͷ��
	void setMaterialProjection(bool projection);
	bool getMaterialProjection() const;

	//��Ұ����
	void setViewDistance(E_LEVEL level);
	E_LEVEL getViewDistance() const;

	//����ϸ��
	void setEnvironmentDetail(E_LEVEL level);
	E_LEVEL getEnvironmentDetail() const;

	//���澰��
	void setGroundScene(E_LEVEL level);
	E_LEVEL getGroundScene() const;

	//��Ӱ����
	void setShadowQuality(E_LEVEL level);
	E_LEVEL getShadowQuality() const;

	//Һ��ϸ��
	void setLiquidDetail(E_LEVEL level);
	E_LEVEL getLiquidDetail() const;

	//����Ч��
	void setSunLightEffect(E_LEVEL level);
	E_LEVEL getSunLightEffect() const;

	//�����ܶ�
	void setParticleDensity(E_LEVEL level);
	E_LEVEL getParticleDensity() const;

	//ssao
	void setSSAO(E_LEVEL level);
	E_LEVEL getSSAO() const;

	void retrieveAdvancedSetting(SAdvancedSetting* advancedSetting) const;
	void applyAdvancedSetting(const SAdvancedSetting& advancedSetting);

	//��������
	void setTripleBuffers(bool tripleBuffers);
	bool getTripleBuffers() const;

	//���������ӳ�
	void setReduceInputDelay(bool reduce);
	bool getReduceInputDelay() const;

	//ʹ��Ӳ��ָ��
	void setHardwarePointer(bool use);
	bool getHardwarePointer() const;

	//ǰ̨����̨fps
	void setForegroundFPSLimit(s32 limit);
	s32 getForegroundFPSLimit() const;
	void setBackgroundFPSLimit(s32 limit);
	s32 getBackgroundFPSLimit() const;

};