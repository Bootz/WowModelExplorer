#pragma once

#include "ISceneStateServices.h"

class CD3D11Driver;

class CD3D11SceneStateServices : public ISceneStateServices
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D11SceneStateServices);
public:
	CD3D11SceneStateServices();

public:
	virtual SColor getAmbientLight() const { return SceneState.AmbientLightColor; }
	virtual void setAmbientLight( SColor color );
	virtual void deleteAllDynamicLights();
	virtual bool setDynamicLight( u32 index, const SLight& light );
	virtual const SLight* getDynamicLight(u32 index) const;
	virtual void turnLightOn(u32 lightIndex, bool turnOn);

	virtual void setFog(SFogParam fogParam);
	virtual SFogParam getFog() const { return SceneState.FogParam; }

	virtual bool setClipPlane( u32 index, const plane3df& plane );
	virtual void enableClipPlane( u32 index, bool enable );

	virtual bool reset() { return true; }

private:
	CD3D11Driver*	Driver;
	ID3D11Device*		pID3DDevice;
	SSceneState		SceneState;
};