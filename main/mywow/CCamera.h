#pragma once

#include "ICamera.h"

class IVideoDriver;

class CCamera : public ICamera
{
public:
	CCamera(const vector3df& position, const vector3df& lookat, const vector3df& up, f32 nearValue, f32 farValue, f32 fov);

public:
	//
	virtual const frustum& getViewFrustum() const { return ViewFrustum; }
	virtual const matrix4& getViewMatrix() const { return ViewMatrix; }
	virtual const matrix4& getProjectionMatrix() const { return ProjectionMatrix; }
	virtual const matrix4& getViewProjectionMatrix() const { return ViewProjectionMatrix; }
	virtual const matrix4& getInverseViewMatrix() const { return InverseViewMatrix; }
	virtual const plane3df& getTerrainClipPlane() const { return ClipPlane; }
	virtual const vector3df& getDir() const { return Dir; }
	virtual void setDir(const vector3df& dir) { Dir = dir; Dir.normalize(); }
	virtual const vector3df& getRight() const { return Right; }
	virtual void setUp(const vector3df& up) { Up = up; Up.normalize(); }
	virtual const vector3df& getUp() const { return Up; }

	virtual void onKeyMove(f32 speed, SKeyControl keycontrol);

	virtual void recalculateAll();
	virtual void pitch_yaw_Maya(f32 pitchDegree, f32 yawDegree);
	virtual void move_offset_Maya(f32 xOffset, f32 yOffset);
	virtual void pitch_yaw_FPS(f32 pitchDegree, f32 yawDegree);

	virtual f32 getClipDistance() const  { return ClipDistance; }
	virtual void setClipDistance(f32 distance);
	virtual void makeClipPlane( const plane3df& plane, plane3df& clip );

	virtual vector2di getScreenPositionFrom3DPosition(const vector3df& pos, const recti& screensize);
	virtual line3df getRayFromScreenPosition(vector2di pos, const recti& screensize);
	virtual vector3df get3DPositionFromScreenPosition(vector2di pos, const recti& screensize, f32 distance);

private:

	void recalculateViewMatrix();
	void recalculateProjectionMatrix();
	void recalculateFrustum();

private:
	matrix4		ViewMatrix;
	matrix4  ProjectionMatrix;
	matrix4		ViewProjectionMatrix;
	matrix4		InverseViewMatrix;
	matrix4		ClipProjectionMatrix;
	frustum	ViewFrustum;
	plane3df	ClipPlane;

	vector3df		Dir;
	vector3df		Up;
	vector3df		Right;
	f32		ClipDistance;
};