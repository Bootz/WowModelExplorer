#include "stdafx.h"
#include "editor_CoordSceneNode.h"

void CoordSceneNode_setPosition2D( ICoordSceneNode* node, ICoordSceneNode::E_POSITION_2D position, f32 distance )
{
	node->setPosition2D(position, distance);
}

void CoordSceneNode_setAxisColor( ICoordSceneNode* node, SColor colorX, SColor colorY, SColor colorZ )
{
	node->setAxisColor(colorX, colorY, colorZ);
}

void CoordSceneNode_setAxisText( ICoordSceneNode* node, const c8* textX, const c8* textY, const c8* textZ )
{
	node->setAxisText(textX, textY, textZ);
}