#pragma once

#include "ISceneNode.h"
#include "SColor.h"

class ICoordSceneNode : public ISceneNode
{
public:
	enum E_COORD_MODE
	{
		ECM_MOVE = 0,
		ECM_ROTATE,
		ECM_SCALE,
		ECM_SCALEALL,

		ECM_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

	enum E_AXIS
	{
		ESA_NONE = 0,
		ESA_X,
		ESA_Y,
		ESA_Z,

		ESA_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

	enum E_POSITION_2D
	{
		EP2D_NONE = 0,
		EP2D_TOPLEFT,
		EP2D_TOPRIGHT,
		EP2D_BOTTOMLEFT,
		EP2D_BOTTOMRIGHT,
		EP2D_TOPCENTER,
		EP2D_BOTTOMCENTER,
		EP2D_CENTERLEFT,
		EP2D_CENTERRIGHT,

		EP2D_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

public:
	ICoordSceneNode(ISceneNode* parent) : ISceneNode(parent),
		Mode(ECM_MOVE), Length(1.0f) { }
	virtual ~ICoordSceneNode() {}

public:
	virtual void attachSceneNode(ISceneNode* node, bool rot = true) = 0;
	virtual ISceneNode* getAttachedSceneNode() const = 0;
	virtual E_AXIS getSelectedAxis() const = 0;
	virtual void checkSelectedAxis(vector2di pos) = 0;
	virtual void setPosition2D(E_POSITION_2D pos2d, f32 distance = 18) = 0;
	virtual void setAxisVisible(bool xVisible, bool yVisible, bool zVisible) = 0;
	virtual void setAxisColor(SColor colorX, SColor colorY, SColor colorZ) = 0;
	virtual void setAxisText(const c8* textX, const c8* textY, const c8* textZ) = 0;
	virtual void setDir(E_AXIS axis, const vector3df& dir) = 0;
	virtual vector3df getDir(E_AXIS axis) const = 0;
	virtual void pitch_yaw_FPS(f32 pitchDegree, f32 yawDegree) = 0;

public:
	E_COORD_MODE		Mode;
	f32  Length;
};