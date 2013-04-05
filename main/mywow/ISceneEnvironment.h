#pragma once

#include "core.h"
#include "SColor.h"

struct SOutDoorLight
{
	SOutDoorLight() : fogColor(0.3f,0.3f,0.3f)
	{
		hour = 0;
		minute = 0;
		dayIntensity = 0;
		nightIntensity = 0;
		ambientIntensity = 0;
		fogIntensity = 0;
		fogDepth = 0;
	}
	f32 hour;
	f32 minute;
	f32 dayIntensity;
	f32 nightIntensity;
	f32 ambientIntensity;
	f32 fogIntensity;
	f32 fogDepth;
	vector3df	dayColor;
	vector3df	nightColor;
	vector3df	ambientColor;
	vector3df	fogColor;
	vector3df dayDirection;
	vector3df nightDirection;
};

class ISceneEnvironment
{
public:
	ISceneEnvironment() 
		: AmbientColor(255, 255, 255), DirLightColor(SColor::White()), LightDir(-vector3df::UnitY())
	{
		EnableDirLight = false;
		SpecularStrength = 0.5f;
	}
	virtual ~ISceneEnvironment() {}

	static const int INDEX_DIR_LIGHT = 0;

public:
	static const u32 MAX_DAYTIME = 2880;			//24 * 60 * 2
	
	virtual void computeOutdoorLight(s32 time) = 0;
	virtual void setDayTime(s32 hour, s32 minute) = 0;
	virtual void setDayTime(s32 time) = 0;
	virtual s32 getDayTime() const = 0;

	virtual SColor getFogColor() { return SColorf(OutDoorLightInfo.fogColor).toSColor(); }

public:
	SOutDoorLight		OutDoorLightInfo;

	//light
	vector3df	LightDir;
	SColor	AmbientColor;
	SColor	DirLightColor;
	f32		SpecularStrength;			

	bool EnableDirLight;
};