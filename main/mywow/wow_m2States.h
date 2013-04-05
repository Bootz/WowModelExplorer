#pragma once

#include "base.h"
#include "wow_m2State.h"
#include "wow_m2action.h"

//m2µÄ×´Ì¬

class IM2SceneNode;
class wow_m2Action;

//ÐÝÏÐ
class wow_m2State_Stand : public wow_m2State<IM2SceneNode>
{
private:
	DISALLOW_COPY_AND_ASSIGN(wow_m2State_Stand);

public:
	wow_m2State_Stand() : M2Action(NULL) {}

	virtual bool isValid(IM2SceneNode* entity) const;
	virtual bool enter(IM2SceneNode* entity);
	virtual void tick(IM2SceneNode* entity, u32 timeSinceStart, u32 timeSinceLastFrame) {}
	virtual void exit(IM2SceneNode* entity) { M2Action= NULL; }

	virtual E_M2_STATES getType() const { return EMS_STAND; }

private:
	wow_m2Action* M2Action;
};

//Ë³Ðò²¥·Å¶¯×÷
class wow_m2State_commonAction : public wow_m2State<IM2SceneNode>
{
private:
	DISALLOW_COPY_AND_ASSIGN(wow_m2State_commonAction);
public:
	wow_m2State_commonAction(E_ACTION action, E_M2_STATES state)
		: ActionType(action), State(state), M2Action(NULL) {}

	virtual bool isValid(IM2SceneNode* entity) const;
	virtual bool enter(IM2SceneNode* entity);
	virtual void tick(IM2SceneNode* entity, u32 timeSinceStart, u32 timeSinceLastFrame);
	virtual void exit(IM2SceneNode* entity);

	virtual E_M2_STATES getType() const { return State; }

private:
	wow_m2Action* M2Action;
	E_ACTION	ActionType;
	E_M2_STATES State;
};

