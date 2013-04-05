#pragma once

#include "core.h"
#include <list>

class IFileM2;

enum E_ACTION
{
	ACTION_STAND = 0,
	ACTION_ROLL,
	ACTION_FLYINGKICK,
	ACTION_JUMP,
	ACTION_USESTANDING,
	ACTION_CRANE,
	ACTION_KNEEL,
	ACTION_EMOTEREAD,
	ACTION_DANCE,
	ACTION_SPINNINGKICK,
	ACTION_TORPEDO,
	ACTION_WALK,
	ACTION_RUN,
	ACTION_SITGROUND,

	ACTION_COUNT,
};

static const c8* g_actionNames[] =
{
	"Stand",
	"Roll",
	"FlyingKick",
	"Jump",
	"UseStanding",
	"Crane",
	"Kneel",
	"SpellKneel",
	"EmoteRead",
	"Dance",
	"SpinningKick",
	"Torpedo",
	"Walk",
	"Run",
	"SitGround",
};

inline const c8* getActionName(E_ACTION action)
{
	if (action < ARRAY_COUNT(g_actionNames))
		return g_actionNames[action];

	return "";
}


//一个由基本animation组成的列表
class wow_m2Action
{
private:
	DISALLOW_COPY_AND_ASSIGN(wow_m2Action);

public:
	enum E_PLAY_TYPE
	{
		EPT_RANDOM = 0,
		EPT_SEQUENCE,
	};

	struct SAnimationEntry
	{
		c8 strName[DEFAULT_SIZE];
		u32 subIdx;
		s32 loopTime;
	};

public:
	wow_m2Action(IFileM2* filem2, const c8* name, E_PLAY_TYPE playType, s32 maxPlayTime = -1);
	~wow_m2Action();

private:
	struct SAnimEntry 
	{
		u32 entryIndex;
		s32 animIndex;
		s32 loopTime;
	};

public:
	u32 getAnimationCount() const { return AnimationList.size(); }
	
	bool pushAnimationEntry(const c8* animName, u32 subIdx, s32 loopTime);

	void clear();

	const c8* getActionName() const { return Name; }

	E_PLAY_TYPE getPlayType() const { return PlayType; }

	bool isInfinite() const { return MaxPlayTime == -1; }

	typedef std::list<SAnimEntry, qzone_allocator<SAnimEntry>> T_AnimationList;	
	T_AnimationList	AnimationList;

	//random
	u32 TotalLoopTime;
	s32	MaxPlayTime;

private:
	c8		Name[DEFAULT_SIZE];
	IFileM2* FileM2;

	E_PLAY_TYPE		PlayType;
};
