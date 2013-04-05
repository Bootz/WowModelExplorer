#include "stdafx.h"
#include "editor_Camera.h"

void Camera_setPosition( ICamera* cam, vector3df pos )
{
	cam->Position = pos;
}

void Camera_getPosition( ICamera* cam, vector3df* pos )
{
	*pos = cam->Position;
}

void Camera_setDir( ICamera* cam, vector3df dir )
{
	cam->setDir(dir);
}

void Camera_getDir( ICamera* cam, vector3df* dir )
{
	*dir = cam->getDir();
}

void Camera_setUp( ICamera* camera, vector3df up )
{
	camera->setUp(up);
}

void Camera_getUp( ICamera* camera, vector3df* up )
{
	*up = camera->getUp();
}

void Camera_onKeyMove( ICamera* cam, f32 speed, ICamera::SKeyControl keyControl )
{
	cam->onKeyMove(speed, keyControl);
}

void Camera_recalculateAll( ICamera* cam )
{
	cam->recalculateAll();
}

void Camera_pitch_yaw_Maya( ICamera* cam, f32 pitchDegree, f32 yawDegree )
{
	cam->pitch_yaw_Maya(pitchDegree, yawDegree);
}

void Camera_move_offset_Maya( ICamera* cam, f32 xOffset, f32 yOffset )
{
	cam->move_offset_Maya(xOffset, yOffset);
}

void Camera_pitch_yaw_FPS( ICamera* cam, f32 pitchDegree, f32 yawDegree )
{
	cam->pitch_yaw_FPS(pitchDegree, yawDegree);
}

