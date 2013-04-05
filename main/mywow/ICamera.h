#pragma once

#include "core.h"

class ICamera
{
public:
	struct SKeyControl 
	{
		bool front;
		bool back;
		bool left;
		bool right;
		bool up;
		bool down;
	};

public:
	ICamera()
	{
		IsOrthogonal = false;
		NearValue = 1.0f;
		FarValue = 2000.0f;
		AspectRatio = 1.0f;
		FOV = PI / 4;
	}

	virtual ~ICamera() {}

public:
	//
	virtual const frustum& getViewFrustum() const = 0;
	virtual const matrix4& getViewMatrix() const = 0;
	virtual const matrix4& getProjectionMatrix() const = 0;
	virtual const matrix4& getViewProjectionMatrix() const = 0;
	virtual const matrix4& getInverseViewMatrix() const = 0;
	virtual const plane3df& getTerrainClipPlane() const = 0;
	virtual const vector3df& getDir() const  = 0; 
	virtual void setDir(const vector3df& dir) = 0;
	virtual const vector3df& getRight() const = 0;
	virtual void setUp(const vector3df& up) = 0;
	virtual const vector3df& getUp() const = 0;

	virtual void onKeyMove(f32 speed, SKeyControl keycontrol) = 0;

	virtual void recalculateAll() = 0;
	virtual void pitch_yaw_Maya(f32 pitchDegree, f32 yawDegree) = 0;
	virtual void move_offset_Maya(f32 xOffset, f32 yOffset) = 0;
	virtual void pitch_yaw_FPS(f32 pitchDegree, f32 yawDegree) = 0;

	virtual f32 getClipDistance() const = 0;
	virtual void setClipDistance(f32 distance) = 0;
	virtual void makeClipPlane( const plane3df& plane, plane3df& clip ) = 0;

	virtual vector2di getScreenPositionFrom3DPosition(const vector3df& pos, const recti& screensize) = 0;
	virtual line3df getRayFromScreenPosition(vector2di pos, const recti& screensize) = 0;
	virtual vector3df get3DPositionFromScreenPosition(vector2di pos, const recti& screensize, f32 distance) = 0;

public:
	vector3df		Position;
	f32		NearValue;
	f32		FarValue;
	f32		AspectRatio;
	f32		FOV;
	bool	IsOrthogonal;
};
