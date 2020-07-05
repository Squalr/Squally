#pragma once

#include "Objects/Platformer/Combat/CombatObject.h"

class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class SmartParticles;
class TimelineEntry;
class WorldSound;

class EnvelopingWinds : public CombatObject
{
public:
	static EnvelopingWinds* create(PlatformerEntity* caster, PlatformerEntity* target);

protected:
	EnvelopingWinds(PlatformerEntity* caster, PlatformerEntity* target);
	virtual ~EnvelopingWinds();

	void onEnter() override;
	void onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed) override;

private:
	typedef CombatObject super;

	SmartParticles* wind;

	static const float WindDrain;
};
