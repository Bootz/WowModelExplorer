#pragma once

enum E_M2_STATES
{
	EMS_STAND = 0,
	EMS_ROLL,
	EMS_JUMP,
	EMS_KNEEL,
	EMS_DANCE,
	EMS_FLYINGKICK,
	EMS_EMOTEREAD,
	EMS_CRANE,
	EMS_SPINNINGKICK,
	EMS_TORPEDO,
	EMS_WALK,
	EMS_RUN,
	EMS_SITGROUND,

	EMS_COUNT,

	EMS_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

template <class entity_type>
class wow_m2State
{
public:
	virtual ~wow_m2State() {}

public:
	virtual bool isValid(entity_type* entity) const = 0;
	virtual bool enter(entity_type* entity) = 0;
	virtual void tick(entity_type* entity, u32 timeSinceStart, u32 timeSinceLastFrame) = 0;
	virtual void exit(entity_type* entity) = 0;

	virtual E_M2_STATES getType() const = 0;
};