#pragma once

#include "ICoordSceneNode.h"
#include "core.h"

class CCoordSceneNode : public ICoordSceneNode
{
public:
	CCoordSceneNode(ISceneNode* parent);
	~CCoordSceneNode();

public:
	//ICoordSceneNode
	virtual void attachSceneNode(ISceneNode* node, bool rot = true);
	virtual ISceneNode* getAttachedSceneNode() const { return AttachedSceneNode; }
	virtual E_AXIS getSelectedAxis() const { return SelectedAxis; }
	virtual void checkSelectedAxis(vector2di pos);
	virtual void setPosition2D(E_POSITION_2D pos2d, f32 distance = 18);
	virtual void setAxisVisible(bool xVisible, bool yVisible, bool zVisible);
	virtual void setAxisColor(SColor colorX, SColor colorY, SColor colorZ);
	virtual void setAxisText(const c8* textX, const c8* textY, const c8* textZ);
	virtual void setDir(E_AXIS axis, const vector3df& dir);
	virtual vector3df getDir(E_AXIS axis) const;
	virtual void pitch_yaw_FPS(f32 pitchDegree, f32 yawDegree);

	//ISceneNode
	virtual void registerSceneNode(bool frustumcheck = true);
	virtual aabbox3df getBoundingBox() const { return aabbox3df::Zero(); }
	virtual void tick(u32 timeSinceStart, u32 timeSinceLastFrame, bool visible);
	virtual void render();
	virtual bool isNodeEligible() const { return Visible; }

private:
	struct SAxisParam 
	{
		SAxisParam() 
		{
			center.clear();
			xPos = xDir = vector3df::UnitX();
			yPos = yDir = vector3df::UnitY();
			zPos = zDir = vector3df::UnitZ();
		}
		vector3df center;
		vector3df xPos;
		vector3df yPos;
		vector3df zPos;
		vector3df xDir;
		vector3df yDir;
		vector3df zDir;
	};

	SAxisParam	AxisParam;

	bool intersectWith(vector2di pos, E_AXIS axis);
	void calculateAxisParam(SAxisParam& param);
	void drawArrows(const SAxisParam& param);
	void drawAxis(const SAxisParam& param);
	void drawText(const SAxisParam& param);

private:
	E_AXIS		SelectedAxis;
	ISceneNode*		AttachedSceneNode;

	E_POSITION_2D	Position2D;
	f32		Distance;

	SColor ColorX, ColorY, ColorZ;
	string16 TextX, TextY, TextZ;
	bool VisibleX, VisibleY, VisibleZ;;
};

inline void CCoordSceneNode::setPosition2D( E_POSITION_2D pos2d, f32 distance )
{
	Position2D = pos2d;
	Distance = distance;
}

inline void CCoordSceneNode::setAxisVisible( bool xVisible, bool yVisible, bool zVisible )
{
	VisibleX = xVisible;
	VisibleY = yVisible;
	VisibleZ = zVisible;
}

inline void CCoordSceneNode::setAxisColor( SColor colorX, SColor colorY, SColor colorZ )
{
	ColorX = colorX;
	ColorY = colorY;
	ColorZ = colorZ;
}

inline void CCoordSceneNode::setAxisText( const c8* textX, const c8* textY, const c8* textZ )
{
	TextX = textX;
	TextY = textY;
	TextZ = textZ;
}

