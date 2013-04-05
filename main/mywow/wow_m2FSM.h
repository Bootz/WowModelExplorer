#pragma once

#include "core.h"
#include "wow_m2action.h"
#include "wow_m2State.h"

class IM2SceneNode;

struct SDynAction
{
	SDynAction() 
		: action(NULL), finished(true), playedTime(0), currentAnimLoop(0)
	{
	}
	wow_m2Action* action;

	wow_m2Action::T_AnimationList::iterator currentIterator;
	u32 currentAnimLoop;
	s32 playedTime;		//²¥·Å´ÎÊý
	bool finished;
};

class wow_m2FSM
{
public:
	wow_m2FSM(IM2SceneNode* node);
	~wow_m2FSM();

public:
	void onAnimationEnd();

	bool playAction(wow_m2Action* action, u32 blendtime = 200);

	const SDynAction& getDynAction() { return DynAction; }

	bool isPlaying(wow_m2Action* action) const;

	//state management
	void tick(u32 timeSinceStart, u32 timeSinceLastFrame);

	void resetState();

	bool changeState(wow_m2State<IM2SceneNode>* newstate);

	bool changeState(E_M2_STATES state);

	void revertToPreviousState()
	{
		changeState(PreviousState);
	}

	bool isInState(E_M2_STATES state) const
	{
		return CurrentState && CurrentState->getType() == state;
	}

	wow_m2State<IM2SceneNode>* getState(E_M2_STATES state) const;

private:
	void buildStates();
	void destroyStates();

	void finishAction();

	bool playActionSequence(wow_m2Action* action, u32 blendtime = 200);
	bool playActionRandom(wow_m2Action* action, u32 blendtime = 200);

	void onAnimationEndSequence();
	void onAnimationEndRandom();

private:
	IM2SceneNode*			M2SceneNode;

	wow_m2State<IM2SceneNode>*	States[EMS_COUNT];	
//
	wow_m2State<IM2SceneNode>*	CurrentState;
	wow_m2State<IM2SceneNode>*	PreviousState;
	wow_m2State<IM2SceneNode>*	GlobalState;

	SDynAction		DynAction;
};